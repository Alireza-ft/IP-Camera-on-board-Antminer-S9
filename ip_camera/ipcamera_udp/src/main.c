#include "xil_printf.h"
#include "network.h"
#include "udp.h"

int main(void)
{
    

    xil_printf("Project Start\r\n");

    if(network_init() != 0)
        return -1;

    if(udp_socket_init() != 0)
        return -1;

    udp_send_test();

    while(1)
    {
        network_poll();
    }

    return 0;
}