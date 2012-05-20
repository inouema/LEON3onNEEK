//altpll bandwidth_type="AUTO" CBX_DECLARE_ALL_CONNECTED_PORTS="OFF" clk0_divide_by=10 clk0_duty_cycle=50 clk0_multiply_by=20 clk0_phase_shift="0" clk1_divide_by=10 clk1_duty_cycle=50 clk1_multiply_by=20 clk1_phase_shift="2500" clk2_divide_by=10 clk2_duty_cycle=50 clk2_multiply_by=20 clk2_phase_shift="5000" clk3_divide_by=10 clk3_duty_cycle=50 clk3_multiply_by=20 clk3_phase_shift="7500" clk4_divide_by=10 clk4_duty_cycle=50 clk4_multiply_by=20 clk4_phase_shift="2500" compensate_clock="CLK0" device_family="Cyclone III" inclk0_input_frequency=20000 intended_device_family="Cyclone III" lpm_hint="CBX_MODULE_PREFIX=apll" operation_mode="normal" pll_type="FAST" port_clk0="PORT_USED" port_clk1="PORT_USED" port_clk2="PORT_USED" port_clk3="PORT_USED" port_clk4="PORT_USED" port_clk5="PORT_UNUSED" port_extclk0="PORT_UNUSED" port_extclk1="PORT_UNUSED" port_extclk2="PORT_UNUSED" port_extclk3="PORT_UNUSED" port_inclk1="PORT_UNUSED" port_phasecounterselect="PORT_USED" port_phasedone="PORT_USED" port_scandata="PORT_UNUSED" port_scandataout="PORT_UNUSED" self_reset_on_loss_lock="ON" width_clock=5 width_phasecounterselect=3 areset clk inclk locked phasecounterselect phasedone phasestep phaseupdown scanclk CARRY_CHAIN="MANUAL" CARRY_CHAIN_LENGTH=48
//VERSION_BEGIN 11.1SP1 cbx_altclkbuf 2011:11:23:21:11:17:SJ cbx_altiobuf_bidir 2011:11:23:21:11:17:SJ cbx_altiobuf_in 2011:11:23:21:11:17:SJ cbx_altiobuf_out 2011:11:23:21:11:17:SJ cbx_altpll 2011:11:23:21:11:17:SJ cbx_cycloneii 2011:11:23:21:11:17:SJ cbx_lpm_add_sub 2011:11:23:21:11:17:SJ cbx_lpm_compare 2011:11:23:21:11:17:SJ cbx_lpm_decode 2011:11:23:21:11:17:SJ cbx_lpm_mux 2011:11:23:21:11:17:SJ cbx_mgl 2011:11:23:21:12:03:SJ cbx_stratix 2011:11:23:21:11:17:SJ cbx_stratixii 2011:11:23:21:11:17:SJ cbx_stratixiii 2011:11:23:21:11:17:SJ cbx_stratixv 2011:11:23:21:11:17:SJ cbx_util_mgl 2011:11:23:21:11:17:SJ  VERSION_END
//CBXI_INSTANCE_NAME="leon3mp_ddrspa_ddrsp0_ddrc0_ddrphy_wrap_ddr_phy0_ddrphy_ddr_phy0_cycloneiii_ddr_phy_cyc3_ddr_phy0_apll_pll0_altpll_altpll_component"
// synthesis VERILOG_INPUT_VERSION VERILOG_2001
// altera message_off 10463



// Copyright (C) 1991-2011 Altera Corporation
//  Your use of Altera Corporation's design tools, logic functions 
//  and other software and tools, and its AMPP partner logic 
//  functions, and any output files from any of the foregoing 
//  (including device programming or simulation files), and any 
//  associated documentation or information are expressly subject 
//  to the terms and conditions of the Altera Program License 
//  Subscription Agreement, Altera MegaCore Function License 
//  Agreement, or other applicable license agreement, including, 
//  without limitation, that your use is for the sole purpose of 
//  programming logic devices manufactured by Altera and sold by 
//  Altera or its authorized distributors.  Please refer to the 
//  applicable agreement for further details.




//altpll_dynamic_phase_lcell CBX_DECLARE_ALL_CONNECTED_PORTS="OFF" DEVICE_FAMILY="Cyclone III" INDEX=0 combout dataa datab datac datad ALTERA_INTERNAL_OPTIONS=ADV_NETLIST_OPT_ALLOWED = NEVER_ALLOW;REMOVE_REDUNDANT_LOGIC_CELLS = OFF;IGNORE_LCELL_BUFFERS = OFF
//VERSION_BEGIN 11.1SP1 cbx_altclkbuf 2011:11:23:21:11:17:SJ cbx_altiobuf_bidir 2011:11:23:21:11:17:SJ cbx_altiobuf_in 2011:11:23:21:11:17:SJ cbx_altiobuf_out 2011:11:23:21:11:17:SJ cbx_altpll 2011:11:23:21:11:17:SJ cbx_cycloneii 2011:11:23:21:11:17:SJ cbx_lpm_add_sub 2011:11:23:21:11:17:SJ cbx_lpm_compare 2011:11:23:21:11:17:SJ cbx_lpm_decode 2011:11:23:21:11:17:SJ cbx_lpm_mux 2011:11:23:21:11:17:SJ cbx_mgl 2011:11:23:21:12:03:SJ cbx_stratix 2011:11:23:21:11:17:SJ cbx_stratixii 2011:11:23:21:11:17:SJ cbx_stratixiii 2011:11:23:21:11:17:SJ cbx_stratixv 2011:11:23:21:11:17:SJ cbx_util_mgl 2011:11:23:21:11:17:SJ  VERSION_END

//synthesis_resources = lut 1 
//synopsys translate_off
`timescale 1 ps / 1 ps
//synopsys translate_on
(* ALTERA_ATTRIBUTE = {"ADV_NETLIST_OPT_ALLOWED = NEVER_ALLOW;REMOVE_REDUNDANT_LOGIC_CELLS = OFF;IGNORE_LCELL_BUFFERS = OFF;PLL_PHASE_RECONFIG_COUNTER_REMAP_LCELL = 0"} *)
module  apll_altpll_dyn_phase_le
	( 
	combout,
	dataa,
	datab,
	datac,
	datad) /* synthesis synthesis_clearbox=1 */;
	output   combout;
	input   dataa;
	input   datab;
	input   datac;
	input   datad;

	wire  wire_le_comb6_combout;

	cycloneiii_lcell_comb   le_comb6
	( 
	.combout(wire_le_comb6_combout),
	.cout(),
	.dataa(dataa),
	.datab(datab),
	.datac(datac),
	.cin(1'b0),
	.datad(1'b0)
	);
	defparam
		le_comb6.dont_touch = "on",
		le_comb6.lut_mask = 16'hAAAA,
		le_comb6.sum_lutc_input = "datac",
		le_comb6.lpm_type = "cycloneiii_lcell_comb";
	assign
		combout = wire_le_comb6_combout;
endmodule //apll_altpll_dyn_phase_le


//altpll_dynamic_phase_lcell CBX_DECLARE_ALL_CONNECTED_PORTS="OFF" DEVICE_FAMILY="Cyclone III" INDEX=1 combout dataa datab datac datad ALTERA_INTERNAL_OPTIONS=ADV_NETLIST_OPT_ALLOWED = NEVER_ALLOW;REMOVE_REDUNDANT_LOGIC_CELLS = OFF;IGNORE_LCELL_BUFFERS = OFF
//VERSION_BEGIN 11.1SP1 cbx_altclkbuf 2011:11:23:21:11:17:SJ cbx_altiobuf_bidir 2011:11:23:21:11:17:SJ cbx_altiobuf_in 2011:11:23:21:11:17:SJ cbx_altiobuf_out 2011:11:23:21:11:17:SJ cbx_altpll 2011:11:23:21:11:17:SJ cbx_cycloneii 2011:11:23:21:11:17:SJ cbx_lpm_add_sub 2011:11:23:21:11:17:SJ cbx_lpm_compare 2011:11:23:21:11:17:SJ cbx_lpm_decode 2011:11:23:21:11:17:SJ cbx_lpm_mux 2011:11:23:21:11:17:SJ cbx_mgl 2011:11:23:21:12:03:SJ cbx_stratix 2011:11:23:21:11:17:SJ cbx_stratixii 2011:11:23:21:11:17:SJ cbx_stratixiii 2011:11:23:21:11:17:SJ cbx_stratixv 2011:11:23:21:11:17:SJ cbx_util_mgl 2011:11:23:21:11:17:SJ  VERSION_END

//synthesis_resources = lut 1 
//synopsys translate_off
`timescale 1 ps / 1 ps
//synopsys translate_on
(* ALTERA_ATTRIBUTE = {"ADV_NETLIST_OPT_ALLOWED = NEVER_ALLOW;REMOVE_REDUNDANT_LOGIC_CELLS = OFF;IGNORE_LCELL_BUFFERS = OFF;PLL_PHASE_RECONFIG_COUNTER_REMAP_LCELL = 1"} *)
module  apll_altpll_dyn_phase_le1
	( 
	combout,
	dataa,
	datab,
	datac,
	datad) /* synthesis synthesis_clearbox=1 */;
	output   combout;
	input   dataa;
	input   datab;
	input   datac;
	input   datad;

	wire  wire_le_comb7_combout;

	cycloneiii_lcell_comb   le_comb7
	( 
	.combout(wire_le_comb7_combout),
	.cout(),
	.dataa(dataa),
	.datab(datab),
	.datac(datac),
	.cin(1'b0),
	.datad(1'b0)
	);
	defparam
		le_comb7.dont_touch = "on",
		le_comb7.lut_mask = 16'hCCCC,
		le_comb7.sum_lutc_input = "datac",
		le_comb7.lpm_type = "cycloneiii_lcell_comb";
	assign
		combout = wire_le_comb7_combout;
endmodule //apll_altpll_dyn_phase_le1


//altpll_dynamic_phase_lcell CBX_DECLARE_ALL_CONNECTED_PORTS="OFF" DEVICE_FAMILY="Cyclone III" INDEX=2 combout dataa datab datac datad ALTERA_INTERNAL_OPTIONS=ADV_NETLIST_OPT_ALLOWED = NEVER_ALLOW;REMOVE_REDUNDANT_LOGIC_CELLS = OFF;IGNORE_LCELL_BUFFERS = OFF
//VERSION_BEGIN 11.1SP1 cbx_altclkbuf 2011:11:23:21:11:17:SJ cbx_altiobuf_bidir 2011:11:23:21:11:17:SJ cbx_altiobuf_in 2011:11:23:21:11:17:SJ cbx_altiobuf_out 2011:11:23:21:11:17:SJ cbx_altpll 2011:11:23:21:11:17:SJ cbx_cycloneii 2011:11:23:21:11:17:SJ cbx_lpm_add_sub 2011:11:23:21:11:17:SJ cbx_lpm_compare 2011:11:23:21:11:17:SJ cbx_lpm_decode 2011:11:23:21:11:17:SJ cbx_lpm_mux 2011:11:23:21:11:17:SJ cbx_mgl 2011:11:23:21:12:03:SJ cbx_stratix 2011:11:23:21:11:17:SJ cbx_stratixii 2011:11:23:21:11:17:SJ cbx_stratixiii 2011:11:23:21:11:17:SJ cbx_stratixv 2011:11:23:21:11:17:SJ cbx_util_mgl 2011:11:23:21:11:17:SJ  VERSION_END

//synthesis_resources = lut 1 
//synopsys translate_off
`timescale 1 ps / 1 ps
//synopsys translate_on
(* ALTERA_ATTRIBUTE = {"ADV_NETLIST_OPT_ALLOWED = NEVER_ALLOW;REMOVE_REDUNDANT_LOGIC_CELLS = OFF;IGNORE_LCELL_BUFFERS = OFF;PLL_PHASE_RECONFIG_COUNTER_REMAP_LCELL = 2"} *)
module  apll_altpll_dyn_phase_le12
	( 
	combout,
	dataa,
	datab,
	datac,
	datad) /* synthesis synthesis_clearbox=1 */;
	output   combout;
	input   dataa;
	input   datab;
	input   datac;
	input   datad;

	wire  wire_le_comb8_combout;

	cycloneiii_lcell_comb   le_comb8
	( 
	.combout(wire_le_comb8_combout),
	.cout(),
	.dataa(dataa),
	.datab(datab),
	.datac(datac),
	.cin(1'b0),
	.datad(1'b0)
	);
	defparam
		le_comb8.dont_touch = "on",
		le_comb8.lut_mask = 16'hF0F0,
		le_comb8.sum_lutc_input = "datac",
		le_comb8.lpm_type = "cycloneiii_lcell_comb";
	assign
		combout = wire_le_comb8_combout;
endmodule //apll_altpll_dyn_phase_le12

//synthesis_resources = cycloneiii_pll 1 lut 6 reg 1 
//synopsys translate_off
`timescale 1 ps / 1 ps
//synopsys translate_on
(* ALTERA_ATTRIBUTE = {"SUPPRESS_DA_RULE_INTERNAL=C104;{-to remap_decoy_le3a_0} ADV_NETLIST_OPT_ALLOWED = NEVER_ALLOW;{-to remap_decoy_le3a_1} ADV_NETLIST_OPT_ALLOWED = NEVER_ALLOW;{-to remap_decoy_le3a_2} ADV_NETLIST_OPT_ALLOWED = NEVER_ALLOW;{-to remap_decoy_le3a_0} IGNORE_LCELL_BUFFERS = OFF;{-to remap_decoy_le3a_1} IGNORE_LCELL_BUFFERS = OFF;{-to remap_decoy_le3a_2} IGNORE_LCELL_BUFFERS = OFF;{-to remap_decoy_le3a_0} REMOVE_REDUNDANT_LOGIC_CELLS = OFF;{-to remap_decoy_le3a_1} REMOVE_REDUNDANT_LOGIC_CELLS = OFF;{-to remap_decoy_le3a_2} REMOVE_REDUNDANT_LOGIC_CELLS = OFF"} *)
module  apll_altpll
	( 
	areset,
	clk,
	inclk,
	locked,
	phasecounterselect,
	phasedone,
	phasestep,
	phaseupdown,
	scanclk) /* synthesis synthesis_clearbox=1 */;
	input   areset;
	output   [4:0]  clk;
	input   [1:0]  inclk;
	output   locked;
	input   [2:0]  phasecounterselect;
	output   phasedone;
	input   phasestep;
	input   phaseupdown;
	input   scanclk;
`ifndef ALTERA_RESERVED_QIS
// synopsys translate_off
`endif
	tri0   areset;
	tri0   [1:0]  inclk;
	tri1   [2:0]  phasecounterselect;
	tri1   phasestep;
	tri1   phaseupdown;
	tri0   scanclk;
`ifndef ALTERA_RESERVED_QIS
// synopsys translate_on
`endif

	wire  wire_altpll_dyn_phase_le2_combout;
	wire  wire_altpll_dyn_phase_le4_combout;
	wire  wire_altpll_dyn_phase_le5_combout;
	reg	pll_lock_sync;
	wire  [0:0]   wire_remap_decoy_le3a_0out;
	wire  [0:0]   wire_remap_decoy_le3a_1out;
	wire  [0:0]   wire_remap_decoy_le3a_2out;
	wire  [4:0]   wire_pll1_clk;
	wire  wire_pll1_fbout;
	wire  wire_pll1_locked;
	wire  wire_pll1_phasedone;

	apll_altpll_dyn_phase_le   altpll_dyn_phase_le2
	( 
	.combout(wire_altpll_dyn_phase_le2_combout),
	.dataa(wire_remap_decoy_le3a_0out[0:0]),
	.datab(wire_remap_decoy_le3a_1out[0:0]),
	.datac(wire_remap_decoy_le3a_2out[0:0]),
	.datad(1'b0));
	apll_altpll_dyn_phase_le1   altpll_dyn_phase_le4
	( 
	.combout(wire_altpll_dyn_phase_le4_combout),
	.dataa(wire_remap_decoy_le3a_0out[0:0]),
	.datab(wire_remap_decoy_le3a_1out[0:0]),
	.datac(wire_remap_decoy_le3a_2out[0:0]),
	.datad(1'b0));
	apll_altpll_dyn_phase_le12   altpll_dyn_phase_le5
	( 
	.combout(wire_altpll_dyn_phase_le5_combout),
	.dataa(wire_remap_decoy_le3a_0out[0:0]),
	.datab(wire_remap_decoy_le3a_1out[0:0]),
	.datac(wire_remap_decoy_le3a_2out[0:0]),
	.datad(1'b0));
	// synopsys translate_off
	initial
		pll_lock_sync = 0;
	// synopsys translate_on
	always @ ( posedge wire_pll1_locked or  posedge areset)
		if (areset == 1'b1) pll_lock_sync <= 1'b0;
		else  pll_lock_sync <= 1'b1;
	lcell   remap_decoy_le3a_0
	( 
	.in(phasecounterselect[0]),
	.out(wire_remap_decoy_le3a_0out[0:0]));
	lcell   remap_decoy_le3a_1
	( 
	.in(phasecounterselect[1]),
	.out(wire_remap_decoy_le3a_1out[0:0]));
	lcell   remap_decoy_le3a_2
	( 
	.in(phasecounterselect[2]),
	.out(wire_remap_decoy_le3a_2out[0:0]));
	cycloneiii_pll   pll1
	( 
	.activeclock(),
	.areset(areset),
	.clk(wire_pll1_clk),
	.clkbad(),
	.fbin(wire_pll1_fbout),
	.fbout(wire_pll1_fbout),
	.inclk(inclk),
	.locked(wire_pll1_locked),
	.phasecounterselect({wire_altpll_dyn_phase_le5_combout, wire_altpll_dyn_phase_le4_combout, wire_altpll_dyn_phase_le2_combout}),
	.phasedone(wire_pll1_phasedone),
	.phasestep(phasestep),
	.phaseupdown(phaseupdown),
	.scanclk(scanclk),
	.scandataout(),
	.scandone(),
	.vcooverrange(),
	.vcounderrange()
	`ifndef FORMAL_VERIFICATION
	// synopsys translate_off
	`endif
	,
	.clkswitch(1'b0),
	.configupdate(1'b0),
	.pfdena(1'b1),
	.scanclkena(1'b1),
	.scandata(1'b0)
	`ifndef FORMAL_VERIFICATION
	// synopsys translate_on
	`endif
	);
	defparam
		pll1.bandwidth_type = "auto",
		pll1.clk0_divide_by = 10,
		pll1.clk0_duty_cycle = 50,
		pll1.clk0_multiply_by = 20,
		pll1.clk0_phase_shift = "0",
		pll1.clk1_divide_by = 10,
		pll1.clk1_duty_cycle = 50,
		pll1.clk1_multiply_by = 20,
		pll1.clk1_phase_shift = "2500",
		pll1.clk2_divide_by = 10,
		pll1.clk2_duty_cycle = 50,
		pll1.clk2_multiply_by = 20,
		pll1.clk2_phase_shift = "5000",
		pll1.clk3_divide_by = 10,
		pll1.clk3_duty_cycle = 50,
		pll1.clk3_multiply_by = 20,
		pll1.clk3_phase_shift = "7500",
		pll1.clk4_divide_by = 10,
		pll1.clk4_duty_cycle = 50,
		pll1.clk4_multiply_by = 20,
		pll1.clk4_phase_shift = "2500",
		pll1.compensate_clock = "clk0",
		pll1.inclk0_input_frequency = 20000,
		pll1.operation_mode = "normal",
		pll1.pll_type = "auto",
		pll1.self_reset_on_loss_lock = "on",
		pll1.lpm_type = "cycloneiii_pll";
	assign
		clk = {wire_pll1_clk[4:0]},
		locked = (wire_pll1_locked & pll_lock_sync),
		phasedone = wire_pll1_phasedone;
endmodule //apll_altpll
//VALID FILE
