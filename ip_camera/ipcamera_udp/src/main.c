#include "xil_printf.h"
#include "network.h"

int main(void)
{
    xil_printf("Project Start\r\n");

    network_init();

    while(1)
    {

    }

    return 0;
}