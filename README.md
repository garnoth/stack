# Lego Stack
 This is my first attempt and writing a TCP/IP stack from the ground up
## Getting started
 development is currently setup for a TAP device on an OpenBSD system
 other OS/s will be added later. Writing this for IPv4 but trying to do some groundwork for adding in IPv6 later

### Running
    Currently my highly complex builds script is called BA for build all

## Preconditions
 currently I'm not sure how to allow users to create a tap device on the fly
 so right now I'm creating tap6 which doesn't exist by default
###
cd /dev
mknod -m 666 tap6 c 93 6
##
 as root to allow normal users who run this program to open the tap device
 hopefully there is an easier way in the future
