// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2024 Advanced Micro Devices, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2024.1 (win64) Build 5076996 Wed May 22 18:37:14 MDT 2024
// Date        : Fri Jun 12 18:04:03 2026
// Host        : DESKTOP-GTOUM49 running 64-bit major release  (build 9200)
// Command     : write_verilog -force -mode synth_stub {c:/Users/Arf/Desktop/ip_camera/New
//               folder/IP-Camera-on-board-Antminer-S9/ip_camera/ip_camera.gen/sources_1/bd/design_1/ip/design_1_ov7670_axi_stream_ca_0_0/design_1_ov7670_axi_stream_ca_0_0_stub.v}
// Design      : design_1_ov7670_axi_stream_ca_0_0
// Purpose     : Stub declaration of top-level module interface
// Device      : xc7z010clg400-1
// --------------------------------------------------------------------------------

// This empty module with port declaration file causes synthesis tools to infer a black box for IP.
// The synthesis directives are for Synopsys Synplify support to prevent IO buffer insertion.
// Please paste the declaration into a Verilog source file or add the file as an additional source.
(* x_core_info = "ov7670_axi_stream_capture,Vivado 2024.1" *)
module design_1_ov7670_axi_stream_ca_0_0(pclk, vsync, href, d, m_axis_tvalid, m_axis_tready, 
  m_axis_tlast, m_axis_tdata, m_axis_tuser, aclk)
/* synthesis syn_black_box black_box_pad_pin="vsync,href,d[7:0],m_axis_tvalid,m_axis_tready,m_axis_tlast,m_axis_tdata[31:0],m_axis_tuser,aclk" */
/* synthesis syn_force_seq_prim="pclk" */;
  input pclk /* synthesis syn_isclock = 1 */;
  input vsync;
  input href;
  input [7:0]d;
  output m_axis_tvalid;
  input m_axis_tready;
  output m_axis_tlast;
  output [31:0]m_axis_tdata;
  output m_axis_tuser;
  output aclk;
endmodule
