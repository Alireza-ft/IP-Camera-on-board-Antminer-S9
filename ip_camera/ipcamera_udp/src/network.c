#include "network.h"

#include "xparameters.h"
#include "xil_printf.h"
#include "xemacps.h"
#include "sleep.h"

#include "lwip/init.h"
#include "lwip/netif.h"
#include "lwip/ip_addr.h"
#include "netif/xadapter.h"
#include "lwip/timeouts.h"

#include "platform.h"

struct netif server_netif;
static XEmacPs eth_instance;

static unsigned char mac_address[] = { 0x00, 0x0A, 0x35, 0x00, 0x1E, 0x53 };

static ip4_addr_t ipaddr;
static ip4_addr_t netmask;
static ip4_addr_t gateway;

#define PHY_ADDR              1
#define PHY_REG_CONTROL       0
#define PHY_REG_STATUS        1
#define AUTONEG_COMPLETE_BIT  (1 << 5)
#define LINK_STATUS_BIT       (1 << 2)

static int wait_for_phy_autoneg(u32 timeout_ms)
{
    u16_t status_reg = 0;
    u32 elapsed_ms = 0;
    const u32 poll_interval_ms = 100;

    xil_printf("[DEBUG] Waiting for real PHY autonegotiation...\r\n");

    while (elapsed_ms < timeout_ms)
    {
        XEmacPs_PhyRead(&eth_instance, PHY_ADDR, PHY_REG_STATUS, &status_reg);

        if (status_reg & AUTONEG_COMPLETE_BIT)
        {
            xil_printf("[DEBUG] PHY autonegotiation COMPLETE after %u ms | StatusReg=%04X | LinkUp=%d\r\n",
                       elapsed_ms, status_reg, (status_reg & LINK_STATUS_BIT) ? 1 : 0);
            return 1;
        }

        usleep(poll_interval_ms * 1000);
        elapsed_ms += poll_interval_ms;

        if (elapsed_ms % 1000 == 0)
        {
            xil_printf("[DEBUG] ... still waiting (%u ms), StatusReg=%04X\r\n", elapsed_ms, status_reg);
        }
    }

    xil_printf("[DEBUG] PHY autonegotiation TIMEOUT after %u ms | Last StatusReg=%04X\r\n",
               timeout_ms, status_reg);
    return 0;
}


int network_init(void)
{
    xil_printf("[DEBUG] === network_init start ===\r\n");

    platform_init();
    xil_printf("[DEBUG] platform_init() done\r\n");

    lwip_init();
    xil_printf("[DEBUG] lwip_init() done\r\n");

    IP4_ADDR(&ipaddr, 192,168,1,38);
    IP4_ADDR(&netmask, 255,255,255,0);
    IP4_ADDR(&gateway, 192,168,1,1);

    xil_printf("[DEBUG] Before xemac_add\r\n");

    if (!xemac_add(&server_netif, &ipaddr, &netmask, &gateway,
                   mac_address, XPAR_XEMACPS_0_BASEADDR))
    {
        xil_printf("[DEBUG] Error: xemac_add FAILED\r\n");
        return -1;
    }
    xil_printf("[DEBUG] xemac_add OK\r\n");

   if (!wait_for_phy_autoneg(5000))
    {
        xil_printf("[DEBUG] WARNING: proceeding despite autoneg timeout - link will likely not work\r\n");
    }
    

    platform_enable_interrupts();
    xil_printf("[DEBUG] platform_enable_interrupts() done\r\n");

    xil_printf("MAC = %02X:%02X:%02X:%02X:%02X:%02X\r\n",
        server_netif.hwaddr[0], server_netif.hwaddr[1], server_netif.hwaddr[2],
        server_netif.hwaddr[3], server_netif.hwaddr[4], server_netif.hwaddr[5]);

    netif_set_default(&server_netif);
    netif_set_up(&server_netif);

    xil_printf("Ethernet Link %s\r\n", netif_is_link_up(&server_netif) ? "UP" : "DOWN");
    xil_printf("Netif flags = %02X\r\n", server_netif.flags);

    xil_printf("IP Address : %d.%d.%d.%d\r\n",
        ip4_addr1(&ipaddr), ip4_addr2(&ipaddr), ip4_addr3(&ipaddr), ip4_addr4(&ipaddr));

    XEmacPs_Config *Cfg = XEmacPs_LookupConfig(XPAR_XEMACPS_0_BASEADDR);
    XEmacPs_CfgInitialize(&eth_instance, Cfg, Cfg->BaseAddress);

    xil_printf("[DEBUG] === network_init end ===\r\n");

    return 0;
}

void network_poll(void)
{
    static int cnt = 0;
    cnt++;

    if (cnt % 100000 == 0)
    {
        xil_printf("[DEBUG] poll #%d | Netif flags=%02X | LinkUp=%d\r\n",
                   cnt, server_netif.flags, netif_is_link_up(&server_netif));
    }

    xemacif_input(&server_netif);
    //sys_check_timeouts();
}

void network_debug_dump(void)
{
    u16_t phy_reg;

    xil_printf("\r\n[DEBUG] ===== ETHERNET FULL STATUS =====\r\n");

    u32 nwcfg = XEmacPs_ReadReg(XPAR_XEMACPS_0_BASEADDR, XEMACPS_NWCFG_OFFSET);
    xil_printf("[DEBUG] NWCFG    = %08X | Speed100/1000=%d FullDuplex=%d\r\n",
               nwcfg, (nwcfg >> 10) & 1, (nwcfg >> 8) & 1);

    u32 nwsr = XEmacPs_ReadReg(XPAR_XEMACPS_0_BASEADDR, XEMACPS_NWSR_OFFSET);
    xil_printf("[DEBUG] NWSR     = %08X\r\n", nwsr);

    XEmacPs_PhyRead(&eth_instance, 1, 0, &phy_reg);
    xil_printf("[DEBUG] PHY Reg0 (Control)      = %04X | AutoNegEnable=%d Reset=%d\r\n",
               phy_reg, (phy_reg >> 12) & 1, (phy_reg >> 15) & 1);

    XEmacPs_PhyRead(&eth_instance, 1, 1, &phy_reg);
    xil_printf("[DEBUG] PHY Reg1 (Status)       = %04X | AutoNegComplete=%d LinkUp=%d\r\n",
               phy_reg, (phy_reg >> 5) & 1, phy_reg & 4 ? 1 : 0);

    XEmacPs_PhyRead(&eth_instance, 1, 4, &phy_reg);
    xil_printf("[DEBUG] PHY Reg4 (AutoNeg Adv)  = %04X\r\n", phy_reg);

    XEmacPs_PhyRead(&eth_instance, 1, 5, &phy_reg);
    xil_printf("[DEBUG] PHY Reg5 (LinkPartner)  = %04X\r\n", phy_reg);

    XEmacPs_PhyRead(&eth_instance, 1, 9, &phy_reg);
    xil_printf("[DEBUG] PHY Reg9 (1000T Ctrl)   = %04X\r\n", phy_reg);

    XEmacPs_PhyRead(&eth_instance, 1, 10, &phy_reg);
    xil_printf("[DEBUG] PHY Reg10 (1000T Status)= %04X | LP1000FullDuplex=%d\r\n",
               phy_reg, (phy_reg >> 11) & 1);               

    
    xil_printf("[DEBUG] TX Octets Low  = %08X\r\n",
        XEmacPs_ReadReg(XPAR_XEMACPS_0_BASEADDR, 0x100));
    xil_printf("[DEBUG] TX Frames OK   = %08X\r\n",
        XEmacPs_ReadReg(XPAR_XEMACPS_0_BASEADDR, 0x118));
    xil_printf("[DEBUG] TX Errors      = %08X\r\n",
        XEmacPs_ReadReg(XPAR_XEMACPS_0_BASEADDR, 0x170));

   
    xil_printf("[DEBUG] RX Frames OK   = %08X\r\n",
        XEmacPs_ReadReg(XPAR_XEMACPS_0_BASEADDR, XEMACPS_RXCNT_OFFSET));
    xil_printf("[DEBUG] RX FCS Errors  = %08X\r\n",
        XEmacPs_ReadReg(XPAR_XEMACPS_0_BASEADDR, XEMACPS_RXRESERRCNT_OFFSET));
    xil_printf("[DEBUG] RX Resource Err= %08X\r\n",
        XEmacPs_ReadReg(XPAR_XEMACPS_0_BASEADDR, XEMACPS_RXRESERRCNT_OFFSET));
    xil_printf("[DEBUG] ==================================\r\n\r\n");
}