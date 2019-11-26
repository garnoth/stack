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
//void netdev_init(char *ip_addr, char *hw_addr)
void netdev_init()
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
    if (dev == NULL) {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }
    // write mac address, fixme write better solution, allow for variable width
    // like 2C:0:40:4... etc
    memcpy(dev->hw_addr, hw_addr, ETH_ADDR_LEN);

    // convert the string ip to bytes
    inet_pton(addr_fam, ip_addr, &dev->ip_addr);

    // write the current ip address length, 4 bytes or 16
    if (addr_fam == AF_INET){

        // convert the ip to bytes but then convert back to host order
        dev->ip_addr = ntohl(dev->ip_addr);

        dev->ip_addr_len = IP_ADDR_LEN_V4; 
    } else {
        // ipv6 case
        // convert the ip to bytes but then convert back to host order
        uint32_t * ip = (uint32_t*) &dev->ip_addr;
        ip[0] = ntohl(ip[0]);
        ip[1] = ntohl(ip[1]);
        ip[2] = ntohl(ip[2]);
        ip[3] = ntohl(ip[3]);

        dev->ip_addr_len = IP_ADDR_LEN_V6;
    }
    // finally write the mtu value
    dev->mtu = mtu;

    return dev;
}

//  fills in the netdev layer items like dst and src mac and
// ethertype fields before writing to the tunnel
int netdev_send( struct gbuf *gbuf, uint8_t *dst_hw, uint16_t ethertype)
{
    return 0;
}

//// return a pointer to the netdev if the given ip matches what we have
//// configured previously. Takes an ip address string
//struct netdev *netdev_get(char * ip)
//{
//    uint32_t search_ip =  ipv4str_to_bytes(ip);
//    return _netdev_get(search_ip);
//}

// return a pointer to the netdev if the given ip matches what we have
// configured previously. Takes a host ordered ip address
struct netdev *netdev_get_self(uint32_t ip)
{
    if ( ip == netdev->ip_addr){
        return netdev;
    } else if ( ip == loopback->ip_addr) {
        return loopback;
    }
    // no matching configured device found, did you accidentally convert
    // the ip to network order before calling this function?
    return NULL;
}

// process recieving a packet, send packets to arp or ip4/6 layer
static int netdev_recv(struct gbuf * gbuf) 
{
    return 0;
}
