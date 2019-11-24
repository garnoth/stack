#include "tap.h"
#include "tools.h"

static int tapfd;
// static char* dev; // needed later when we plumb in the name

// try to open /dev/tap0
// plumb in optional name and non-hardcoded value later 
// i.e. tap2 or something
static int get_tap()
{
    int fd;
    char * path = "/dev/tap0";
    fd = open(path, O_RDWR | O_NONBLOCK);
    if (fd != -1) {
        return (fd);
    }

    return (-1);
}

// init the tunnel by calling the get_tap function
void tap_init()
{
    tapfd = get_tap();
    if (tapfd < 0) {
        perror("error: could not get tap device");
        exit(EXIT_FAILURE);    
    }
}

int tap_read(char *buf, int len)
{
    return read(tapfd, buf, len);
}

int tap_write(char *buf, int len) 
{
    return write(tapfd, buf, len);
}

// fixme: clean up this shit
void print_tap_info()
{
    struct tuninfo *tinfo = NULL;
    tinfo = (struct tuninfo *)malloc(sizeof(struct tuninfo)); 
    if (ioctl(tapfd, TUNGIFINFO, tinfo) < 0) {
        printf("Getting tunnel info failed \n");
    }
    if (tinfo != NULL) {
        print_tuninfo(tinfo);
    }
    free(tinfo);
}

// for any clean-up later on
void tap_destroy() 
{
    //    free (dev);
}

