#include "network.h"

#include "xparameters.h"
#include "xil_printf.h"

#include "lwip/init.h"
#include "lwip/netif.h"
#include "lwip/ip_addr.h"
#include "netif/xadapter.h"

struct netif server_netif;

static unsigned char mac_address[] =
{
    0x00,
    0x0A,
    0x35,
    0x00,
    0x01,
    0x02
};

ip4_addr_t ipaddr;
ip4_addr_t netmask;
ip4_addr_t gateway;

int network_init(void)
{
    xil_printf("Initializing Network...\r\n");

    lwip_init();

    IP4_ADDR(&ipaddr,192,168,1,10);
    IP4_ADDR(&netmask,255,255,255,0);
    IP4_ADDR(&gateway,192,168,1,1);



    xil_printf("lwIP OK\r\n");

    return 0;
}