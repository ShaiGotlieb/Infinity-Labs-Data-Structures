#ifndef __H__IP__
#define __H__IP__

#include <stddef.h> /* size_t */

typedef unsigned char ip_t[4];
typedef enum { FALSE = 0, TRUE = 1}boolean;
typedef enum { SUCCESS = 0, FAILURE = 1}status;

unsigned char *IpSetBitOn(ip_t ip, int index);
unsigned char *IpSetBitOff(ip_t ip, int index);
int IpIsBitOn(ip_t ip, int index);
size_t IpGetSize(int host_size);
int IsSameIp(ip_t ip1, ip_t ip2);
int IpIsInNetworkRange(ip_t ip1, ip_t ip2, int network_mask);
int IsSameBroadcastIp(ip_t ip, int network_mask);

#endif 