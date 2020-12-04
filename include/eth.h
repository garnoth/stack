#pragma once
//pre-defined ethertype values
#define ETHERTYPE_ARP   0x0806
#define ETHERTYPE_IP    0x0800
#define ETHERTYPE_IPV6  0x86DD

#define ETH_ADDR_LEN    0x0006 // 6 bytes for hw address
#define ETH_MTU         0x1500 // default ethernet mtu

#define ETH_HDR_LEN 14
// ethernet header: 12 bytes + 2 for type
// 14 total bytes. The types we will need to use:
// ETHERTYPE_ARP ETHERTYPE_IP
struct eth_hdr
{
    unsigned char dst_mac[ETH_ADDR_LEN];
    unsigned char src_mac[ETH_ADDR_LEN];
    uint16_t ethertype;
    unsigned char payload[];
} __attribute__((packed));

