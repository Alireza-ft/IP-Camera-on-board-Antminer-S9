#include "vdma.h"

#include "xparameters.h"
#include "xaxivdma.h"
#include "xil_printf.h"

static XAxiVdma Vdma;

int vdma_init(void)
{
    XAxiVdma_Config *Config;
    int Status;

    Config = XAxiVdma_LookupConfig(XPAR_AXIVDMA_0_DEVICE_ID);

    if (Config == NULL)
    {
        xil_printf("ERROR: VDMA config not found\r\n");
        return XST_FAILURE;
    }

    Status = XAxiVdma_CfgInitialize(
                &Vdma,
                Config,
                Config->BaseAddress);

    if (Status != XST_SUCCESS)
    {
        xil_printf("ERROR: VDMA init failed\r\n");
        return XST_FAILURE;
    }

    xil_printf("VDMA Initialized\r\n");

    return XST_SUCCESS;
}