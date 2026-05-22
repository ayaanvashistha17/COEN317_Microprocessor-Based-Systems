# COEN 317: Microprocessor Systems (Winter 2026)

Welcome to my repository for **COEN 317: Microprocessor Systems** at **Concordia University**. This project explores embedded systems design using the **Xilinx Zynq-7000 SoC (ZC702 Development Board)** through hardware/software co-design techniques using VHDL and C++.

---

# 🎯 Project Overview

Modern embedded systems combine traditional processors with customizable hardware accelerators on a single chip. This course focuses on designing systems where software running on ARM processors communicates directly with custom FPGA hardware logic.

The platform used throughout this course is the **Xilinx Zynq-7000 SoC**, which contains:

- A dual-core ARM Cortex-A9 Processing System (PS)
- FPGA-based Programmable Logic (PL)
- AXI interconnect buses for high-speed communication

---

# 🧠 System Architecture Overview

```text
┌─────────────────────────────────────────────────────────────┐
│                     Xilinx Zynq-7000 SoC                   │
│                                                             │
│   ┌───────────────────────────┐   High-Speed AXI Bus        │
│   │  Processing System (PS)   │◄────────────────────────┐   │
│   │  • Dual-Core ARM CPU      │                         │   │
│   └───────────────────────────┘                         ▼   │
│                                              ┌──────────────────┐
│   ┌───────────────────────────┐              │ Programmable     │
│   │  Custom C++ Firmware      │              │ Logic (PL)       │
│   │  • Interrupt Handlers     │              │ • VHDL AND Gates │
│   │  • Peripheral Control     │              │ • Hardware Timers│
│   └───────────────────────────┘              │ • Central DMA    │
│                                              └──────────────────┘
└─────────────────────────────────────────────────────────────┘
```

---

# 📂 Repository Structure

```text
├── Lab_Guidelines/        # Official course requirements
├── Lab1_Introduction/     # Bare-metal system initialization
├── Lab2_And_Array/        # ARM-to-FPGA hardware communication
├── Lab3_Timers/           # AXI timers, PWM, and debouncing
├── Lab4_Interrupts_DMA/   # Interrupt controllers and DMA engines
└── Screenshots/           # Lab setup images and execution results
```

---

# 🛠️ Laboratory Breakdown

## 📍 Lab 1 — Introduction to Zynq

### Objective
Set up the Zynq processing system and deploy standalone software applications.

### Key Concepts
- Bare-metal embedded programming
- UART serial communication
- Hardware/software export flow

### Technical Work
- Configured the ARM Processing System (PS)
- Exported hardware definitions from XPS to SDK
- Built and deployed a standalone C++ firmware application
- Printed output over UART serial communication using:
  - `/dev/ttyUSB0`
  - `115200 baud`

### Example Output
```text
Hello World from Zynq PS
```

---

## 📍 Lab 2 — AND Array in Programmable Logic

### Objective
Design custom FPGA logic and interface it with ARM software through AXI GPIO.

### Key Concepts
- FPGA logic design
- AXI communication
- Hardware/software interaction

### Technical Work
- Designed an 8-bit AND gate in VHDL
- Connected the module using AXI GPIO
- Sent packed 16-bit data from software to hardware
- Controlled onboard LEDs using FPGA-generated outputs

### Hardware Flow
```text
ARM Processor → AXI Bus → GPIO → FPGA Logic → LEDs
```

---

## 📍 Lab 3 — AXI Hardware Timers

### Objective
Use dedicated hardware timers for accurate timing operations and waveform generation.

### Key Concepts
- Counter mode timing
- Button debouncing
- PWM signal generation

### Features Implemented

#### ⏱️ Counter Mode
- Measured software execution cycles
- Used AXI Timer hardware registers for precise timing

#### 🔘 Capture Mode
- Captured button press timing events
- Implemented software debouncing to filter noisy button signals

#### 💡 PWM Generation
- Generated adjustable square waves
- Controlled LED brightness using variable duty cycles
- Configured:
  - `TLR0`
  - `TLR1`

---

## 📍 Lab 4 — Interrupts & DMA

### Objective
Improve system efficiency using asynchronous interrupts and hardware-assisted memory transfers.

### Key Concepts
- Interrupt-driven execution
- Direct Memory Access (DMA)
- CPU offloading

---

## 🔔 Part 1 — Hardware Interrupts

### Technical Work
- Connected AXI Timer interrupts to the ARM General Interrupt Controller (GIC)
- Implemented custom Interrupt Service Routines (ISRs)
- Cleared timer interrupt status bits dynamically
- Enabled event-driven software execution

### Interrupt Flow
```text
Timer Overflow → GIC → ARM CPU → ISR Execution
```

---

## 🚚 Part 2 — Central DMA (CDMA)

### Technical Work
- Configured AXI Central DMA
- Connected DMA through High-Performance AXI ports
- Transferred memory blocks directly between DDR locations
- Compared DMA transfers against CPU-based copying

### Benefits
- Reduced CPU workload
- Faster memory transfers
- Improved system throughput

---

# 💻 Technologies & Tools

## Languages
- C++
- VHDL

## Hardware Platform
- Xilinx Zynq-7000 SoC
- XC7Z020 FPGA
- ARM Cortex-A9 Dual-Core Processor

## Development Tools
- Xilinx PlanAhead 14.7
- Xilinx Platform Studio (XPS)
- Xilinx SDK

## Communication Protocols
- AXI4-Lite
- AXI4-Stream
- UART
- GPIO
- DMA

## Operating System
- Linux Workstation Environment

---

# 🚀 Build & Run Instructions

> Note: Xilinx 14.7 tools and a ZC702 FPGA board are required for full hardware execution.

## 1. Initialize the Xilinx Environment

```bash
source /CMC/tools/xilinx_14.7/14.7/ISE_DS/settings64_CMC_central_license.csh
```

---

## 2. Clone the Repository

```bash
git clone https://github.com/vashistha-ayaan/COEN-317.git
cd COEN-317
```

---

## 3. Launch PlanAhead

```bash
planAhead &
```

---

## 4. Open SDK & Run Projects

- Open Xilinx SDK
- Select the desired workspace
- Build the hardware/software projects
- Connect the ZC702 board
- Run the executable through UART serial communication

---

# 📘 Course Information

## Course
**COEN 317 — Microprocessor Systems**  
Department of Electrical & Computer Engineering  
Concordia University

## Main Topics Covered
- Embedded Systems
- FPGA Design
- ARM Processors
- Hardware/Software Co-Design
- AXI Bus Architecture
- DMA Systems
- Interrupt Controllers
- Hardware Timers

---
