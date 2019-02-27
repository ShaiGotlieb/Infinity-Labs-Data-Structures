#include <assert.h>
#include <math.h> /* pow */
#include <stdlib.h> /* size_t, malloc, free */
#include <string.h> /* memcpy */

#include "ip.h"
#include "dhcp.h"
#include "trie.h"

const int IP_MAX_SIZE_BYTES = 4;
const int MAX_HOST_SIZE = 32;
const int NETWORK_IP_SIZE = 1;

struct dhcp_s
{
	trie_t *trie;
	ip_t network_address;
	int network_mask;
};

dhcp_t *DHCPCreate(const ip_t network_address, int network_mask)
{
	dhcp_t *dhcp = NULL;

	dhcp = (dhcp_t*)malloc(sizeof(dhcp_t));
	if (NULL == dhcp)
	{
		return (NULL);
	}

	dhcp->trie = TrieCreate(MAX_HOST_SIZE - network_mask);
	if (NULL == dhcp->trie)
	{
		free(dhcp);
		dhcp = NULL;

		return (NULL);
	}

	memcpy(dhcp->network_address,network_address, IP_MAX_SIZE_BYTES);
	dhcp->network_mask = network_mask;

	return (dhcp);
}

void DHCPDestroy(dhcp_t *dhcp)
{
	TrieDestroy(dhcp->trie);
	dhcp->trie = NULL;

	free(dhcp);
	dhcp = NULL;
}

alloc_return_status_t DHCPAlloc(dhcp_t *dhcp, const ip_t requested_ip_address,
      						                          ip_t allocated_address)
{
	assert(TRUE == IpIsInNetworkRange(dhcp->network_address, (unsigned char *)requested_ip_address, dhcp->network_mask));

	if ((NULL == requested_ip_address) || SUCCESS != GetPath(dhcp->trie, (unsigned char*)requested_ip_address))
	{
		node_t *node = GetNextFreeNode(dhcp->trie);
		if (NULL == node)
		{
			return (FAILED_TO_ALLOCATE);
		}

		SetPath(dhcp->trie, node, allocated_address);

		return (ALLOCATED_OTHER_ADDRESS);
	}
	else 
	{
		memcpy(allocated_address, requested_ip_address, IP_MAX_SIZE_BYTES);
		
		return (ALLOCATED_REQUESTED_ADDRESS);
	}
}

void DHCPFree(dhcp_t *dhcp, const ip_t to_free)
{
	node_t *node = NULL;

	assert(TRUE == IpIsInNetworkRange(dhcp->network_address, (unsigned char *)to_free, dhcp->network_mask));
	assert(FALSE == IsSameBroadcastIp((unsigned char*)to_free, dhcp->network_mask));
	assert(FALSE == IsSameIp(dhcp->network_address, (unsigned char*)to_free));

	node = FindNode(dhcp->trie, (unsigned char*)to_free);

	assert(NULL != node);

	TrieUpdateUsedNodes(dhcp->trie, node, FALSE);
}

size_t DHCPCountFree(dhcp_t *dhcp)
{
	return (IpGetSize(MAX_HOST_SIZE - dhcp->network_mask) - TrieCountFree(dhcp->trie));
}
