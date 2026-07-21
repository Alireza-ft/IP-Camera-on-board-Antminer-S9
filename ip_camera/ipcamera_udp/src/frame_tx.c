#include "frame_tx.h"

#include "vdma.h"
#include "xil_printf.h"
#include "xil_cache.h"

#include <stdint.h>

int udp_send_frame(void)
{
    uint8_t *frame = (uint8_t *)FRAME_BUFFER_ADDR;

    uint32_t frame_size =
            FRAME_WIDTH *
            FRAME_HEIGHT *
            BYTES_PER_PIXEL;

    uint32_t offset = 0;

    xil_printf("Sending Frame...\r\n");
    


        
    while(offset < frame_size)
    {
        uint32_t packet_size = UDP_PAYLOAD_SIZE;

        if((frame_size - offset) < UDP_PAYLOAD_SIZE)
            packet_size = frame_size - offset;

        xil_printf("Packet Offset=%u Size=%u\r\n",
                   offset,
                   packet_size);

        if(udp_send_packet(frame + offset, packet_size) != 0)
        {
            xil_printf("Packet Send Failed\r\n");
            return -1;
        }


        offset += packet_size;
    }

    Xil_DCacheFlushRange(FRAME_BUFFER_ADDR, frame_size);
        
    xil_printf("Frame Finished\r\n");

    return 0;
}