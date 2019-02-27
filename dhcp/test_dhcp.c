#include <stdlib.h> /* EXIT_SUCCESS, size_t */

#include "test.h"
#include "ip.h"
#include "dhcp.h"
#include "trie.h"

#define SIZE_ARR(a) (sizeof(a)/sizeof(a[0]))
#define UNUSED(a) ((void)(a))
#define HOST_SIZE (8)
#define TOTAL_IPS (256)
#define NETWORK_MASK (24)
#define SUCCESS (0)
#define FAILURE (1)
#define NETWORK_IP_SIZE (1)
#define BROADCAST_IP_SIZE (1)
#define FALSE (0)
#define TRUE (1)

ip_t ips[] = 
{
	{10, 1, 0, 1},
	{10, 1, 0, 3},
	{10, 1, 0, 5},
	{10, 1, 0, 7},
	{10, 1, 0, 9},
};

ip_t network_ips[] = 
{
	{10, 1, 0, 0},
	{10, 1, 0, 0},
	{10, 1, 0, 0},
	{10, 1, 0, 0},
	{10, 1, 0, 0},
};

TestResult TestDHCPCreate();
TestResult TestDHCPAlloc();
TestResult TestDHCPFree();
TestResult TestDHCPCountFree();

int main()
{
	RUN_TEST(TestDHCPCreate);
	RUN_TEST(TestDHCPAlloc);
	RUN_TEST(TestDHCPFree);
	RUN_TEST(TestDHCPCountFree);

	return (EXIT_SUCCESS);
}

TestResult TestDHCPCreate()
{
	dhcp_t *dhcp = DHCPCreate(ips[0], NETWORK_MASK);

	REQUIRE(NULL != dhcp);

	DHCPDestroy(dhcp);
	
	return (TEST_PASS);
}

TestResult TestDHCPAlloc()
{
	dhcp_t *dhcp = DHCPCreate(network_ips[0], NETWORK_MASK);
	dhcp_t *dhcp_full = DHCPCreate(network_ips[0], NETWORK_MASK);
	dhcp_t *dhcp_null = DHCPCreate(network_ips[0], NETWORK_MASK);
	ip_t allocated_ip = {0};
	size_t i;

	for (i = 0; i < SIZE_ARR(ips) ; ++i)
	{
		REQUIRE(ALLOCATED_REQUESTED_ADDRESS == DHCPAlloc(dhcp, ips[i], allocated_ip));
		REQUIRE(ALLOCATED_OTHER_ADDRESS == DHCPAlloc(dhcp, ips[i], allocated_ip));
	}

	for (i = 0; i < TOTAL_IPS - 2; ++i)
	{
		DHCPAlloc(dhcp_full, ips[0], allocated_ip);
		REQUIRE(ALLOCATED_OTHER_ADDRESS == DHCPAlloc(dhcp_null, NULL, allocated_ip));
	}

	REQUIRE(0 == DHCPCountFree(dhcp_full));
	REQUIRE(FAILED_TO_ALLOCATE == DHCPAlloc(dhcp_full, ips[0], allocated_ip));

	DHCPDestroy(dhcp);
	DHCPDestroy(dhcp_full);
	DHCPDestroy(dhcp_null);
	
	return (TEST_PASS);
}

TestResult TestDHCPFree()
{
	dhcp_t *dhcp = DHCPCreate(network_ips[0], NETWORK_MASK);
	dhcp_t *dhcp_full = DHCPCreate(network_ips[0], NETWORK_MASK);
	ip_t allocated_ip;
	size_t i;

	for (i = 0; i < SIZE_ARR(ips) ; ++i)
	{
		REQUIRE(ALLOCATED_REQUESTED_ADDRESS == DHCPAlloc(dhcp, ips[i], allocated_ip));
		REQUIRE(ALLOCATED_OTHER_ADDRESS == DHCPAlloc(dhcp, ips[i], allocated_ip));
	}

	for (i = 0; i < SIZE_ARR(ips) ; ++i)
	{
		DHCPFree(dhcp, ips[i]);
		REQUIRE(ALLOCATED_REQUESTED_ADDRESS == DHCPAlloc(dhcp, ips[i], allocated_ip));
	}

	DHCPDestroy(dhcp);
	DHCPDestroy(dhcp_full);
	
	return (TEST_PASS);
}

TestResult TestDHCPCountFree()
{
	dhcp_t *dhcp = DHCPCreate(network_ips[0], NETWORK_MASK);
	ip_t allocated_ip;
	size_t i;

	for (i = 0; i < SIZE_ARR(ips) ; ++i)
	{
		REQUIRE(ALLOCATED_REQUESTED_ADDRESS == DHCPAlloc(dhcp, ips[i], allocated_ip));
	}

	REQUIRE(TOTAL_IPS - SIZE_ARR(ips) - NETWORK_IP_SIZE - BROADCAST_IP_SIZE == DHCPCountFree(dhcp));

	for (i = 0; i < SIZE_ARR(ips) ; ++i)
	{
		DHCPFree(dhcp, ips[i]);
	}

	REQUIRE(TOTAL_IPS - NETWORK_IP_SIZE - BROADCAST_IP_SIZE == DHCPCountFree(dhcp));

	DHCPDestroy(dhcp);
	
	return (TEST_PASS);
}