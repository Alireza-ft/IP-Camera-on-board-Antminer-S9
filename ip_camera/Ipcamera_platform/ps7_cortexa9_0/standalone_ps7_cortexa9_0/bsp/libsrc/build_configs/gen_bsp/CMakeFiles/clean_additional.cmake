# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "")
  file(REMOVE_RECURSE
  "C:\\Users\\Arf\\Desktop\\ip_camera\\zynq\\IP-Camera-on-board-Antminer-S9\\ip_camera\\Ipcamera_platform\\ps7_cortexa9_0\\standalone_ps7_cortexa9_0\\bsp\\include\\sleep.h"
  "C:\\Users\\Arf\\Desktop\\ip_camera\\zynq\\IP-Camera-on-board-Antminer-S9\\ip_camera\\Ipcamera_platform\\ps7_cortexa9_0\\standalone_ps7_cortexa9_0\\bsp\\include\\xiltimer.h"
  "C:\\Users\\Arf\\Desktop\\ip_camera\\zynq\\IP-Camera-on-board-Antminer-S9\\ip_camera\\Ipcamera_platform\\ps7_cortexa9_0\\standalone_ps7_cortexa9_0\\bsp\\include\\xtimer_config.h"
  "C:\\Users\\Arf\\Desktop\\ip_camera\\zynq\\IP-Camera-on-board-Antminer-S9\\ip_camera\\Ipcamera_platform\\ps7_cortexa9_0\\standalone_ps7_cortexa9_0\\bsp\\lib\\libxiltimer.a"
  )
endif()
