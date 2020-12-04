//filename: netdev.h

// the struct for a netdev. This is a structure which holds the network device
// layer information like configured ip addr and hardware mac address and
// interface mtu which we get from the tap device
#pragma once
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h> // malloc
#include <stdio.h> // perror
#include "gbuf.h"
#include "eth.h"
#include "ip.h"
#include "tools.h"
#include <string.h> // memcpy
#include "tap.h"

struct netdev
{
    uint32_t    ip_addr;
    uint8_t     ip_addr_len;
    uint8_t     hw_addr[ETH_ADDR_LEN]; // def 6 bytes
    uint16_t    mtu;
};

// makes calls to setup a loopback device and a basic netdev device
// hardcoded just for the 2 devices atm. loopback may not be needed
// this function currently has the hardcoded ip and mac values
void init_netdev();

// setup up the netdev struct when called by init
// and returns a ptr to the allocated memory
static struct netdev * alloc_netdev(char *ip_addr, unsigned char *hw_addr, uint16_t mtu, int);

// fills in the netdev layer items like dst and src mac and
// ethertype fields before writing to the tap
int write_netdev( struct netdev * device, char * buf, size_t len, uint8_t *dst_hw, uint16_t ethertype);

// return a pointer to the netdev if the given ip matches what we have
// configured previously. Takes a host ordered ip address
struct netdev * get_netdev_self(uint32_t);

// process recieving a packet, send packets to arp or ip4/6 layer
static int recv_netdev(struct gbuf *gbuf);
