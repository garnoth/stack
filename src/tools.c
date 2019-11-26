#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <net/if_tun.h>
#include <net/if.h>
#include <arpa/inet.h>
#include "tools.h"

// good for debugging, inspired from stackoverflow
char * byte2str(int i)
{
    size_t bits = CHAR_BIT;

    char * str = malloc(bits + 1);
    if(!str) return NULL;
    str[bits] = '\0';

    // type punning because signed shift is implementation-defined
    unsigned char u = *(unsigned char *)&i;
    for(; bits--; u >>= 1){
        str[bits] = u & 1 ? '1' : '0';
 printf("bits: %zu\n",bits);
    }
 printf("final bits: %zu\n",bits);
    return str;
}


// ASCII table hack to report hex values for nibbles
// the 55 offset is to use upper case
char dec_to_hexii(uint8_t val) {
    if (val > 9 ) {
        return val + 55;
    } else {
        return val + 48;
    }
}

// this function takes a ptr to a string and writes in the mac address
// from the given pointer
void mac_to_string(char * str, unsigned char* mac) {
    uint8_t i, j;
    j = 0;
    for (i = 0; i < ETH_ADDR_LEN; i++) {
        // shift the upper 4 bits right so we just get them
        str[j++] = dec_to_hexii(mac[i] >> 4); 
        // mask off the upper 4 bits so we just get the lower 4
        str[j++] = dec_to_hexii(mac[i] & 0x0F); 
        str[j++] = ':'; 
    }
    // backtrack once and null terminate the final semicolon
    str[--j] = '\0';
}


void print_tuninfo(struct tuninfo *t)
{
    printf("mtu:   %d \n", t->mtu);
    printf("type:  %d \n", t->type);
    printf("flags: %d \n", t->flags);
    printf("baud:  %d \n", t->baudrate);

}

//void print_ifreq(struct ifreq *ifr)
//{
//    printf("data: %x\n", ifr);
//
//}

void print_eth_hdr(struct eth_hdr *e)
{
    int i;

    printf("d_mac: ");
    for (i = 0; i < ETH_ADDR_LEN; i++) {
    printf( "%X",e->dst_mac[i]);
    }
    printf("\n s_mac: ");
    for (i = 0; i < ETH_ADDR_LEN; i++) {
    printf( "%X",e->src_mac[i]);
    }
    printf("\n");
    printf("ethertype: 0x%X \n", ntohs(e->ethertype));
}

// convert an IPv4 string into it's 4 byte equiv, host order
uint32_t ipv4str_to_bytes(char * ip)
{
    uint32_t ret_ip;
    inet_pton(AF_INET, ip, &ret_ip);
    return ntohl(ret_ip);
}
