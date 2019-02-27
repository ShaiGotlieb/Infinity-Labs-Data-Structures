#ifndef __H__DHCP__
#define __H__DHCP__

#include "ip.h"
/********************************************************************
 * DHCP - the API for DHCP data structure. 
 *******************************************************************/

typedef struct dhcp_s dhcp_t;

typedef enum alloc_return_status {ALLOCATED_REQUESTED_ADDRESS = 0, 
	                              ALLOCATED_OTHER_ADDRESS     = 1,
	                              FAILED_TO_ALLOCATE           = 2} 
alloc_return_status_t;

dhcp_t *DHCPCreate(const ip_t network_address, int network_mask);
/********************************************************************
 * DHCPCreate - creates dhcp_t
 *
 * network_address - the network's prefix.
 *
 * network_mask - the network's mask.
 *
 * Returns - a pointer to the DHCP.
 *******************************************************************/

void DHCPDestroy(dhcp_t *dhcp);
/********************************************************************
 * DHCPDestroy - frees the DHCP.
 *
 * dhcp - a pointer to dhcp_t.
 *******************************************************************/

alloc_return_status_t DHCPAlloc(dhcp_t *dhcp, const ip_t requested_ip_address,
      						                          ip_t allocated_address);
/******************************************************************** 
 * DHCPAlloc - allocates an ip address from the DHCP.
 *
 * dhcp - a pointer to dhcp_t
 *
 * requested_ip_address - an ip address requested by the user.
 * if address is unavailable a different address will be returned.
 * if there's no preference, the user may enter NULL.
 * 
 * Returns - an ip address. If no address is available - NULL will 
 * be returned.
 *******************************************************************/

void DHCPFree(dhcp_t *dhcp, const ip_t to_free);
/********************************************************************
 * DHCPFree - frees an ip address.
 *
 * dhcp - a pointer to dhcp_t
 *
 * ip_address - an ip address to be made available for use again.
 *******************************************************************/

size_t DHCPCountFree(dhcp_t *dhcp);
/********************************************************************
 * CountFree - Counts the number of available ip addresses.
 *
 * dhcp - a pointer to dhcp_t.
 *
 * Returns - the number of available ip addresses.
 *******************************************************************/

#endif