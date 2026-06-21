##========================
## OV7670 DATA BUS
##========================

set_property PACKAGE_PIN U18 [get_ports {d_0[0]}]
set_property PACKAGE_PIN Y18 [get_ports {d_0[1]}]
set_property PACKAGE_PIN U19 [get_ports {d_0[2]}]
set_property PACKAGE_PIN U15 [get_ports {d_0[3]}]
set_property PACKAGE_PIN T20 [get_ports {d_0[4]}]
set_property PACKAGE_PIN V20 [get_ports {d_0[5]}]
set_property PACKAGE_PIN W20 [get_ports {d_0[6]}]
set_property PACKAGE_PIN U20 [get_ports {d_0[7]}]

set_property IOSTANDARD LVCMOS33 [get_ports {d_0[0]}]
set_property IOSTANDARD LVCMOS33 [get_ports {d_0[1]}]
set_property IOSTANDARD LVCMOS33 [get_ports {d_0[2]}]
set_property IOSTANDARD LVCMOS33 [get_ports {d_0[3]}]
set_property IOSTANDARD LVCMOS33 [get_ports {d_0[4]}]
set_property IOSTANDARD LVCMOS33 [get_ports {d_0[5]}]
set_property IOSTANDARD LVCMOS33 [get_ports {d_0[6]}]
set_property IOSTANDARD LVCMOS33 [get_ports {d_0[7]}]

##========================
## SYNC SIGNALS
##========================

set_property PACKAGE_PIN U14 [get_ports {pclk_0}]
set_property PACKAGE_PIN V16 [get_ports {vsync_0}]
set_property PACKAGE_PIN W16 [get_ports {href_0}]

set_property IOSTANDARD LVCMOS33 [get_ports {pclk_0}]
set_property IOSTANDARD LVCMOS33 [get_ports {vsync_0}]
set_property IOSTANDARD LVCMOS33 [get_ports {href_0}]

##========================
## CAMERA CLOCK
##========================

set_property PACKAGE_PIN Y19 [get_ports {xclk_0}]
set_property IOSTANDARD LVCMOS33 [get_ports {xclk_0}]

##========================
## SCCB / I2C
##========================

set_property PACKAGE_PIN J18 [get_ports {siod_0}]
set_property PACKAGE_PIN H20 [get_ports {sioc_0}]

set_property IOSTANDARD LVCMOS33 [get_ports {siod_0}]
set_property IOSTANDARD LVCMOS33 [get_ports {sioc_0}]