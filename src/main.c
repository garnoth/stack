#include "tap.h"
#include "arp.h"
#include "eth.h"

static void start_up()
{
    tap_init();
    arp_system_init();
}

int main() 
{
start_up();

tap_close();
    return 0;
}
