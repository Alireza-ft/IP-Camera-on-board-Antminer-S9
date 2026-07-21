#include "xil_printf.h"
#include "network.h"
#include "udp.h"
#include "vdma.h"
#include "frame_tx.h"

#include <string.h>

int main(void)
{
    xil_printf("Project Start\r\n");

    if(network_init() != 0)
        return -1;

    if(vdma_init() != 0)
        return -1;
    memset((void *)FRAME_BUFFER_ADDR, 0x00, FRAME_WIDTH * FRAME_HEIGHT * BYTES_PER_PIXEL);
        
    if(vdma_start() != 0)
    return -1;

    for(volatile int i = 0; i < 50000000; i++){}


    vdma_dump_framebuffer();
    
    if(udp_socket_init() != 0)
        return -1;
    for(int i = 0; i < 1000; i++)
    {
        network_poll();
    }

    udp_send_test();
    
    //udp_send_frame();

    while(1)
    {
        network_poll();
    }

    return 0;
}