#include "tap.h"
#include "tools.h"

// static char* dev; // needed later when we plumb in the name

// try to open /dev/tap6
// this must have been previously created
// plumb in optional name and non-hardcoded value later 
// i.e. tap2 or something
static int _get_tap()
{
    int fd;
    char * path = "/dev/tap6";
    fd = open(path, O_RDWR | O_NONBLOCK);
    if (fd != -1) {
        printf("Successfully opened %s\n", path);
        return (fd);
    }
    printf("Failed to open tap device: %s\n", path);
    return (-1);
}

// init the tunnel by calling the get_tap function
void init_tap()
{
    tapfd = _get_tap();
    if (tapfd < 0) {
    perror("Error:");
        exit(EXIT_FAILURE);    
    }
}

int read_tap(char *buf, int len)
{
    return read(tapfd, buf, len);
}

int write_tap(char *buf, int len) 
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

// clean-up operations for the tap device
void close_tap()
{
    close(tapfd);
}

