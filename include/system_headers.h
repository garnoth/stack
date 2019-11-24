#include <sys/socket.h>
#include <sys/types.h>
#include <net/if_tun.h>
#include <net/ethertypes.h>
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
#include <unistd.h> //write
#include <stdint.h> //uint16_t ..etc
