#include "system_headers.h"
#include "arp.h"
#include <sys/queue.h> // for linked list
#include <arpa/inet.h>
#include <sys/socket.h> // for inet_pton
#include <stdio.h>

// the arp table head entry

// linked list of nodes holding arp_cache_entries
struct arp_cache_node
{
    struct arp_cache_entry entry;
    SLIST_ENTRY(arp_cache_node) nodes;
};

// This macro creates the data type for the head of the list
SLIST_HEAD(head_s, arp_cache_node) head;

// init the arp system. Create the arp_table linked list head entry
void init_arp_system()
{
    // init the head before use
    SLIST_INIT(&head);
}

// adds to the front of the list
// does not check for duplicates first
///static void _add_arp_entry( uint32_t src_ip, unsigned char *src_mac) 
void _add_arp_entry( uint32_t src_ip, unsigned char *src_mac) 
{
    struct arp_cache_node * e = NULL;
    e = malloc(sizeof(struct arp_cache_node));
    if (e == NULL)
    {
        fprintf(stderr, "malloc failed");
        exit(EXIT_FAILURE);
    }
    // copy in the ip address
    e->entry.src_ip = src_ip;

    // copy in the MAC address
    memcpy(e->entry.src_mac, src_mac, ETH_ADDR_LEN);
    e->entry.resolved = 0; 
    SLIST_INSERT_HEAD(&head, e, nodes);
    e = NULL;
}

// returns a ptr to an arp_cache_entry if the given ip is found in arp table
static struct arp_cache_entry * _get_node_by_ip(uint32_t ip) 
{
    struct arp_cache_node * e = NULL;
    SLIST_FOREACH(e,&head, nodes)
    {
        if (e->entry.src_ip == ip)    
            return &e->entry;
    }
    fprintf(stderr, "DEBUG WARNING, var \"ip\" called with a null value!");
    return NULL;
}


/* update the ARP tables entry with src mac address for the given ip, if it exists
 * if it does, update the entry and return 1 to indicate we performed an
 * update. else return 0 indicating no update
 */
static int _update_arp_table(uint32_t ip, unsigned char *mac)
{
    struct arp_cache_entry * e = _get_node_by_ip(ip);
    if (e != NULL){
        // update the senders mac addr for this ip
        memcpy(e->src_mac, mac, ETH_ADDR_LEN);
        return 1;
    }
    return 0;
}

// print the arp table
void print_arp_table() 
{
    fprintf(stdout,"Host\t\t\tEthernet Address\tNetDev\n");
    struct arp_cache_node * e = NULL;
    char ip_str[INET_ADDRSTRLEN];
    char * str = (char*)malloc(18);//what why this much?
    SLIST_FOREACH(e,&head, nodes)
    {
        inet_ntop(AF_INET, &e->entry.src_ip, ip_str, INET_ADDRSTRLEN);
        fprintf(stdout, "%s\t\t", ip_str);
        mac_to_string(str, e->entry.src_mac);
        fprintf(stdout, "%s\n", str);
    }
    free(str);
}

// the main processing algorithm for reciving arp packets
// follows RFC826 as best I can follow. This is my first reading of an RFC for 
// writing code to implement it
void recv_arp( struct eth_hdr * eth_header, struct netdev * device)
{
    // create 2 structs for decoding the received packet
    struct arp_hdr *arp_header = (struct arp_hdr*)eth_header->payload;

    struct arp_ipv4 *arp_ipv4 = (struct arp_ipv4*)arp_header->data;
    int merge;

    // pointless checks but part of the RFC
    // hwtype == 1; hwsize == 6
    if ((ntohs(arp_header->hwtype) == ARP_HRD_ETH ) && 
            (arp_header->hwsize == ETH_ADDR_LEN)) {
        if (ntohs(arp_header->protype) == ETHERTYPE_IP) { // only process ipv4 arp
            // the merge flag comes from the RFC
            merge = _update_arp_table(ntohl(arp_ipv4->src_ip), arp_ipv4->src_mac);
            device = get_netdev_self(ntohl(arp_ipv4->dst_ip));
            if (device != NULL) {
                // the dst_ip matches my IP. i.e., I am the dst
                if (!merge) { // merge flag is false, add the triplett
                    _add_arp_entry(ntohl(arp_ipv4->src_ip), arp_ipv4->src_mac);
                }
                if (arp_header->opcode == ARP_REQUEST) {
                    // send a reply packet swapping dst and src fields
                    send_arp(ntohl(arp_ipv4->src_ip), arp_ipv4->src_mac, ARP_REPLY, device);
                }
            } // I wasn't the dst_ip, skip further processing
        } else {
            printf("Error: prototype unsupported: %x\n",ntohs(arp_header->protype));
        }
    } else {
        printf("Error: bad hwtype or hwsize: %x %x\n",ntohs(arp_header->hwtype),
                arp_header->hwsize);
    }
}

// create an arp response to send out to the netdev
void send_arp(uint32_t dst_ip, unsigned char * dst_mac, int opcode, struct netdev * device)
{
    struct arp_hdr *arp_header = (struct arp_hdr*)malloc(sizeof(struct arp_hdr));
    struct arp_ipv4 *arp_ipv4 = (struct arp_ipv4*)malloc(sizeof(struct arp_ipv4));
    // fill in the arp_hdr fields
    arp_header->hwtype = htons(ARP_HRD_ETH);
    arp_header->protype = htons(ETHERTYPE_IP);
    arp_header->hwsize = ETH_ADDR_LEN;
    arp_header->prosize = ARP_IP_ADDR_LEN;
    arp_header->opcode = htons(opcode); 

    // fill in the arp_ipv4 fields
    memcpy(arp_ipv4->src_mac, &device->hw_addr , ETH_ADDR_LEN);
    arp_ipv4->src_ip = htonl(device->ip_addr); 
    memcpy(arp_ipv4->dst_mac, dst_mac , ETH_ADDR_LEN);
    arp_ipv4->dst_ip = htonl(dst_ip);

    // create an IFR to pass to the netdev
    // write out packet 
    //    int netdev_send( struct ifreq *ifr, dst_mac, ETHERTYPE_IP);
}
