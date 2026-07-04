#line 2 "lop-config.dts"
/dts-v1/;
/ {
        compatible = "system-device-tree-v1,lop";
        lops {
                lop_0 {
                        compatible = "system-device-tree-v1,lop,load";
                        load = "assists/baremetal_validate_comp_xlnx.py";
                };

                lop_1 {
                    compatible = "system-device-tree-v1,lop,assist-v1";
                    node = "/";
                    outdir = "C:/Users/Arf/Desktop/ip_camera/zynq/IP-Camera-on-board-Antminer-S9/ip_camera/ipcamera_platform/ps7_cortexa9_0/standalone_ps7_cortexa9_0/bsp";
                    id = "module,baremetal_validate_comp_xlnx";
                    options = "ps7_cortexa9_0 E:/xilinx/Vitis/2024.1/data/embeddedsw/ThirdParty/sw_services/lwip220_v1_0/src C:/Users/Arf/Desktop/ip_camera/zynq/IP-Camera-on-board-Antminer-S9/ip_camera/.wsdata/.repo.yaml";
                };

        };
    };
