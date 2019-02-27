#include <assert.h>
#include <math.h> /* pow */

#include "ip.h"

#define MAX_HOST_SIZE (32)

const int BYTE_SIZE = 8;
int byte_index_lut[MAX_HOST_SIZE];

void InitLutByte()
{
	int i = 0, j = BYTE_SIZE, k = BYTE_SIZE * 2, m = BYTE_SIZE * 3;

	for (i = 0; i < 8; ++i, ++j, ++k, ++m)
	{
		byte_index_lut[i] = 3;
		byte_index_lut[j] = 2;
		byte_index_lut[k] = 1;
		byte_index_lut[m] = 0;
	}
}

unsigned char *IpSetBitOn(ip_t ip, int index)
{
	unsigned int mask = 1;
	
	InitLutByte();

	mask <<= index % BYTE_SIZE;
	ip[byte_index_lut[index]] |= mask;

	return (ip);
}

unsigned char *IpSetBitOff(ip_t ip, int index)
{
	unsigned int mask = 1;
	
	InitLutByte();

	mask <<= index % BYTE_SIZE;
	ip[byte_index_lut[index]] &= ~mask;

	return (ip);
}

int IpIsBitOn(ip_t ip, int index)
{
	unsigned int mask = 1;

	InitLutByte();

	return !!(ip[byte_index_lut[index]] & (mask << (index % 8)));
}

size_t IpGetSize(int host_size)
{
	return (pow(2, host_size));
}

int IpIsInNetworkRange(ip_t ip1, ip_t ip2, int network_mask)
{
	int index = MAX_HOST_SIZE - 1;
	int starting_host_index	= index - network_mask;

	if (NULL == ip2)
	{
		return (TRUE);
	}

	while (index >= starting_host_index)
	{
		if (IpIsBitOn(ip1, index) != IpIsBitOn(ip2, index))
		{
			return (FALSE);
		}

		index--;
	}

	return (TRUE);
}

int IsSameBroadcastIp(ip_t ip, int network_mask)
{
	int index = MAX_HOST_SIZE - network_mask - 1;

	if (NULL == ip)
	{
		return (TRUE);
	}

	while (index >= 0)
	{
		if (!IpIsBitOn(ip, index))
		{
			return (FALSE);
		}

		index--;
	}

	return (TRUE);
}

int IsSameIp(ip_t ip1, ip_t ip2)
{
	int index = MAX_HOST_SIZE - 1;

	while (index >= 0)
	{
		if (IpIsBitOn(ip1, index) != IpIsBitOn(ip2, index))
		{
			return (FALSE);
		}

		index--;
	}

	return (TRUE);
}

