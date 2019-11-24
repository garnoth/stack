#pragma once
#include <stdint.h>
#include "eth.h"

/* Manually defined system headers
 * For networking protocols
 *
 * ARP related structures defined here
 */

#define ARP_REQUEST 1
#define ARP_REPLY   2
#define ARP_REV_REQ 3
#define ARP_REV_REP 4

#define ARP_TABLE_MAX 64

#define ARP_ENTRY_FREE          0
#define ARP_ENTRY_RESOLVED      1
#define ARP_ENTRY_UNRESOLVED    2  
/*
 *  Address lengths format
 */
#define ARP_HRD_ETH 	0x0001	/* ethernet hardware type for ARP */
#define ARP_IP_ADDR_LEN 0x0004  /* IP address byte len */


struct arp_cache_entry
{
    uint32_t      src_ip;
    unsigned char src_mac[ETH_ADDR_LEN];
    unsigned short  resolved; /* 0 == unresolved, 1 = resolved */
};

struct arp_hdr
{
    uint16_t      hwtype;
    uint16_t      protype;
    unsigned char hwsize;
    unsigned char prosize;
    uint16_t      opcode; // request or reply
    unsigned char data[];
} __attribute__((packed));

struct arp_ipv4
{
    unsigned char src_mac[ETH_ADDR_LEN];
    uint32_t      src_ip;
    unsigned char dst_mac[ETH_ADDR_LEN];
    uint32_t      dst_ip;
} __attribute__((packed));

//setup the ARP subsystem
void arp_system_init();

// process an incomming ARP packet
void arp_recv( struct eth_hdr *);

// create an arp response to send out to the network
void arp_send(uint32_t, unsigned char *, int);

void mac_to_string(char *, unsigned char*);
