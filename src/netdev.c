// filename: netdev.c
// this file creates an ethernet device or nic that talks to the TAP
// this is where we can configure the MAC address and the IP addr will also
// get stored here for lookup by ARP
//

#include "netdev.h"

struct netdev *loopback;
struct netdev *netdev;

// makes calls to setup a loopback device and a basic netdev device
// hardcoded just for the 2 devices atm. loopback may not be needed
void netdev_init(char *ip_addr, char *hw_addr)
{
    // AF_INET or AF_INET6
    int addr_fam = AF_INET;

    // default loopback device config
    unsigned char mac_loop[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    char * loop_ip =    "127.0.0.1";

    // netdev configuration properties
    unsigned char mac_dev[] = {0x34, 0x2C, 0x4A, 0x9A, 0x60, 0x06};
    char * netdev_ip =  "192.168.0.10";


    loopback    = netdev_alloc(loop_ip, mac_loop, ETH_MTU, addr_fam);
    netdev      = netdev_alloc(netdev_ip, mac_dev, ETH_MTU, addr_fam);

}

// setup up the netdev struct when called by init
// and returns a ptr to the allocated memory
static struct netdev *netdev_alloc(char *ip_addr, unsigned char *hw_addr, uint16_t mtu, int addr_fam) 
{
    struct netdev *dev = (struct netdev *) malloc(sizeof(struct netdev));
    // fixme: do we need to guard malloc failures here?
    // write mac address, fixme write better solution, allow for variable width
    // like 2C:0:40:4... etc
    memcpy(dev->hw_addr, hw_addr, ETH_ADDR_LEN);

    // store the ip in network order
    inet_pton(addr_fam, ip_addr, &dev->ip_addr);

    // write the current ip address length, 4 bytes or 16
    if (addr_fam == AF_INET){
        dev->ip_addr_len = IP_ADDR_LEN_V4; 
    } else {
        // ipv6 case
        dev->ip_addr_len = IP_ADDR_LEN_V6;
    }
    // finally write the mtu value
    dev->mtu = mtu;
    
    return dev;
}

//  fills in the netdev layer items like dst and src mac and
// ethertype fields before writing to the tunnel
int netdev_send( struct ifreq *ifr, uint8_t *dst_hw, uint16_t ethertype);

// return a pointer to the netdev if the given ip matches what we have
// configured previously
struct netdev *net_dev_get(uint32_t ip);

// process recieving a packet, send packets to arp or ip4/6 layer
static int netdev_recv(struct ifreq *ifr);
