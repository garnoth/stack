#include "eth.h"
#include <net/if_tun.h>

char * byte2str(int );
char dec_to_hexii(uint8_t);
void mac_to_string(char *, unsigned char*);
void print_tuninfo(struct tuninfo*);
void print_eth_hdr(struct eth_hdr*);
uint32_t ipv4str_to_bytes(char *);
