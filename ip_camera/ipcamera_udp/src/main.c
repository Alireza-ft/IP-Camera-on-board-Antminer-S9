#include "xil_printf.h"
#include "network.h"
#include "udp.h"
#include "vdma.h"

int main(void)
{
    xil_printf("Project Start\r\n");

    if(network_init() != 0)
        return -1;

    if(vdma_init() != 0)
        return -1;
            
    if(vdma_start() != 0)
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