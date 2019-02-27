#include <stdlib.h> /* EXIT_SUCCESS, size_t */

#include "test.h"
#include "ip.h"

#define SIZE_ARR(a) (sizeof(a)/sizeof(a[0]))
#define UNUSED(a) ((void)(a))
#define TRUE (1)
#define FALSE (0)
#define NETWORK_MASK (24)
#define MAX_IPS (256)
#define HOST_SIZE (8)

TestResult TestIsBitOn();
TestResult TestIsInNetworkRange();
TestResult TestIsSameBroadcastIp();
TestResult TestIsSameIp();
TestResult TestIpGetSize();
TestResult TestSetBitOff();

ip_t ips[] = 
{
	{11, 1, 1, 1},
	{11, 1, 1, 3},
	{11, 1, 1, 5},
	{11, 1, 1, 7},
	{11, 1, 1, 255},
};

ip_t network_ips[] = 
{
	{11, 1, 1, 0},
	{11, 1, 1, 0},
	{11, 1, 1, 0},
	{11, 1, 1, 0},
	{11, 1, 1, 0},
};

int main()
{
	RUN_TEST(TestIsBitOn);
	RUN_TEST(TestIsInNetworkRange);
	RUN_TEST(TestIsSameBroadcastIp);
	RUN_TEST(TestIsSameIp);
	RUN_TEST(TestIpGetSize);
	RUN_TEST(TestSetBitOff);

	return (EXIT_SUCCESS);
}

TestResult TestIsBitOn()
{
	size_t i;

	for (i = 0; i < SIZE_ARR(ips) - 1; i++)
	{
		REQUIRE(TRUE == IpIsBitOn(ips[i], 0));
		REQUIRE(FALSE == IpIsBitOn(ips[i], 7));
	}

	return (TEST_PASS);
}

TestResult TestIsInNetworkRange()
{
	size_t i;

	for (i = 0; i < SIZE_ARR(ips) - 1; i++)
	{
		REQUIRE(TRUE == IpIsInNetworkRange(network_ips[i], ips[i], NETWORK_MASK));
	}

	return (TEST_PASS);
}

TestResult TestIsSameBroadcastIp()
{
	size_t i;

	for (i = 0; i < SIZE_ARR(ips) - 1; i++)
	{
		REQUIRE(FALSE == IsSameBroadcastIp(ips[i], NETWORK_MASK));
	}

	REQUIRE(TRUE == IsSameBroadcastIp(ips[i], NETWORK_MASK));

	return (TEST_PASS);
}

TestResult TestIsSameIp()
{
	size_t i;

	for (i = 0; i < SIZE_ARR(ips) - 1; i++)
	{
		REQUIRE(TRUE == IsSameIp(ips[i], ips[i]));
	}

	REQUIRE(FALSE == IsSameIp(ips[1], ips[0]));

	return (TEST_PASS);
}

TestResult TestIpGetSize()
{
	REQUIRE(MAX_IPS == IpGetSize(HOST_SIZE));

	return (TEST_PASS);
}

TestResult TestSetBitOff()
{
	size_t i;

	for (i = 0; i < SIZE_ARR(ips) - 1; i++)
	{
		IpSetBitOff(ips[i], 0);
		REQUIRE(FALSE == IpIsBitOn(ips[i], 0));
	}

	return (TEST_PASS);
}

TestResult TestSetBitOn()
{
	size_t i;

	for (i = 0; i < SIZE_ARR(ips) - 1; i++)
	{
		IpSetBitOff(ips[i], 0);
		IpSetBitOn(ips[i], 0);
		REQUIRE(TRUE == IpIsBitOn(ips[i], 0));
	}

	return (TEST_PASS);
}