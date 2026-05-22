-- /*******************************************************************************
-- *     This file is owned and controlled by Xilinx and must be used             *
-- *     solely for design, simulation, implementation and creation of            *
-- *     design files limited to Xilinx devices or technologies. Use              *
-- *     with non-Xilinx devices or technologies is expressly prohibited          *
-- *     and immediately terminates your license.                                 *
-- *                                                                              *
-- *     XILINX IS PROVIDING THIS DESIGN, CODE, OR INFORMATION "AS IS"            *
-- *     SOLELY FOR USE IN DEVELOPING PROGRAMS AND SOLUTIONS FOR                  *
-- *     XILINX DEVICES.  BY PROVIDING THIS DESIGN, CODE, OR INFORMATION          *
-- *     AS ONE POSSIBLE IMPLEMENTATION OF THIS FEATURE, APPLICATION              *
-- *     OR STANDARD, XILINX IS MAKING NO REPRESENTATION THAT THIS                *
-- *     IMPLEMENTATION IS FREE FROM ANY CLAIMS OF INFRINGEMENT,                  *
-- *     AND YOU ARE RESPONSIBLE FOR OBTAINING ANY RIGHTS YOU MAY REQUIRE         *
-- *     FOR YOUR IMPLEMENTATION.  XILINX EXPRESSLY DISCLAIMS ANY                 *
-- *     WARRANTY WHATSOEVER WITH RESPECT TO THE ADEQUACY OF THE                  *
-- *     IMPLEMENTATION, INCLUDING BUT NOT LIMITED TO ANY WARRANTIES OR           *
-- *     REPRESENTATIONS THAT THIS IMPLEMENTATION IS FREE FROM CLAIMS OF          *
-- *     INFRINGEMENT, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS          *
-- *     FOR A PARTICULAR PURPOSE.                                                *
-- *                                                                              *
-- *     Xilinx products are not intended for use in life support                 *
-- *     appliances, devices, or systems. Use in such applications are            *
-- *     expressly prohibited.                                                    *
-- *                                                                              *
-- *     Copyright (c) 1995-2012 Xilinx, Inc.  All rights reserved.               *
-- *******************************************************************************/

-- The following must be inserted into your VHDL file for this
-- core to be instantiated. Change the instance name and port connections
-- (in parentheses) to your own signal names.

------------- Begin Cut here for INSTANTIATION Template ---// INST_TAG

 attribute BOX_TYPE : STRING;
 attribute BOX_TYPE of system : component is "user_black_box";

  system_i : system
    port map (
      processing_system7_0_MIO => processing_system7_0_MIO,     -- inout std_logic_vector(53 downto 0);
      processing_system7_0_PS_SRSTB => processing_system7_0_PS_SRSTB,     -- in std_logic;
      processing_system7_0_PS_CLK => processing_system7_0_PS_CLK,     -- in std_logic;
      processing_system7_0_PS_PORB => processing_system7_0_PS_PORB,     -- in std_logic;
      processing_system7_0_DDR_Clk => processing_system7_0_DDR_Clk,     -- inout std_logic;
      processing_system7_0_DDR_Clk_n => processing_system7_0_DDR_Clk_n,     -- inout std_logic;
      processing_system7_0_DDR_CKE => processing_system7_0_DDR_CKE,     -- inout std_logic;
      processing_system7_0_DDR_CS_n => processing_system7_0_DDR_CS_n,     -- inout std_logic;
      processing_system7_0_DDR_RAS_n => processing_system7_0_DDR_RAS_n,     -- inout std_logic;
      processing_system7_0_DDR_CAS_n => processing_system7_0_DDR_CAS_n,     -- inout std_logic;
      processing_system7_0_DDR_WEB_pin => processing_system7_0_DDR_WEB_pin,     -- out std_logic;
      processing_system7_0_DDR_BankAddr => processing_system7_0_DDR_BankAddr,     -- inout std_logic_vector(2 downto 0);
      processing_system7_0_DDR_Addr => processing_system7_0_DDR_Addr,     -- inout std_logic_vector(14 downto 0);
      processing_system7_0_DDR_ODT => processing_system7_0_DDR_ODT,     -- inout std_logic;
      processing_system7_0_DDR_DRSTB => processing_system7_0_DDR_DRSTB,     -- inout std_logic;
      processing_system7_0_DDR_DQ => processing_system7_0_DDR_DQ,     -- inout std_logic_vector(31 downto 0);
      processing_system7_0_DDR_DM => processing_system7_0_DDR_DM,     -- inout std_logic_vector(3 downto 0);
      processing_system7_0_DDR_DQS => processing_system7_0_DDR_DQS,     -- inout std_logic_vector(3 downto 0);
      processing_system7_0_DDR_DQS_n => processing_system7_0_DDR_DQS_n,     -- inout std_logic_vector(3 downto 0);
      processing_system7_0_DDR_VRN => processing_system7_0_DDR_VRN,     -- inout std_logic;
      processing_system7_0_DDR_VRP => processing_system7_0_DDR_VRP,     -- inout std_logic;
      axi_gpio_for_output_pins => axi_gpio_for_output_pins     -- out std_logic_vector(7 downto 0);
    );

-- INST_TAG_END ------ End INSTANTIATION Template ---------

