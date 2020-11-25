#include "tap.h"
#include "arp.h"
#include "eth.h"
#include "netdev.h"

static void start_up()
{
    init_tap();
    init_netdev();
    init_arp_system();
}

int main() 
{
start_up();

close_tap();
    return 0;
}
