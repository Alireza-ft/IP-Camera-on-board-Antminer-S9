# IP Camera UDP Application

This application is the software layer of the IP Camera project running on the Zynq Processing System (PS). It is responsible for initializing the Ethernet interface, configuring the Video DMA (VDMA), reading video frames from DDR memory, and transmitting image data over UDP using the lwIP stack.

## Project Structure

```
ipcamera_udp/
├── main.c
├── network.c
├── network.h
├── udp.c
├── udp.h
├── frame_tx.c
├── frame_tx.h
├── vdma.c
├── vdma.h
└── README.md
```

## Modules

### main.c

Application entry point.

Responsibilities:

- Start the application.
- Initialize the network subsystem.
- Initialize the VDMA engine.
- Initialize the UDP transmitter.
- Execute the main polling loop.

---

### network.c / network.h

Responsible for Ethernet and lwIP initialization.

Features:

- Configure static IP address.
- Initialize lwIP stack.
- Register the Ethernet interface.
- Bring the network interface up.
- Monitor link status.
- Process Ethernet packets through polling.
- Print network configuration and diagnostic information.

---

### udp.c / udp.h

Responsible for UDP communication.

Features:

- Create UDP PCB.
- Configure destination IP and port.
- Allocate transmission buffers.
- Send UDP packets.
- Print transmission status and debug information.

---

### frame_tx.c / frame_tx.h

Responsible for frame transmission.

Features:

- Read image data from the frame buffer located in DDR.
- Build UDP payloads.
- Transmit frame data over Ethernet.
- Support future packetization of complete image frames.

---

### vdma.c / vdma.h

Responsible for Video DMA configuration.

Features:

- Initialize AXI VDMA.
- Configure frame buffer addresses.
- Configure frame dimensions and stride.
- Start VDMA in circular mode.
- Verify that video data is being written into DDR memory.

---

## Current Features

- Standalone application
- lwIP RAW API
- Static IPv4 configuration
- Ethernet initialization
- PHY detection
- UDP socket initialization
- UDP packet transmission
- AXI VDMA initialization
- DDR frame buffer access
- UART debug output

---

## Current Status

The software successfully:

- Boots correctly.
- Initializes the Ethernet MAC.
- Detects the PHY.
- Brings the network interface up.
- Initializes lwIP.
- Configures VDMA.
- Reads the frame buffer.
- Creates and connects the UDP PCB.
- Reports successful UDP transmission through the lwIP API.

Packet transmission over the physical Ethernet link is currently under investigation. Additional debugging is focused on Ethernet driver configuration, PHY behavior, hardware design, and packet visibility on the network.

---

## Future Work

- Complete Ethernet transmission verification.
- Implement full frame packetization.
- Optimize UDP throughput.
- Add camera receiver support.
- Support continuous video streaming.
- Add image synchronization and frame numbering.
- Improve error handling and diagnostics.

---

## Target Platform

- Xilinx Zynq-7000
- Vitis 2024.1
- Vivado 2024.1
- lwIP RAW API
- AXI Ethernet
- AXI VDMA
