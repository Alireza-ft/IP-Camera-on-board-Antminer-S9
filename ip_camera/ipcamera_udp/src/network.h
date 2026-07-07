#ifndef NETWORK_H
#define NETWORK_H

#include "lwip/netif.h"

extern struct netif server_netif;

int network_init(void);
void network_poll(void);

#endif