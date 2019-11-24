#include "arp.c"
int main(int argc, const char* argv[]) {
//setup stuff


//setup TAP


// setup ARP?
//
arp_system_init();
//add_arp_entry( uint32_t src_ip, unsigned char *src_mac)
//38 2c 4a 9b b4 a8
unsigned char mac1[] = {0x31, 0x2C, 0x4A, 0x9B, 0xb4, 0x01};
unsigned char mac2[] = {0x32, 0x2C, 0x4A, 0x9B, 0xb4, 0x02};
unsigned char mac3[] = {0x33, 0x2C, 0x4A, 0x9B, 0xb4, 0x03};
unsigned char mac4[] = {0x34, 0x2C, 0x4A, 0x9B, 0xb4, 0x04};
uint32_t ip1, ip2, ip3, ip4;
char sip1[] = "192.168.0.101";
char sip2[] = "192.168.0.102";
char sip3[] = "192.168.0.5";
char sip4[] = "192.168.0.244";
inet_pton(AF_INET, sip1, &ip1);
inet_pton(AF_INET, sip2, &ip2);
inet_pton(AF_INET, sip3, &ip3);
inet_pton(AF_INET, sip4, &ip4);
//ip1 = ntohl(ip1);
//ip2 = ntohl(ip2);
//ip3 = ntohl(ip3);
//ip4 = ntohl(ip4);
add_arp_entry(ip1, mac1);
add_arp_entry(ip2, mac2);
add_arp_entry(ip3, mac3);
add_arp_entry(ip4, mac4);
// start receiving packets in a loop
print_arp_table();
    return 0;
}
