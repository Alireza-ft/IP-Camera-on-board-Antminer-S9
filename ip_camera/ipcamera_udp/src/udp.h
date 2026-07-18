#ifndef UDP_H
#define UDP_H

#include "lwip/err.h"
#include <arch/cc.h>

int udp_socket_init(void);
int udp_send_test(void);
int udp_send_packet(void *data, u16_t length);

#endif