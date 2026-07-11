#include "udp.h"

#include "xil_printf.h"

#include "lwip/udp.h"
#include "lwip/pbuf.h"
#include "lwip/ip_addr.h"

#include <string.h>

static struct udp_pcb *pcb;
static ip_addr_t dest_ip;

int udp_socket_init(void)
{
    pcb = udp_new();

   

    if(pcb == NULL)
    {
        xil_printf("UDP Create Failed\r\n");
        return -1;
    }

    xil_printf("UDP PCB Created\r\n");    

    IP4_ADDR(&dest_ip,192,168,1,70);

    xil_printf("Destination IP : %d.%d.%d.%d\r\n",
    ip4_addr1(ip_2_ip4(&dest_ip)),
    ip4_addr2(ip_2_ip4(&dest_ip)),
    ip4_addr3(ip_2_ip4(&dest_ip)),
    ip4_addr4(ip_2_ip4(&dest_ip)));

    err_t err;

    err = udp_connect(pcb,
                    &dest_ip,
                    5001);

    if(err != ERR_OK)
    {
        xil_printf("UDP Connect Failed ,Error code is (%d)\r\n",err);
        return -1;
    }

    xil_printf("UDP Connected\r\n");    
    

    return 0;
}

int udp_send_test(void)
{
    struct pbuf *packet;

    const char message[] = "Hello from Zynq UDP";

    packet = pbuf_alloc(PBUF_TRANSPORT,
                        sizeof(message),
                        PBUF_RAM);

    if(packet == NULL)
    {
        xil_printf("PBUF Allocation Failed\r\n");
        return -1;
    }

    memcpy(packet->payload,
           message,
           sizeof(message));

    err_t err;

    err = udp_send(pcb, packet);
    xil_printf("udp_send() returned = %d\r\n", err);

    if(err != ERR_OK)
    {
        xil_printf("UDP Send Failed\r\n");
        return -1;
    }

    pbuf_free(packet);

    xil_printf("UDP Packet Sent\r\n");

    return 0;
}