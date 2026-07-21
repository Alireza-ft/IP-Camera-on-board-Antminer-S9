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

  

    xil_printf("Before xemac_add\r\n");    
    
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

    xil_printf("MAC = %02X:%02X:%02X:%02X:%02X:%02X\r\n",
        server_netif.hwaddr[0],
        server_netif.hwaddr[1],
        server_netif.hwaddr[2],
        server_netif.hwaddr[3],
        server_netif.hwaddr[4],
        server_netif.hwaddr[5]);

    xil_printf("HWADDR_LEN = %d\r\n", server_netif.hwaddr_len);
    
    xil_printf("After xemac_add\r\n");

    netif_set_default(&server_netif);

    netif_set_up(&server_netif);

    if (netif_is_link_up(&server_netif))
    {
        xil_printf("Ethernet Link UP\r\n");
    }

    
    else
    {
        xil_printf("Ethernet Link DOWN\r\n");
    }    

    xil_printf("Ethernet Interface Up\r\n");
    xil_printf("Netif flags = %02X\r\n", server_netif.flags);        

    xil_printf("lwIP OK\r\n");

    
    xil_printf("IP Address : %d.%d.%d.%d\r\n",
        ip4_addr1(&ipaddr),
        ip4_addr2(&ipaddr),
        ip4_addr3(&ipaddr),
        ip4_addr4(&ipaddr));

    xil_printf("Gateway    : %d.%d.%d.%d\r\n",
        ip4_addr1(&gateway),
        ip4_addr2(&gateway),
        ip4_addr3(&gateway),
        ip4_addr4(&gateway));

    
    return 0;
}

void network_poll(void)
{
    static int cnt = 0;

    cnt++;

    if(cnt % 100000 == 0)
    {
        xil_printf("poll\r\n");
        xil_printf("Netif flags = %02X\r\n", server_netif.flags);
    }

    xemacif_input(&server_netif);
    //sys_check_timeouts();
}