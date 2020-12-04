#pragma once
#include <pthread.h>
#include <stdint.h>
#include "eth.h"
#include "netdev.h"

/* Manually defined system headers
 * For networking protocols
 *
 * ARP related structures defined here
 */
#define ARP_REQUEST 1
#define ARP_REPLY   2
#define ARP_REV_REQ 3
#define ARP_REV_REP 4

#define ARP_TABLE_MAX 64 // unused

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
    unsigned char src_mac[ETH_ADDR_LEN]; // usually 6 bytes
    uint32_t      src_ip;
    unsigned char dst_mac[ETH_ADDR_LEN]; 
    uint32_t      dst_ip;
} __attribute__((packed));

//global var for ARP system thread
pthread_t arp_thread;

void* arp_thread_routine();

// setup the ARP subsystem
void init_arp_system();

// tear down the ARP subsystem and free any nodes
void destroy_arp_system();

// adds an arp entry to the list
//static void _add_arp_entry( uint32_t src_ip, unsigned char *src_mac);
void _add_arp_entry( uint32_t src_ip, unsigned char *src_mac);

// returns a ptr to an arp_cache_entry if the given ip is found in arp table
static struct arp_cache_entry * _get_node_by_ip(uint32_t ip);


/* update the ARP tables entry with src mac address for the given ip, if it exists
 * if it does, update the entry and return 1 to indicate we performed an
 * update. else return 0 indicating no update
 */
static int _update_arp_table(uint32_t ip, unsigned char *mac);

// print the arp table
void print_arp_table();

// process an incoming ARP packet 
void recv_arp( struct eth_hdr *, struct netdev *);


// create an arp response to send out to the netdev
void send_arp(uint32_t, unsigned char *, int, struct netdev *);

