#include "vdma.h"

#include "xparameters.h"
#include "xaxivdma.h"
#include "xil_printf.h"

#include <string.h>

static XAxiVdma Vdma;

int vdma_start(void)
{
    XAxiVdma_DmaSetup Setup;
    UINTPTR BufferAddr;
    int Status;

    memset(&Setup, 0, sizeof(Setup));

    Setup.VertSizeInput = FRAME_HEIGHT;
    Setup.HoriSizeInput = FRAME_WIDTH * BYTES_PER_PIXEL;
    Setup.Stride = FRAME_STRIDE;

    Setup.FrameDelay = 0;

    Setup.EnableCircularBuf = 1;
    Setup.EnableSync = 0;
    Setup.PointNum = 0;
    Setup.EnableFrameCounter = 0;
    Setup.FixedFrameStoreAddr = 0;

    Status = XAxiVdma_DmaConfig(
                &Vdma,
                XAXIVDMA_WRITE,
                &Setup);

    if(Status != XST_SUCCESS)
    {
        xil_printf("VDMA Config Failed\r\n");
        return XST_FAILURE;
    }

    BufferAddr = FRAME_BUFFER_ADDR;

    Status = XAxiVdma_DmaSetBufferAddr(
                &Vdma,
                XAXIVDMA_WRITE,
                &BufferAddr);

    if(Status != XST_SUCCESS)
    {
        xil_printf("VDMA Buffer Failed\r\n");
        return XST_FAILURE;
    }

    Status = XAxiVdma_DmaStart(
                &Vdma,
                XAXIVDMA_WRITE);

    if(Status != XST_SUCCESS)
    {
        xil_printf("VDMA Start Failed\r\n");
        return XST_FAILURE;
    }

    xil_printf("VDMA Started\r\n");

    return XST_SUCCESS;
}

void vdma_dump_framebuffer(void)
{
    volatile unsigned int *ptr = (volatile unsigned int *)FRAME_BUFFER_ADDR;

    xil_printf("Frame Buffer:\r\n");

    for(int i = 0; i < 16; i++)
    {
        xil_printf("%08X\r\n", ptr[i]);
    }
}

int vdma_init(void)
{
    XAxiVdma_Config *Config;
    int Status;

    Config = XAxiVdma_LookupConfig(XPAR_XAXIVDMA_0_BASEADDR);

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