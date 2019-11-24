#include <sys/socket.h>
#include <sys/types.h>
#include <net/if_tun.h>
#include <net/ethertypes.h>
#include <net/if_arp.h>
#include <net/if.h>
#include <fcntl.h> // open
#include <stdlib.h> // exit
#include <string.h> // for memset
#include <sys/ioctl.h>
#include <poll.h>
#include <errno.h>
#include <signal.h>
#include <assert.h>
#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <netinet/in.h> // has struct sin_addr
#include <unistd.h> //write
#include <netinet/if_ether.h>
#include <arpa/inet.h> // htns

#define MAX_TAP	256
#define PATH_MAX 1024
#define ETH_ADDR_SIZE 6

static int get_tap();
void tap_init();
int tap_read(char *buf, int len);
int tap_write(char *buf, int len);
void print_tap_info();
void tap_destroy();
