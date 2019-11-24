#include "include/system_headers.h"
#include "include/eth.h"
#include "include/arp.h"
#include <arpa/inet.h> // htns

void print_eth_hdr(struct eth_hdr *e)
{
    int i;

    printf("d_mac: ");
    for (i = 0; i < ETHER_ADDR_LEN; i++) {
        printf( "%X",e->dst_mac[i]);
    }
    printf("\n s_mac: ");
    for (i = 0; i < ETHER_ADDR_LEN; i++) {
        printf( "%X",e->src_mac[i]);
    }
    printf("\n");
    printf("ethertype: 0x%X \n", ntohs(e->ethertype));
}
const uint8_t etherbroadcastaddr[] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };
const uint8_t etherzeroaddr[] = { 0, 0, 0, 0, 0, 0 };


// this function gets and stores the interfaces source mac address
// for quick access later
void ether_init()
{
    struct sockaddr sa;

    struct ether_header e;
    int i;
    short prot_id = ETHERTYPE_ARP;

    memset(e.dst_mac, 0, sizeof(e.dst_mac));
    memset(e.src_mac, 0, sizeof(e.ether_shost));

    printf("My dmac address is: %X\n", e.dst_mac);
    printf("My smac address is: %X\n", e.src_mac);
    //    strlcpy(ifr.ifr_name, ifname, sizeof(ifr.ifr_name));

    if (ioctl(*tapfd,SIOCGIFADDR,&e.src_mac) == -1) {
        perror("Getting MAC address failed!");        
    } else {
        for (i = 0; i < ETHER_ADDR_LEN; i++ ){
            e.dst_mac[i] = 255;
        }
        //const unsigned char* smac = (unsigned char*)*src_addr;
    }
    e.ethertype = 0+htons(ETHERTYPE_ARP);
    print_eth_hdr(&e);


    //  ifr.ifr_data = (caddr_t)vfr.vfr_value
    ///           if (ioctl(env->vmd_fd, SIOCSIFDESCR, &ifr) < 0) 
    //             perror("failed to SIOCSIFDESCR");

    write(*tapfd, &e, sizeof(e));
    return 0;
}
