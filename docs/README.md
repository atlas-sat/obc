<div align="left" style="position: relative;">
<h1>Atlas Sat On Board Computer</h1>
<p align="left">
	<em>On Board Computer designed for Atlas Sat. Developed at DSO National Laboratories for R@YDSP</em>
</p>
<p align="left">
	<!--Latest Release Version-->
	<img src="https://img.shields.io/github/v/release/atlas-sat/obc?style=default&logo=github&logoColor=white&color=0080ff" alt="latest-release">
	<img src="https://img.shields.io/github/last-commit/atlas-sat/obc?style=default&logo=git&logoColor=white&color=0080ff" alt="last-commit">
	<img src="https://img.shields.io/github/languages/top/atlas-sat/obc?style=default&color=0080ff" alt="repo-top-language">
	<img src="https://img.shields.io/github/languages/count/atlas-sat/obc?style=default&color=0080ff" alt="repo-languages">
	<img src="https://img.shields.io/github/repo-size/atlas-sat/obc?style=default&color=0080ff" alt="repo-size">
</p>

<!-- insert logo here -->

</div>
<br clear="right">

##  Table of Contents

- [ Overview](#-overview)
- [ Features](#-features)
- [ Project Structure](#-project-structure)
- [ Getting Started](#-getting-started)
  - [ Prerequisites](#-prerequisites)
  - [ Installation](#-installation)
  - [ Usage](#-usage)
  - [ Testing](#-testing)
- [ Project Roadmap](#-project-roadmap)
- [ Contributing](#-contributing)
- [ License](#-license)
- [ Acknowledgments](#-acknowledgments)

---

##  Overview

<!-- Introduce OBC -->
<!-- link to FreeRTOS repo. -->
<!-- link to CSP repo. -->

This repository features code used in the On Board Computer (OBC) of Atlas Sat. The OBC is responsible for managing the satellite's subsystems, and executing the satellite's mission. The OBC is built using the [FreeRTOS real-time operating system](https://www.freertos.org/) and the [CSP communication protocol](https://github.com/libcsp/libcsp). The OBC software is designed to be modular and extensible, allowing for easy integration of new features and subsystems.

---

##  Features

<!-- For lis of features refer to the report -->

For a detailed list of features, refer to the [project report]().

---

##  Project Structure

<details>
<summary>View Project Structure</summary>

```sh
└── obc/
    ├── docs
    │   ├── Capture_obc.PNG
    │   ├── Capture_subsys.PNG
    │   ├── README.md
    │   ├── _config.yml
    │   └── wiring.jpg
    ├── obc
    │   ├── FreeRTOS
    │   │   ├── Demo
    │   │   │   └── Common
    │   │   └── Source
    │   │       ├── include
    │   │       ├── list.c
    │   │       ├── portable
    │   │       ├── queue.c
    │   │       ├── tasks.c
    │   │       └── timers.c
    │   ├── FreeRTOSConfig.h
    │   ├── libcsp
    │   │   ├── CHANGELOG
    │   │   ├── CONTRIBUTORS
    │   │   ├── COPYING
    │   │   ├── INSTALL.rst
    │   │   ├── README.rst
    │   │   ├── bindings
    │   │   │   └── python
    │   │   ├── doc
    │   │   │   ├── example.rst
    │   │   │   ├── history.rst
    │   │   │   ├── interfaces.rst
    │   │   │   ├── libcsp.rst
    │   │   │   ├── memory.rst
    │   │   │   ├── mtu.rst
    │   │   │   ├── protocolstack.rst
    │   │   │   ├── structure.rst
    │   │   │   └── topology.rst
    │   │   ├── include
    │   │   │   └── csp
    │   │   ├── src
    │   │   │   ├── arch
    │   │   │   ├── crypto
    │   │   │   ├── csp_bridge.c
    │   │   │   ├── csp_buffer.c
    │   │   │   ├── csp_conn.c
    │   │   │   ├── csp_crc32.c
    │   │   │   ├── csp_debug.c
    │   │   │   ├── csp_dedup.c
    │   │   │   ├── csp_endian.c
    │   │   │   ├── csp_iflist.c
    │   │   │   ├── csp_io.c
    │   │   │   ├── csp_port.c
    │   │   │   ├── csp_promisc.c
    │   │   │   ├── csp_qfifo.c
    │   │   │   ├── csp_route.c
    │   │   │   ├── csp_service_handler.c
    │   │   │   ├── csp_services.c
    │   │   │   ├── csp_sfp.c
    │   │   │   ├── interfaces
    │   │   │   ├── rtable
    │   │   │   └── transport
    │   │   ├── utils
    │   │   │   ├── cfpsplit.py
    │   │   │   └── cspsplit.py
    │   │   ├── waf
    │   │   └── wscript
    │   ├── main.c
    │   ├── obc.componentinfo.xml
    │   ├── obc.cproj
    │   └── project
    │       ├── include
    │       │   ├── conf_util.h
    │       │   ├── driver_debug.h
    │       │   ├── error.h
    │       │   ├── packet.h
    │       │   ├── protocol.h
    │       │   ├── tasks.h
    │       │   └── uart.h
    │       └── src
    │           ├── i2c.c
    │           ├── packet.c
    │           ├── protocol.c
    │           ├── tasks.c
    │           └── uart.c
    └── obc.atsln
```
</details>

---

##  Getting Started

###  Prerequisites

Before getting started with obc, ensure your runtime environment meets the following requirements:

- **Programming Language:** C
- **IDE:** Microchip Studio

###  Installation

<!-- Add installation instructions for microchip studio here -->

#### 1. Download and Install Arduino IDE
- Download from [Arduino Software](https://www.arduino.cc/en/software).
- Choose the MSI installer.

#### 2. Configure Arduino IDE
1. Go to `Tools > Board > Boards Manager` and install Arduino AVR boards.
2. Check the installation path of Arduino IDE:
   - Right-click on the Arduino IDE icon > Open File Location.
   - Example: `C:\Users\johndoe\AppData\Local\Programs\Arduino IDE`.
3. Verify the existence of the folder:
   - Example: `C:\Users\johndoe\AppData\Local\Arduino15`.
4. Locate the `avrdude.exe` path:
   - Example:  
     ```
     C:\Users\johndoe\AppData\Local\Arduino15\packages\arduino\tools\avrdude\6.3.0-arduino17\bin\avrdude.exe
     ```
   - Copy the path and save it.

#### 3. Install Microchip Studio
1. Download Microchip Studio from the [Microchip website](https://www.microchip.com/en-us/tools-resources/develop/microchip-studio).
2. Open Microchip Studio.
3. Go to `Tools > External Tools`.
4. Click on `Add`.
5. Fill in the following fields:
   - Title: `COMx`.
       - Example: `COM4`.
   - Command: `avrdude.exe` path.
       - Example: 
       ```
       C:\Users\johndoe\AppData\Local\Arduino15\packages\arduino\tools\avrdude\6.3.0-arduino17\bin\avrdude.exe
       ```
   - Arguments: `-C` path to `avrdude.conf` file `-v -patmega328p -carduino -PCOM` x `-b115200 -D -Uflash:w:"$(ProjectDir)Debug\$(TargetName).hex":i`.
        - Example: 
        ```
        -C"C:\Users\johndoe\AppData\Local\Arduino15\packages\arduino\tools\avrdude\6.3.0-arduino17\etc\avrdude.conf" -v -patmega328p -carduino -PCOM3 -b115200 -D -Uflash:w:"$(ProjectDir)Debug\$(TargetName).hex":i
        ```

#### 4. Clone the Repository
1. Clone the obc repository:
```sh
❯ git clone https://github.com/atlas-sat/obc
```

2. Navigate to the project directory:
```sh
❯ cd obc
```

###  Usage

#### 1. Open the Project
1. Open Microchip Studio.
2. Go to `File > Open > Project/Solution`.
3. Navigate to the project directory and open the `obc.atsln` file.

#### 2. Build the Project
1. Build the project by clicking on the `Build` button.
2. Verify that the project builds successfully.

#### 3. Flash the Project
1. Go to `Tools > COMx`.
2. Verify that the project flashes successfully.

###  Contribution


---
<summary>Contributor Graph</summary>
<br>
<p align="left">
   <a href="https://github.com{/atlas-sat/obc/}graphs/contributors">
      <img src="https://contrib.rocks/image?repo=atlas-sat/obc">
   </a>
</p>
</details>

---

##  License

This project is not protected under any license. You are free to use, modify, and distribute the software as you see fit.

---

##  Acknowledgments

- Caden's cat Clover.

---