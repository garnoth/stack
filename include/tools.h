#include "eth.h"
#include <net/if_tun.h>

// print a byte TODO doesn't this leak like a sieve?
char * byte2str(int );

// ASCII table hack for reporting hex values for nibbles
char dec_to_hexii(uint8_t);

// returns a string representation of the passed in MAC address
void mac_to_string(char *, unsigned char*);

// print tun info to stdout
void print_tuninfo(struct tuninfo*);

// print an eth header to stdout
void print_eth_hdr(struct eth_hdr*);

// convert an ipv4 address to it's 4 byte equiv
uint32_t ipv4str_to_bytes(char *);
