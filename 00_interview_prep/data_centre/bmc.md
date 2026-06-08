# Baseboard Management Controller (BMC) Architecture

## 1. Architectural Overview
A **Baseboard Management Controller (BMC)** is an autonomous SoC (System on Chip) residing on server or accelerator baseboards. It functions as the root of out-of-band (OOB) management and hardware root of trust. Utilizing isolated standby power, the BMC maintains execution state and network connectivity independently of the host CPU's power state or operating system viability. 

## 2. Hardware Interactions
In AI-centric node architectures, the BMC interfaces asynchronously with dense compute (GPUs, TPUs) and data plane accelerators (SmartNICs/DPUs).

### 2.1. Sideband Communication
The BMC establishes telemetry and control planes via low-speed sideband buses:
- **I2C/SMBus/I3C**: Primarily for reading thermal sensors, EEPROMs (FRU data), and PMBus for power supply telemetry.
- **NC-SI (Network Controller Sideband Interface) over RMII/PCIe**: Dedicated OOB networking pass-through without relying on host data-plane stacks.

### 2.2. Thermal and Power Telemetry
- **Compute Accelerators**: The BMC polls die temperatures and instantaneous power draw. It implements PID control loops to dynamically modulate PWM fan duty cycles, mitigating thermal throttling while optimizing data center PUE (Power Usage Effectiveness).
- **Network Accelerators**: Monitors optical transceiver thresholds (Tx/Rx power, temp) and localized error counters.

### 2.3. Root of Trust and Initialization
- **Secure Boot**: The BMC authenticates cryptographic signatures of component firmwares (Option ROMs, NIC firmware) before de-asserting PCIe reset pins.
- **Power Sequencing**: Enforces strict power rail sequencing during cold boot and handles graceful/hard shutdown signaling.

## 3. Core Management Functions
The BMC abstracts physical chassis interactions through network-addressable endpoints (Redfish/IPMI).

### 3.1. Provisioning and Media
- **Virtual Media**: Exposes remote block devices (ISO/IMG) as local USB Mass Storage over IP.
- **KVM over IP**: Captures host video buffers and injects USB HID inputs over OOB networks for bare-metal debugging.

### 3.2. Firmware Lifecycle
Executes atomic firmware updates for the UEFI/BIOS, CPLDs, SmartNICs, and compute accelerators without relying on host-side flash utilities.

## 4. RAS (Reliability, Availability, Serviceability) Monitoring
The BMC aggregates hardware telemetry to predict or diagnose node-level failures.

### 4.1. Error Telemetry and Routing
Hardware faults (e.g., Uncorrectable memory ECC, PCIe AER) are routed to the BMC via dedicated interrupt pins (`FATAL_ERR`, `THERMTRIP`) or polled registers. The BMC commits these to a persistent NVRAM-backed System Event Log (SEL).

### 4.2. Diagnostic Crashdumps
Upon catastrophic host hangs (e.g., CPU IERR), the BMC leverages JTAG or I2C debugging interfaces to extract raw register states, core dumps, and SRAM contents before triggering a system reset, preserving volatile context for post-mortem analysis.

### 4.3. Predictive Failure Analysis (PFA)
By analyzing the frequency of corrected errors (e.g., corrected ECC in HBM or DDR5), the BMC flags degrading silicon. It issues Redfish events to cluster orchestrators (e.g., Kubernetes) to gracefully cordon the node and drain workloads before a fatal fault occurs.
