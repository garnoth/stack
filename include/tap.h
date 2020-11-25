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
#include <unistd.h> //write and close
#include <netinet/if_ether.h>
#include <arpa/inet.h> // htns
#include  <sys/errno.h>
#define MAX_TAP	256
#define PATH_MAX 1024

// file descriptor for the tap device
static int tapfd;

// opens a system tap device. TODO undo hardcoded path
static int _get_tap();

// init the tap device
void init_tap();

// read from the tap device
int read_tap(char *buf, int len);

// write to the tap device
int write_tap(char *buf, int len);

// print the tap information
void print_tap_info();

// clean-up operations for the tap device
void close_tap();
