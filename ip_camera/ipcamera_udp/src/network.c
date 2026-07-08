#include "network.h"

#include "xparameters.h"
#include "xil_printf.h"

#include "lwip/init.h"
#include "lwip/netif.h"
#include "lwip/ip_addr.h"
#include "netif/xadapter.h"
#include "lwip/timeouts.h"

struct netif server_netif;

static unsigned char mac_address[] =
{
    0x00,
    0x0A,
    0x35,
    0x00,
    0x1E,
    0x53
};

static ip4_addr_t ipaddr;
static ip4_addr_t netmask;
static ip4_addr_t gateway;

int network_init(void)
{
    xil_printf("Initializing Network...\r\n");

    lwip_init();

    IP4_ADDR(&ipaddr,192,168,1,38);
    IP4_ADDR(&netmask,255,255,255,0);
    IP4_ADDR(&gateway,192,168,1,1);

    if (!xemac_add(&server_netif,
                &ipaddr,
                &netmask,
                &gateway,
                mac_address,
                XPAR_XEMACPS_0_BASEADDR))
    {
        xil_printf("Error: Failed to add Ethernet interface!\r\n");
        return -1;
    }

    netif_set_default(&server_netif);

    netif_set_up(&server_netif);

    xil_printf("Ethernet Interface Up\r\n");    

        xil_printf("lwIP OK\r\n");

        return 0;
}

void network_poll(void)
{
    xemacif_input(&server_netif);
    //sys_check_timeouts();
}