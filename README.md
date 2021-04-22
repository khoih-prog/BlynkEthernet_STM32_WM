## BlynkEthernet_STM32_WM

[![arduino-library-badge](https://www.ardu-badge.com/badge/BlynkEthernet_STM32_WM.svg?)](https://www.ardu-badge.com/BlynkEthernet_STM32_WM)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/BlynkEthernet_STM32_WM.svg)](https://github.com/khoih-prog/BlynkEthernet_STM32_WM/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/BlynkEthernet_STM32_WM/blob/master/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/BlynkEthernet_STM32_WM.svg)](http://github.com/khoih-prog/BlynkEthernet_STM32_WM/issues)

---
---

## Table of Contents

* [Why do we need this BlynkEthernet_STM32_WM library](#why-do-we-need-this-blynkethernet_stm32_wm-library)
  * [Features](#features)
  * [Currently supported Boards](#currently-supported-boards)
  * [Currently supported Ethernet shields/modules](#currently-supported-ethernet-shieldsmodules)
  * [Not supported Boards](#not-supported-boards)
* [Changelog](#changelog)
  * [Releases v1.2.1](#releases-v121)
  * [Releases v1.2.0](#releases-v120)
  * [Releases v1.1.1](#releases-v111)
  * [Major Releases v1.1.0](#major-releases-v110)
  * [Releases v1.0.4](#releases-v104)
  * [Releases v1.0.3](#releases-v103)
  * [Releases v1.0.2](#releases-v102)
* [Prerequisites](#prerequisites)
* [Installation](#installation)
  * [Use Arduino Library Manager](#use-arduino-library-manager)
  * [Manual Install](#manual-install)
  * [VS Code & PlatformIO](#vs-code--platformio)
* [Packages' Patches](#packages-patches)
  * [1. For STM32 boards to use LAN8720](#1-for-stm32-boards-to-use-lan8720)
  * [2. For STM32 boards to use Serial1](#2-for-stm32-boards-to-use-serial1)
* [Libraries' Patches](#libraries-patches)
  * [1. For application requiring 2K+ HTML page](#1-for-application-requiring-2k-html-page)
  * [2. For Ethernet library](#2-for-ethernet-library)
  * [3. For EthernetLarge library](#3-for-ethernetlarge-library)
  * [4. For Etherne2 library](#4-for-ethernet2-library)
  * [5. For Ethernet3 library](#5-for-ethernet3-library)
  * [6. For UIPEthernet library](#6-for-uipethernet-library)
  * [7. Optional UIPthernet patch](#7-optional-uipethernet-patch) 
* [Configuration Notes](#configuration-notes)
  * [1. How to select which built-in Ethernet or shield to use](#1-how-to-select-which-built-in-ethernet-or-shield-to-use)
    * [Select **one and only one** Ethernet library to use as follows:](#select-one-and-only-one-ethernet-library-to-use-as-follows)
    * [To use built-in LAN8742A](#to-use-built-in-lan8742a)
    * [To use LAN8720](#to-use-lan8720)
    * [To use W5x00 Ethernet, for example using EthernetLarge library](#to-use-w5x00-ethernet-for-example-using-ethernetlarge-library)
    * [To use ENC28J60 Ethernet, using EthernetENC library (**NEW and Better**)](#to-use-enc28j60-ethernet-using-ethernetenc-library-new-and-better)
    * [To use ENC28J60 Ethernet, using UIPEthernet library](#to-use-enc28j60-ethernet-using-uipethernet-library)
  * [Important](#important)
  * [2. How to connect or select another CS/SS pin to use](#2-how-to-connect-or-select-another-csss-pin-to-use)
  * [3. How to increase W5x00 TX/RX buffer](#3-how-to-increase-w5x00-txrx-buffer)
  * [4. How to adjust sendContent_P() and send_P() buffer size](#4-how-to-adjust-sendcontent_p-and-send_p-buffer-size)
* [How to use](#how-to-use)
* [HOWTO use default Credentials and have them pre-loaded onto Config Portal](#howto-use-default-credentials-and-have-them-pre-loaded-onto-config-portal)
  * [ 1. To load Default Credentials](#1-to-load-default-credentials)
  * [ 2. To use system default to load "blank" when there is no valid Credentials](#2-to-use-system-default-to-load-blank-when-there-is-no-valid-credentials)
  * [ 3. Example of Default Credentials](#3-example-of-default-credentials)
  * [ 4. How to add dynamic parameters from sketch](#4-how-to-add-dynamic-parameters-from-sketch)
  * [ 5. If you don't need to add dynamic parameters](#5-if-you-dont-need-to-add-dynamic-parameters)
* [Important Notes for using Dynamic Parameters' ids](#important-notes-for-using-dynamic-parameters-ids)
* [Why using this BlynkEthernet_STM32_WM with MultiBlynk features](#why-using-this-blynkethernet_stm32_wm-with-multiblynk-features)
* [HOWTO use STM32F4 with LAN8720](#howto-use-stm32f4-with-lan8720)
  * [1. Wiring](#1-wiring)
  * [2. HOWTO program using STLink V-2 or V-3](#2-howto-program-using-stlink-v-2-or-v-3)
  * [3. HOWTO use Serial Port for Debugging](#3-howto-use-serial-port-for-debugging)
* [Examples](#examples)
  * [ 1. AM2315_W5500](examples/AM2315_W5500)
  * [ 2. BI_Ethernet_Blynk](examples/BI_Ethernet_Blynk)
  * [ 3. BI_Ethernet_Blynk_Email](examples/BI_Ethernet_Blynk_Email)
  * [ 4. BI_Ethernet_WM_Config](examples/BI_Ethernet_WM_Config)
  * [ 5. BlynkHTTPClient](examples/BlynkHTTPClient)
  * [ 6. DHT11_W5100](examples/DHT11_W5100)
  * [ 7. ENC28J60_Blynk](examples/ENC28J60_Blynk)
  * [ 8. ENC28J60_Blynk_Email](examples/ENC28J60_Blynk_Email)
  * [ 9. ENC28J60_Blynk_Email](examples/ENC28J60_Blynk_Email)
  * [10. **EthernetENC_Blynk**](examples/EthernetENC_Blynk)
  * [11. **EthernetENC_Blynk_Email**](examples/EthernetENC_Blynk_Email)
  * [12. **EthernetENC_WM_Config**](examples/EthernetENC_WM_Config)
  * [13. W5100_Blynk](examples/W5100_Blynk)
  * [14. W5100_WM_Config](examples/W5100_WM_Config)
  * [15. W5100_Blynk_Email](examples/W5100_Blynk_Email)
  * [16. **LAN8720_Ethernet_Blynk**](examples/LAN8720_Ethernet_Blynk)
  * [17. **LAN8720_Ethernet_Blynk_Email**](examples/LAN8720_Ethernet_Blynk_Email)
  * [18. **LAN8720_Ethernet_WM_Config**](examples/LAN8720_Ethernet_WM_Config)
* [So, how it works?](#so-how-it-works)
* [Example BI_Ethernet_Blynk](#example-bi_ethernet_blynk)
  * [1. File BI_Ethernet_Blynk.ino](#1-file-bi_ethernet_blynkino)
  * [2. File defines.h](#2-file-definesh) 
  * [3. File Credentials.h](#3-file-credentialsh) 
  * [4. File dynamicParams.h](#4-file-dynamicparamsh) 
* [Debug Terminal Output Samples](#debug-terminal-output-samples)
  * [1. BI_Ethernet_Blynk on NUCLEO_F767ZI using LAN8742A Ethernet and STM32Ethernet Library](#1-bi_ethernet_blynk-on-nucleo_f767zi-using-lan8742a-ethernet-and-stm32ethernet-library)
    * [1.1. No DoubleReset Detected => Running normally](#11-no-doublereset-detected--running-normally)
    * [1.2. DoubleReset Detected => Enter Config Portal](#12-doublereset-detected--enter-config-portal)
    * [1.3. Enter non-persistent ConfigPortal](#13-enter-non-persistent-configportal)
    * [1.4. Enter persistent ConfigPortal](#14-enter-persistent-configportal)
  * [2. EthernetENC_Blynk on NUCLEO_F767ZI using ENC28J60 and EthernetENC Library](#2-ethernetenc_blynk-on-nucleo_f767zi-using-enc28j60-and-ethernetenc-library)
    * [2.1. No DoubleReset Detected => Running normally](#21-no-doublereset-detected--running-normally)
    * [2.2. DoubleReset Detected => Enter Config Portal](#22-doublereset-detected--enter-config-portal)
    * [2.3. Enter non-persistent ConfigPortal](#23-enter-non-persistent-configportal)
    * [2.4. Enter persistent ConfigPortal](#24-enter-persistent-configportal)
    * [2.5. Lost Blynk Server => autoreconnect to another Blynk Server](#25-lost-blynk-server--autoreconnect-to-another-blynk-server)
  * [3. ENC28J60_Blynk on NUCLEO_F767ZI using ENC28J60 and UIPEthernet Library](#3-enc28j60_blynk-on-nucleo_f767zi-using-enc28j60-and-uipethernet-library)
    * [3.1. No DoubleReset Detected => Running normally](#31-no-doublereset-detected--running-normally)
    * [3.2. DoubleReset Detected => Enter Config Portal](#32-doublereset-detected--enter-config-portal)
    * [3.3. Enter non-persistent ConfigPortal](#33-enter-non-persistent-configportal)
    * [3.4. Enter persistent ConfigPortal](#34-enter-persistent-configportal)
  * [4. W5100_Blynk on NUCLEO_F767ZI using W5x00 and EthernetLarge Library](#4-w5100_blynk-on-nucleo_f767zi-using-w5x00-and-ethernetlarge-library)
    * [4.1. No DoubleReset Detected => Running normally](#41-no-doublereset-detected--running-normally)
    * [4.2. DoubleReset Detected => Enter Config Portal](#42-doublereset-detected--enter-config-portal)
    * [4.3. Enter non-persistent ConfigPortal](#43-enter-non-persistent-configportal)
    * [4.4. Enter persistent ConfigPortal](#44-enter-persistent-configportal)
  * [5. LAN8720_Ethernet_Blynk on STM32F4 BLACK_F407VE with LAN8720 Ethernet using STM32Ethernet Library](#5-lan8720_ethernet_blynk-on-stm32f4-black_f407ve-with-lan8720-ethernet-using-stm32ethernet-library)
    * [5.1. DoubleReset Detected => Enter Config Portal](#51-doublereset-detected--enter-config-portal)
    * [5.2. Config Data Saved => Connect to Blynk](#52-config-data-saved--connect-to-blynk)
* [Debug](#debug)
* [Troubleshooting](#troubleshooting)
* [Releases](#releases)
* [Issues](#issues)
* [TO DO](#to-do)
* [DONE](#done)
* [Contributions and Thanks](#contributions-and-thanks)
* [Contributing](#contributing)
* [License](#license)
* [Copyright](#copyright)

---
---

### Why do we need this [BlynkEthernet_STM32_WM library](https://github.com/khoih-prog/BlynkEthernet_STM32_WM)

#### Features

This is a Blynk and Credentials Manager Library for configuring/auto(re)connecting **STM32F/L/H/G/WB/MP1 boards** to available MultiBlynk servers at runtime. Connection is with or without SSL. Configuration data to be saved in integrated-EEPROM or emulated-EEPROM using [**FlashStorage_STM32 Library**](https://github.com/khoih-prog/FlashStorage_STM32). Default Credentials as well as Dynamic custom Parameters can be added and modified easily without coding knowledge. 

DoubleResetDetector is used to force Config Portal opening even if the Credentials are still valid.

Already updated and tested with latest **STM32 core v2.0.0**

This is the new library, adding to the current Blynk_WiFiManager. It's designed to help you eliminate `hardcoding` your Blynk credentials in **STM32F/L/H/G/WB/MP1 boards using Ethernet shields (W5100, W5200, W5500, ENC28J60, LAN8720, built-in LAN8742A Ethernet)**. It's currently **not supporting SSL**. Will support soon.
- You can update Blynk Credentials any time you need to change via Configure Portal. Data are saved in configurable locations in integrated or emulated EEPROM using [**FlashStorage_STM32** library](https://github.com/khoih-prog/FlashStorage_STM32)
- **DoubleDetectDetector** feature to force Config Portal when double reset is detected within predetermined time, default 10s.
- Configurable **Config Portal Title** to be either BoardName or default undistinguishable names.
- Examples are redesigned to separate Credentials / Defines / Dynamic Params / Code so that you can change Credentials / Dynamic Params quickly for each device toconnect to local or Cloud Blynk Servers.

New recent features:

- **MultiBlynk** feature for configuring/auto(re)connecting boards to one of the available MultiBlynk Servers at runtime.
- **DoubleDetectDetector** feature to force Config Portal when double reset is detected within predetermined time, default 10s.
- Configurable **Config Portal Title** to be either BoardName or default undistinguishable names.
- Examples are redesigned to separate Credentials / Defines / Dynamic Params / Code so that you can change Credentials / Dynamic Params quickly for each device

#### Currently supported Boards

1. **STM32 boards with built-in Ethernet LAN8742A** such as :

  - **Nucleo-144 (F429ZI, F767ZI)**
  - **Discovery (STM32F746G-DISCOVERY)**
  - **All STM32 boards (STM32F/L/H/G/WB/MP1) with 32K+ Flash, with Built-in Ethernet**
  - See [EthernetWebServer_STM32 Support and Test Results](https://github.com/khoih-prog/EthernetWebServer_STM32/issues/1)
  
2. **STM32F/L/H/G/WB/MP1 boards (with 32+K Flash) running W5x00 or ENC28J60 shields)**

- Nucleo-144
- Nucleo-64
- Discovery
- Generic STM32F0, STM32F1, STM32F2, STM32F3, STM32F4, STM32F7 (with 64+K Flash): x8 and up
- STM32L0, STM32L1, STM32L4
- STM32G0, STM32G4
- STM32H7
- STM32WB
- STM32MP1
- LoRa boards
- 3-D printer boards
- Generic Flight Controllers
- Midatronics boards

3. **STM32 boards using Ethernet LAN8720** such as :

  - **Nucleo-144 (F429ZI, NUCLEO_F746NG, NUCLEO_F746ZG, NUCLEO_F756ZG)**
  - **Discovery (DISCO_F746NG)**
  - **STM32F4 boards (BLACK_F407VE, BLACK_F407VG, BLACK_F407ZE, BLACK_F407ZG, BLACK_F407VE_Mini, DIYMORE_F407VGT, FK407M1)**
 
 ---
 
#### Currently Supported Ethernet shields/modules:

1. Built-in Ethernet LAN8742A using [`STM32Ethernet library`](https://github.com/stm32duino/STM32Ethernet)
2. W5x00 using [`Ethernet`](https://www.arduino.cc/en/Reference/Ethernet), [`EthernetLarge`](https://github.com/OPEnSLab-OSU/EthernetLarge), [`Ethernet2`](https://github.com/adafruit/Ethernet2) or [`Ethernet3`](https://github.com/sstaub/Ethernet3) library
3. ENC28J60 using [`EthernetENC`](https://github.com/jandrassy/EthernetENC) or [`UIPEthernet`](https://github.com/UIPEthernet/UIPEthernet) library
4. LAN8720 using [`STM32Ethernet`](https://github.com/stm32duino/STM32Ethernet) and [`LwIP`](https://github.com/stm32duino/LwIP) libraries.

#### Not supported boards

These boards are not supported:

- Some Nucleo-32 (small Flash/memory)
- Eval (no Serial, just need to redefine in sketch, library and UIPEthernet)
- Generic STM32F0 (small Flash/memory)
- Generic STM32F1 (with 64-K Flash): C6
- Generic STM32F3 : no HardwareSPI.h
- Electronics Speed Controllers (small Flash/memory)

---
---

## Changelog


### Releases v1.2.1

1. Add Packages' Patches for **STM32 core v2.0.0** to use LAN8720 with STM32Ethernet and LwIP libraries
2. Updated and tested with latest **STM32 core v2.0.0**

### Releases v1.2.0

1. Add support to **LAN8720** Ethernet for many **STM32F4** (F407xx, NUCLEO_F429ZI) and **STM32F7** (DISCO_F746NG, NUCLEO_F746ZG, NUCLEO_F756ZG) boards.
2. Add LAN8720 examples
3. Add Packages' Patches for STM32 to use LAN8720 with STM32Ethernet and LwIP libraries

### Releases v1.1.1

1. To permit autoreset after configurable timeout if DRD/MRD or non-persistent forced-CP. Check [**Good new feature: Blynk.resetAndEnterConfigPortal() Thanks & question #27**](https://github.com/khoih-prog/Blynk_WM/issues/27)

### Major Releases v1.1.0

1. Fix Config Portal Bug. 
2. Add functions to control Config Portal from software or Virtual Switches. Check [How to trigger a Config Portal from code #25](https://github.com/khoih-prog/Blynk_WM/issues/25)
3. Use more efficient [FlashStorage_STM32 Library](https://github.com/khoih-prog/FlashStorage_STM32) to save data to emulaled-EEPROM.
4. Add support to new [**`EthernetENC library`**](https://github.com/jandrassy/EthernetENC) for ENC28J60.


### Releases v1.0.4

1. New ***powerful-yet-simple-to-use feature to enable adding dynamic custom parameters*** from sketch and input using the same Config Portal. Config Portal will be auto-adjusted to match the number of dynamic parameters.
2. Dynamic custom parameters to be saved ***automatically in EEPROM***.
3. Permit to input special chars such as ***%*** and ***#*** into data fields.
4. MultiBlynk Servers and Tokens with Auto(Re)Connect feature.

### Releases v1.0.3
1. Reduce html and code size for faster Config Portal response. Enhance GUI.
2. Change default macAddress for boards to avoid macAddress conflict while simultaneously testing multiple boards.

### Releases v1.0.2

1. Fix crashing bug when using dynamic EthernetServer
2. Enhance examples, fix indentation, update README.md

---
---

## Prerequisites

 1. [`Arduino IDE 1.8.13+` for Arduino](https://www.arduino.cc/en/Main/Software)
 2. [`Blynk library 0.6.1+`](https://github.com/blynkkk/blynk-library/releases). [![Latest release](https://img.shields.io/github/release/blynkkk/blynk-library.svg)](https://github.com/blynkkk/blynk-library/releases/latest/)
 3. [`Arduino Core for STM32 v2.0.0+`](https://github.com/stm32duino/Arduino_Core_STM32) for STM32 boards. [![GitHub release](https://img.shields.io/github/release/stm32duino/Arduino_Core_STM32.svg)](https://github.com/stm32duino/Arduino_Core_STM32/releases/latest)
 4. For LAN8720 or built-in LAN8742A Ethernet:
   - [`STM32Ethernet library v1.2.0+`](https://github.com/stm32duino/STM32Ethernet) for built-in LAN8742A Ethernet on (Nucleo-144, Discovery). [![GitHub release](https://img.shields.io/github/release/stm32duino/STM32Ethernet.svg)](https://github.com/stm32duino/STM32Ethernet/releases/latest)
   - [`LwIP library v2.1.2+`](https://github.com/stm32duino/LwIP) for built-in LAN8742A Ethernet on (Nucleo-144, Discovery). [![GitHub release](https://img.shields.io/github/release/stm32duino/LwIP.svg)](https://github.com/stm32duino/LwIP/releases/latest)
 5. For W5x00 Ethernet:
   - [`Ethernet library v2.0.0+`](https://github.com/arduino-libraries/Ethernet) for W5100, W5200 and W5500.  [![GitHub release](https://img.shields.io/github/release/arduino-libraries/Ethernet.svg)](https://github.com/arduino-libraries/Ethernet/releases/latest)
   - [`EthernetLarge library v2.0.0+`](https://github.com/OPEnSLab-OSU/EthernetLarge) for W5100, W5200 and W5500.
   - [`Ethernet2 library v1.0.4+`](https://github.com/khoih-prog/Ethernet2) for W5500. [![GitHub release](https://img.shields.io/github/release/adafruit/Ethernet2.svg)](https://github.com/adafruit/Ethernet2/releases/latest)
   - [`Ethernet3 library v1.5.5+`](https://github.com/sstaub/Ethernet3) for W5500/WIZ550io/WIZ850io/USR-ES1 with Wiznet W5500 chip. [![GitHub release](https://img.shields.io/github/release/sstaub/Ethernet3.svg)](https://github.com/sstaub/Ethernet3/releases/latest)
 6. For ENC28J60 Ethernet:
   - [`EthernetENC library v2.0.0+`](https://github.com/jandrassy/EthernetENC) for ENC28J60. [![GitHub release](https://img.shields.io/github/release/jandrassy/EthernetENC.svg)](https://github.com/jandrassy/EthernetENC/releases/latest). **New and Better**
   - [`UIPEthernet library v2.0.9+`](https://github.com/UIPEthernet/UIPEthernet) for ENC28J60. [![GitHub release](https://img.shields.io/github/release/UIPEthernet/UIPEthernet.svg)](https://github.com/UIPEthernet/UIPEthernet/releases/latest)
 7. [`EthernetWebServer_STM32 library v1.2.0+`](https://github.com/khoih-prog/EthernetWebServer_STM32). To install, check [![arduino-library-badge](https://www.ardu-badge.com/badge/EthernetWebServer_STM32.svg?)](https://www.ardu-badge.com/EthernetWebServer_STM32).
 8. [`FlashStorage_STM32 library v1.0.1+`](https://github.com/khoih-prog/FlashStorage_STM32). To install, check [![arduino-library-badge](https://www.ardu-badge.com/badge/FlashStorage_STM32.svg?)](https://www.ardu-badge.com/FlashStorage_STM32).
 9. [`DoubleResetDetector_Generic library v1.0.3+`](https://github.com/khoih-prog/DoubleResetDetector_Generic). To install. check [![arduino-library-badge](https://www.ardu-badge.com/badge/DoubleResetDetector_Generic.svg?)](https://www.ardu-badge.com/DoubleResetDetector_Generic).
10. [`Functional-VLPP library v1.0.2+`](https://github.com/khoih-prog/functional-vlpp) to use server's lambda function. To install. check [![arduino-library-badge](https://www.ardu-badge.com/badge/Functional-Vlpp.svg?)](https://www.ardu-badge.com/Functional-Vlpp)


---

## Installation

#### Use Arduino Library Manager

The best way is to use `Arduino Library Manager`. Search for `BlynkEthernet_STM32_Manager`, then select / install the latest version. 
You can also use this link [![arduino-library-badge](https://www.ardu-badge.com/badge/BlynkEthernet_STM32_WM.svg?)](https://www.ardu-badge.com/BlynkEthernet_STM32_WM) for more detailed instructions.

Then copy [BlynkDetectDevice.h](https://github.com/khoih-prog/BlynkEthernet_STM32_WM/blob/master/src/Blynk/BlynkDetectDevice.h) to folder ~/Arduino/libraries/Blynk/src/Blynk to overwrite the original file `BlynkDetectDevice.h`.

#### Manual Install

1. Navigate to [BlynkEthernet_STM32_Manager](https://github.com/khoih-prog/BlynkEthernet_STM32_WM) page.
2. Download the latest release `BlynkEthernet_STM32_WM-master.zip`.
3. Extract the zip file to `BlynkEthernet_STM32_WM-master` directory 
4. Copy whole 
  - `BlynkEthernet_STM32_WM-master/src` folder to Arduino libraries' directory such as `~/Arduino/libraries/`.

  Then copy [BlynkDetectDevice.h](https://github.com/khoih-prog/BlynkEthernet_STM32_WM/blob/master/src/Blynk/BlynkDetectDevice.h) to folder ~/Arduino/libraries/Blynk/src/Blynk to overwrite the original file `BlynkDetectDevice.h`. By doing this, the correct board type can be displayed correctly along with Blynk logo as follows:

```
    ___  __          __
   / _ )/ /_ _____  / /__
  / _  / / // / _ \/  '_/
 /____/_/\_, /_//_/_/\_\
        /___/ v0.6.1 on STM32 NUCLEO_F767ZI
```

not just unknown Arduino board type:

```
    ___  __          __
   / _ )/ /_ _____  / /__
  / _  / / // / _ \/  '_/
 /____/_/\_, /_//_/_/\_\
        /___/ v0.6.1 on Arduino
```


### VS Code & PlatformIO

1. Install [VS Code](https://code.visualstudio.com/)
2. Install [PlatformIO](https://platformio.org/platformio-ide)
3. Install [**BlynkEthernet_STM32_WM** library](https://platformio.org/lib/show/11751/BlynkEthernet_STM32_WM) or [**BlynkEthernet_STM32_WM** library](https://platformio.org/lib/show/11751/BlynkEthernet_STM32_WM) by using [Library Manager](https://platformio.org/lib/show/7091/BlynkEthernet_STM32_Manager/installation). Search for **BlynkEthernet_STM32_WM** in [Platform.io Author's Libraries](https://platformio.org/lib/search?query=author:%22Khoi%20Hoang%22)
4. Use included [platformio.ini](platformio/platformio.ini) file from examples to ensure that all dependent libraries will installed automatically. Please visit documentation for the other options and examples at [Project Configuration File](https://docs.platformio.org/page/projectconf.html)


---
---

### Packages' Patches

#### 1. For STM32 boards to use LAN8720

Already updated and tested with latest **STM32 core v2.0.0**

To use LAN8720 on some STM32 boards 

- **Nucleo-144 (F429ZI, NUCLEO_F746NG, NUCLEO_F746ZG, NUCLEO_F756ZG)**
- **Discovery (DISCO_F746NG)**
- **STM32F4 boards (BLACK_F407VE, BLACK_F407VG, BLACK_F407ZE, BLACK_F407ZG, BLACK_F407VE_Mini, DIYMORE_F407VGT, FK407M1)**

you have to copy the files [stm32f4xx_hal_conf_default.h](Packages_Patches/STM32/hardware/stm32/x.yy.zz/system/STM32F4xx) and [stm32f7xx_hal_conf_default.h](Packages_Patches/STM32/hardware/stm32/x.yy.zz/system/STM32F7xx) into STM32 stm32 directory (~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/system) to overwrite the old files.

Supposing the STM32 stm32 core version is 2.0.0. These files must be copied into the directory:

- `~/.arduino15/packages/STM32/hardware/stm32/2.0.0/system/STM32F4xx/stm32f4xx_hal_conf_default.h` for STM32F4.
- `~/.arduino15/packages/STM32/hardware/stm32/2.o.0/system/STM32F7xx/stm32f7xx_hal_conf_default.h` for Nucleo-144 STM32F7.

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz,
theses files must be copied into the corresponding directory:

- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/system/STM32F4xx/stm32f4xx_hal_conf_default.h`
- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/system/STM32F7xx/stm32f7xx_hal_conf_default.h


#### 2. For STM32 boards to use Serial1

**To use Serial1 on some STM32 boards without Serial1 definition (Nucleo-144 NUCLEO_F767ZI, Nucleo-64 NUCLEO_L053R8, etc.) boards**, you have to copy the files [STM32 variant.h](Packages_Patches/STM32/hardware/stm32/1.9.0) into STM32 stm32 directory (~/.arduino15/packages/STM32/hardware/stm32/1.9.0). You have to modify the files corresponding to your boards, this is just an illustration how to do.

Supposing the STM32 stm32 core version is 1.9.0. These files must be copied into the directory:

- `~/.arduino15/packages/STM32/hardware/stm32/1.9.0/variants/NUCLEO_F767ZI/variant.h` for Nucleo-144 NUCLEO_F767ZI.
- `~/.arduino15/packages/STM32/hardware/stm32/1.9.0/variants/NUCLEO_L053R8/variant.h` for Nucleo-64 NUCLEO_L053R8.

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz,
theses files must be copied into the corresponding directory:

- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/variants/NUCLEO_F767ZI/variant.h`
- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/variants/NUCLEO_L053R8/variant.h`

---


### Libraries' Patches

#### 1. For application requiring 2K+ HTML page

If your application requires 2K+ HTML page, the current [`Ethernet library`](https://www.arduino.cc/en/Reference/Ethernet) must be modified if you are using W5200/W5500 Ethernet shields. W5100 is not supported for 2K+ buffer. If you use boards requiring different CS/SS pin for W5x00 Ethernet shield, for example ESP32, ESP8266, nRF52, etc., you also have to modify the following libraries to be able to specify the CS/SS pin correctly.

#### 2. For Ethernet library

To fix [`Ethernet library`](https://www.arduino.cc/en/Reference/Ethernet), just copy these following files into the [`Ethernet library`](https://www.arduino.cc/en/Reference/Ethernet) directory to overwrite the old files:
- [Ethernet.h](LibraryPatches/Ethernet/src/Ethernet.h)
- [Ethernet.cpp](LibraryPatches/Ethernet/src/Ethernet.cpp)
- [EthernetServer.cpp](LibraryPatches/Ethernet/src/EthernetServer.cpp)
- [w5100.h](LibraryPatches/Ethernet/src/utility/w5100.h)
- [w5100.cpp](LibraryPatches/Ethernet/src/utility/w5100.cpp)

#### 3. For EthernetLarge library

To fix [`EthernetLarge library`](https://github.com/OPEnSLab-OSU/EthernetLarge), just copy these following files into the [`EthernetLarge library`](https://github.com/OPEnSLab-OSU/EthernetLarge) directory to overwrite the old files:
- [EthernetLarge.h](LibraryPatches/EthernetLarge/src/EthernetLarge.h)
- [EthernetLarge.cpp](LibraryPatches/EthernetLarge/src/EthernetLarge.cpp)
- [EthernetServer.cpp](LibraryPatches/EthernetLarge/src/EthernetServer.cpp)
- [w5100.h](LibraryPatches/EthernetLarge/src/utility/w5100.h)
- [w5100.cpp](LibraryPatches/EthernetLarge/src/utility/w5100.cpp)


#### 4. For Ethernet2 library

To fix [`Ethernet2 library`](https://github.com/khoih-prog/Ethernet2), just copy these following files into the [`Ethernet2 library`](https://github.com/khoih-prog/Ethernet2) directory to overwrite the old files:

- [Ethernet2.h](LibraryPatches/Ethernet2/src/Ethernet2.h)
- [Ethernet2.cpp](LibraryPatches/Ethernet2/src/Ethernet2.cpp)

To add UDP Multicast support, necessary for the [**UPnP_Generic library**](https://github.com/khoih-prog/UPnP_Generic):

- [EthernetUdp2.h](LibraryPatches/Ethernet2/src/EthernetUdp2.h)
- [EthernetUdp2.cpp](LibraryPatches/Ethernet2/src/EthernetUdp2.cpp)

#### 5. For Ethernet3 library

5. To fix [`Ethernet3 library`](https://github.com/sstaub/Ethernet3), just copy these following files into the [`Ethernet3 library`](https://github.com/sstaub/Ethernet3) directory to overwrite the old files:
- [Ethernet3.h](LibraryPatches/Ethernet3/src/Ethernet3.h)
- [Ethernet3.cpp](LibraryPatches/Ethernet3/src/Ethernet3.cpp)

#### 6. For UIPEthernet library

***To be able to compile and run on nRF52 boards with ENC28J60 using UIPEthernet library***, you have to copy these following files into the UIPEthernet `utility` directory to overwrite the old files:

- [UIPEthernet.h](LibraryPatches/UIPEthernet/UIPEthernet.h)
- [UIPEthernet.cpp](LibraryPatches/UIPEthernet/UIPEthernet.cpp)
- [Enc28J60Network.h](LibraryPatches/UIPEthernet/utility/Enc28J60Network.h)
- [Enc28J60Network.cpp](LibraryPatches/UIPEthernet/utility/Enc28J60Network.cpp)

#### 7. Optional UIPEthernet patch

Check if you need to install the UIPEthernet patch [new STM32 core F3/F4 compatibility](https://github.com/UIPEthernet/UIPEthernet/commit/c6d6519a260166b722b9cee5dd1f0fb2682e6782) to avoid errors `#include HardwareSPI.h` on some STM32 boards (Nucleo-32 F303K8, etc.)


---
---

## Configuration Notes

### 1. How to select which built-in Ethernet or shield to use

#### Select **one and only one** Ethernet library to use as follows:

- Standard W5x00 Ethernet library 

Standard W5x00 using Ethernet library is used by default, in the sketch, just be sure to comment out or leave these #defines to be false :

```cpp
#define USE_BUILTIN_ETHERNET    false
#define USE_UIP_ETHERNET        false

#if !(USE_BUILTIN_ETHERNET || USE_UIP_ETHERNET)
  // Only one of the following to be true
  #define USE_ETHERNET          false
  #define USE_ETHERNET2         false
  #define USE_ETHERNET3         false
  #define USE_ETHERNET_LARGE    false
  #define USE_ETHERNET_ESP8266  false
  #define USE_ETHERNET_ENC      false
  #define USE_CUSTOM_ETHERNET   false
#endif
```

#### To use built-in LAN8742A

```
#define USE_BUILTIN_ETHERNET    true
#define USE_UIP_ETHERNET        false

#if !(USE_BUILTIN_ETHERNET || USE_UIP_ETHERNET)
  // Only one of the following to be true
  #define USE_ETHERNET          false
  #define USE_ETHERNET2         false
  #define USE_ETHERNET3         false
  #define USE_ETHERNET_LARGE    false
  #define USE_ETHERNET_ESP8266  false
  #define USE_ETHERNET_ENC      false
  #define USE_CUSTOM_ETHERNET   false
#endif
```

#### To use LAN8720

```
#define USING_LAN8720           true
#define USE_BUILTIN_ETHERNET    true
#define USE_UIP_ETHERNET        false

#if !(USE_BUILTIN_ETHERNET || USE_UIP_ETHERNET)
  // Only one of the following to be true
  #define USE_ETHERNET          false
  #define USE_ETHERNET2         false
  #define USE_ETHERNET3         false
  #define USE_ETHERNET_LARGE    false
  #define USE_ETHERNET_ESP8266  false
  #define USE_ETHERNET_ENC      false
  #define USE_CUSTOM_ETHERNET   false
#endif
```

#### To use W5x00 Ethernet, for example using EthernetLarge library

```cpp
#define USE_BUILTIN_ETHERNET    false
#define USE_UIP_ETHERNET        false

#if !(USE_BUILTIN_ETHERNET || USE_UIP_ETHERNET)
  // Only one of the following to be true
  #define USE_ETHERNET          false
  #define USE_ETHERNET2         false
  #define USE_ETHERNET3         false
  #define USE_ETHERNET_LARGE    true
  #define USE_ETHERNET_ESP8266  false
  #define USE_ETHERNET_ENC      false
  #define USE_CUSTOM_ETHERNET   false
#endif
```

#### To use ENC28J60 Ethernet, using EthernetENC library (**NEW and Better**)

```cpp
#define USE_BUILTIN_ETHERNET    false
#define USE_UIP_ETHERNET        false

#if !(USE_BUILTIN_ETHERNET || USE_UIP_ETHERNET)
  // Only one of the following to be true
  #define USE_ETHERNET          false
  #define USE_ETHERNET2         false
  #define USE_ETHERNET3         false
  #define USE_ETHERNET_LARGE    false
  #define USE_ETHERNET_ESP8266  false
  #define USE_ETHERNET_ENC      true
  #define USE_CUSTOM_ETHERNET   false
#endif
```

#### To use ENC28J60 Ethernet, using UIPEthernet library

```cpp
#define USE_BUILTIN_ETHERNET    false
#define USE_UIP_ETHERNET        true

#if !(USE_BUILTIN_ETHERNET || USE_UIP_ETHERNET)
  // Only one of the following to be true
  #define USE_ETHERNET          false
  #define USE_ETHERNET2         false
  #define USE_ETHERNET3         false
  #define USE_ETHERNET_LARGE    false
  #define USE_ETHERNET_ESP8266  false
  #define USE_ETHERNET_ENC      false
  #define USE_CUSTOM_ETHERNET   false
#endif
```

- To use any of the Ethernet libraries, such as Ethernet2, Ethernet3, EthernetLarge, EthernetENC:

```cpp
#define USE_BUILTIN_ETHERNET    false
#define USE_UIP_ETHERNET        false

#if !(USE_BUILTIN_ETHERNET || USE_UIP_ETHERNET)
  // Only one of the following to be true
  #define USE_ETHERNET          false
  #define USE_ETHERNET2         true
  #define USE_ETHERNET3         false
  #define USE_ETHERNET_LARGE    false
  #define USE_ETHERNET_ESP8266  false
  #define USE_ETHERNET_ENC      false
  #define USE_CUSTOM_ETHERNET   false
#endif
```

- To use another Ethernet library
For example, Ethernet_XYZ library uses **Ethernet_XYZ.h**

```cpp
#define USE_BUILTIN_ETHERNET    false
#define USE_UIP_ETHERNET        false

#if !(USE_BUILTIN_ETHERNET || USE_UIP_ETHERNET)
  // Only one of the following to be true
  #define USE_ETHERNET          false
  #define USE_ETHERNET2         false
  #define USE_ETHERNET3         false
  #define USE_ETHERNET_LARGE    false
  #define USE_ETHERNET_ESP8266  false
  #define USE_ETHERNET_ENC      false
  #define USE_CUSTOM_ETHERNET   true
#endif

....

#elif USE_CUSTOM_ETHERNET
  //#include "Ethernet_XYZ.h"
  #include "EthernetENC.h"
  #warning Using Custom Ethernet library. You must include a library and initialize.
  #define SHIELD_TYPE           "Custom Ethernet & Ethernet_XYZ Library"
#else
  #define USE_ETHERNET          true
  #include "Ethernet.h"
  #warning Using Ethernet lib
  #define SHIELD_TYPE           "W5x00 & Ethernet Library"
#endif  
...

#include <EthernetWebServer.h>
```

---

### Important:

- The **Ethernet_Shield_W5200, EtherCard, EtherSia  libraries are not supported**. Don't use unless you know how to modify those libraries.
- Requests to support for any future custom Ethernet library will be ignored. **Use at your own risk**.

---

### 2. How to connect or select another CS/SS pin to use

**The default CS/SS pin is 10 for all boards, and is configurable in code.**

If the default pin is not corect, select another CS/SS pin (e.e. D22) to use as follows:

```cpp
// To override the default CS/SS pin. Don't use unless you know exactly which pin to use
// You can define here or customize for each board at same place with BOARD_TYPE
#define USE_THIS_SS_PIN   22  //21  //5 //4 //2 //15
// Default pin 10 to SS/CS. To change according to your board, if necessary
//#define USE_THIS_SS_PIN       10
```

The current SPI pin usage can be displayed by turn on the debug option. For example:

Increase debug level to 2 in `defines.h` of any example:

```
#define DEBUG_ETHERNET_WEBSERVER_PORT       Serial

// Debug Level from 0 to 4
#define _ETHERNET_WEBSERVER_LOGLEVEL_       2
```

The Debug Terminal will then show that the current SPI pin usage of **NUCLEO_F767ZI ==> SS/CS: D10, MOSI: D11, MISO: D12 and SCK: D13**

```
[ETHERNET_WEBSERVER] Board : NUCLEO_F767ZI , setCsPin: 10
[ETHERNET_WEBSERVER] Default SPI pinout:
[ETHERNET_WEBSERVER] MOSI: 11
[ETHERNET_WEBSERVER] MISO: 12
[ETHERNET_WEBSERVER] SCK: 13
[ETHERNET_WEBSERVER] SS: 10
[ETHERNET_WEBSERVER] =========================
```

Connect the wires according to the displayed information.


### 3. How to increase W5x00 TX/RX buffer

- For **Ethernet3** library only,  use as follows

```cpp
  // Use  MAX_SOCK_NUM = 4 for 4K, 2 for 8K, 1 for 16K RX/TX buffer
  #ifndef ETHERNET3_MAX_SOCK_NUM
    #define ETHERNET3_MAX_SOCK_NUM      4
  #endif
  
  Ethernet.setCsPin (USE_THIS_SS_PIN);
  Ethernet.init (ETHERNET3_MAX_SOCK_NUM);
```


### 4. How to adjust sendContent_P() and send_P() buffer size

sendContent_P() and send_P() buffer size is set default at 4 Kbytes, and minimum is 512 bytes. If you need to change, just add a definition, e.g.:

```cpp
#define SENDCONTENT_P_BUFFER_SZ     2048
```

Note that the buffer size must be larger than 512 bytes. See [Sending GZIP HTML ~ 120kb+ (suggested enhancement)](https://github.com/khoih-prog/EthernetWebServer_STM32/issues/3).



---

### How to use

In your code, replace
1. `BlynkSimpleEthernet.h`      with `BlynkSTM32Ethernet_WM.h`        for board using W5100, W5200, W5500 `without SSL`

2. `BlynkSimpleUIPEthernet.h`   with `BlynkSTM32UIPEthernet_WM.h`     for board using ENC28J60 `without SSL`

3. `BlynkSimpleUIPEthernet.h`   with `BlynkSTM32EthernetENC_WM.h`     for board using ENC28J60 `without SSL` to use new EthernetENC library

4. For STM32 with built-in Ethernet, use 

 - `BlynkSTM32BIEthernet_WM.h` to use Blynk Manager feature (Config Portal, MultiBlynk, Dynamic Parameters, etc.)
 - `BlynkSimple_STM32BI_Ethernet.h` to just use Blynk feature


```
// Start location to store config data to avoid conflict with other functions
#define EEPROM_START   0

```

Then replace `Blynk.begin(...)` with :

`Blynk.begin()`

in your code. Keep `Blynk.run()` intact.

That's it.

---
---

### HOWTO use default Credentials and have them pre-loaded onto Config Portal

See this example and modify as necessary

#### 1. To load [Default Credentials](examples/W5500_Blynk/Credentials.h)

```
bool LOAD_DEFAULT_CONFIG_DATA = true;
```

#### 2. To use system default to load "blank" when there is no valid Credentials


```
bool LOAD_DEFAULT_CONFIG_DATA = false;
```

#### 3. Example of [Default Credentials](examples/W5500_Blynk/Credentials.h)


```cpp
/// Start Default Config Data //////////////////

/*
  #define BLYNK_SERVER_MAX_LEN      32
#define BLYNK_TOKEN_MAX_LEN       36

typedef struct
{
  char blynk_server[BLYNK_SERVER_MAX_LEN];
  char blynk_token [BLYNK_TOKEN_MAX_LEN];
}  Blynk_Credentials;

#define NUM_BLYNK_CREDENTIALS     2

// Configurable items besides fixed Header
#define NUM_CONFIGURABLE_ITEMS    ( 3 + (2 * NUM_BLYNK_CREDENTIALS) )

typedef struct Configuration
{
  char header         [16];
  Blynk_Credentials Blynk_Creds [NUM_BLYNK_CREDENTIALS];
  int  blynk_port;
  char static_IP      [16];
  char board_name     [24];
  int  checkSum;
} Blynk_Configuration;
*/

#define TO_LOAD_DEFAULT_CONFIG_DATA      true

#if TO_LOAD_DEFAULT_CONFIG_DATA

bool LOAD_DEFAULT_CONFIG_DATA = true;

Blynk_Configuration defaultConfig =
{
  //char header[16], dummy, not used
#if USE_SSL
  "SSL",
#else
  "NonSSL",
#endif
  // Blynk_Credentials Blynk_Creds [NUM_BLYNK_CREDENTIALS];
  // Blynk_Creds.blynk_server and Blynk_Creds.blynk_token
  "account.duckdns.org",  "token1",
  "blynk-cloud.com",     "<<my real Blynk auth>>",
  //int  blynk_port;
#if USE_SSL
  9443,
#else
  8080,
#endif
  // char static_IP      [16];
  //"192.168.2.230",
  // Use dynamic DHCP IP
  "",
  //char board_name     [24];
  "Air-Control",
  // terminate the list
  //int  checkSum, dummy, not used
  0
  /////////// End Default Config Data /////////////
};

#else

bool LOAD_DEFAULT_CONFIG_DATA = false;

Blynk_Configuration defaultConfig;

#endif    // TO_LOAD_DEFAULT_CONFIG_DATA

/////////// End Default Config Data /////////////
```

#### 4. How to add dynamic parameters from sketch

- To add custom parameters, just modify from the example below

In `defines.h`

```
#define USE_DYNAMIC_PARAMETERS     false
```

in `dynamicParams.h`

```
#if (USE_DYNAMIC_PARAMETERS)
  #warning USE_DYNAMIC_PARAMETERS
#endif

// USE_DYNAMIC_PARAMETERS defined in defined.h

/////////////// Start dynamic Credentials ///////////////

//Defined in BlynkEthernet_WM.h, <BlynkEthernet_ESP8266_WM.h>, <BlynkEthernet_ESP32 or_WM.h>
/**************************************
  #define MAX_ID_LEN                5
  #define MAX_DISPLAY_NAME_LEN      16

  typedef struct
  {
  char id             [MAX_ID_LEN + 1];
  char displayName    [MAX_DISPLAY_NAME_LEN + 1];
  char *pdata;
  uint8_t maxlen;
  } MenuItem;
**************************************/

#if USE_DYNAMIC_PARAMETERS

#define MAX_MQTT_SERVER_LEN      34
char MQTT_Server  [MAX_MQTT_SERVER_LEN + 1]   = "";

#define MAX_MQTT_PORT_LEN        6
char MQTT_Port   [MAX_MQTT_PORT_LEN + 1]  = "";

#define MAX_MQTT_USERNAME_LEN      34
char MQTT_UserName  [MAX_MQTT_USERNAME_LEN + 1]   = "";

#define MAX_MQTT_PW_LEN        34
char MQTT_PW   [MAX_MQTT_PW_LEN + 1]  = "";

#define MAX_MQTT_SUBS_TOPIC_LEN      34
char MQTT_SubsTopic  [MAX_MQTT_SUBS_TOPIC_LEN + 1]   = "";

#define MAX_MQTT_PUB_TOPIC_LEN       34
char MQTT_PubTopic   [MAX_MQTT_PUB_TOPIC_LEN + 1]  = "";

MenuItem myMenuItems [] =
{
  { "mqtt", "MQTT Server",      MQTT_Server,      MAX_MQTT_SERVER_LEN },
  { "mqpt", "Port",             MQTT_Port,        MAX_MQTT_PORT_LEN   },
  { "user", "MQTT UserName",    MQTT_UserName,    MAX_MQTT_USERNAME_LEN },
  { "mqpw", "MQTT PWD",         MQTT_PW,          MAX_MQTT_PW_LEN },
  { "subs", "Subs Topics",      MQTT_SubsTopic,   MAX_MQTT_SUBS_TOPIC_LEN },
  { "pubs", "Pubs Topics",      MQTT_PubTopic,    MAX_MQTT_PUB_TOPIC_LEN },
};

uint16_t NUM_MENU_ITEMS = sizeof(myMenuItems) / sizeof(MenuItem);  //MenuItemSize;

#else

MenuItem myMenuItems [] = {};

uint16_t NUM_MENU_ITEMS = 0;
#endif


/////// // End dynamic Credentials ///////////

```

#### 5. If you don't need to add dynamic parameters

Use the following in sketch

```
#define USE_DYNAMIC_PARAMETERS     false
```

---
---

### Important Notes for using Dynamic Parameters' ids

1. These ids (such as "mqtt" in example) must be **unique**.

Please be noted that the following **reserved names are already used in library**:

```
"sv"    for Blynk Server
"tk"    for Blynk Token
"sv1"   for Blynk Server1
"tk1"   for Blynk Token1
"pt"    for Blynk Port
"ip"    for Static IP Address
"nm"    for Board Name
```

---
---

### Why using this [BlynkEthernet_STM32_WM](https://github.com/khoih-prog/BlynkEthernet_STM32_WM) with MultiBlynk features

You can see that the system **automatically detects and connects to the avaiable Blynk Servers**, whenever interruption happens. This feature is very useful for systems requiring high degree of reliability.

Moreover, this `Blynk.begin()` is **not a blocking call**, so you can use it for critical functions requiring in loop().

Anyway, this is better for projects using Blynk just for GUI (graphical user interface).

In operation, if WiFi or Blynk connection is lost, `Blynk.run()` will try reconnecting automatically. Therefore, `Blynk.run()` must be called in the `loop()` function. Don't use:

```cpp
void loop()
{
  if (Blynk.connected())
     Blynk.run();
     
  ...
}
```
just

```cpp
void loop()
{
  Blynk.run();
  ...
}
```

---
---

### HOWTO use STM32F4 with LAN8720

Already tested with latest **STM32 core v2.0.0**

#### 1. Wiring

This is the Wiring for STM32F4 (BLACK_F407VE, etc.) using LAN8720


|LAN8720 PHY|<--->|STM32F4|
|:-:|:-:|:-:|
|TX1|<--->|PB_13|
|TX_EN|<--->|PB_11|
|TX0|<--->|PB_12|
|RX0|<--->|PC_4|
|RX1|<--->|PC_5|
|nINT/RETCLK|<--->|PA_1|
|CRS|<--->|PA_7|
|MDIO|<--->|PA_2|
|MDC|<--->|PC_1|
|GND|<--->|GND|
|VCC|<--->|+3.3V|

---

#### 2. HOWTO program using STLink V-2 or V-3

Connect as follows. To program, use **STM32CubeProgrammer** or Arduino IDE with 

- **U(S)ART Support: "Enabled (generic Serial)"**
- **Upload Method : "STM32CubeProgrammer (SWD)"**


|STLink|<--->|STM32F4|
|:-:|:-:|:-:|
|SWCLK|<--->|SWCLK|
|SWDIO|<--->|SWDIO|
|RST|<--->|NRST|
|GND|<--->|GND|
|5v|<--->|5V|


<p align="center">
    <img src="https://github.com/khoih-prog/BlynkEthernet_STM32_WM/blob/master/pics/STM32F407VET6.png">
</p>

---

#### 3. HOWTO use Serial Port for Debugging

Connect FDTI (USB to Serial) as follows:

|FDTI|<--->|STM32F4|
|:-:|:-:|:-:|
|RX|<--->|TX=PA_9|
|TX|<--->|RX=PA_10|
|GND|<--->|GND|


---
---

### Examples

Also see examples: 
 1. [AM2315_W5100](examples/AM2315_W5100)
 2. [BI_Ethernet_Blynk](examples/BI_Ethernet_Blynk) 
 3. [BI_Ethernet_Blynk_Email](examples/BI_Ethernet_Blynk_Email) 
 4. [BI_Ethernet_WM_Config](examples/BI_Ethernet_WM_Config)
 5. [BlynkHTTPClient](examples/BlynkHTTPClient)
 6. [DHT11_W5100](examples/DHT11_W5100)
 7. [ENC28J60_Blynk](examples/ENC28J60_Blynk) 
 8. [ENC28J60_Blynk_Email](examples/ENC28J60_Blynk_Email) 
 9. [ENC28J60_WM_Config](examples/ENC28J60_WM_Config) 
10. [**EthernetENC_Blynk**](examples/EthernetENC_Blynk). New
11. [**EthernetENC_Blynk_Email**](examples/EthernetENC_Blynk_Email).New
12. [**EthernetENC_WM_Config**](examples/EthernetENC_WM_Config). New
13. [W5100_Blynk](examples/W5100_Blynk) 
14. [W5100_WM_Config](examples/W5100_WM_Config)
15. [W5100_Blynk_Email](examples/W5100_Blynk_Email)
16. [**LAN8720_Ethernet_Blynk**](examples/LAN8720_Ethernet_Blynk) 
17. [**LAN8720_Ethernet_Blynk_Email**](examples/LAN8720_Ethernet_Blynk_Email) 
18. [**LAN8720_Ethernet_WM_Config**](examples/LAN8720_Ethernet_WM_Config)

---

## So, how it works?

If no valid config data are stored in EEPROM (data verified by checksum), forced Config Portal (DoubleResetDetect, soft Config Portal request), it will switch to `Configuration Mode`. Connect to access point at the IP address displayed on Terminal or Router's DHCP server as in the following terminal output:

```
Start BI_Ethernet_Blynk on NUCLEO_F767ZI using LAN8742A Ethernet & STM32Ethernet Library
BlynkEthernet_STM32_WM v1.2.1

EEPROM size = 16384, start = 0
Flag read = 0xd0d01234
doubleResetDetected
ClearFlag write = 0xd0d04321
[2394] CCSum=0x2a68,RCSum=0x2a68
[2394] ChkCrR:CrCCsum=0x15bd,CrRCsum=0x15bd
[2398] CrCCsum=0x15bd,CrRCsum=0x15bd
[2401] ======= Start Stored Config Data =======
[2405] Hdr=LAN8742A,BName=F767ZI_BI
[2409] Svr=account.duckdns.org,Tok=token
[2414] Svr1=account.duckdns.org,Tok1=token1
[2421] Prt=8080,SIP=blank
[2423] MAC: FE-C6-B0-96-A9-DF
[10748] IP:192.168.2.163
[10748] bg:Stay forever in CP:DRD/MRD
[11875] CfgIP=192.168.2.163
F
Your stored Credentials :
MQTT Server = mqtt_server
Port = 1883
MQTT UserName = mqtt_user
MQTT PWD = mqtt_pwd
Subs Topics = Subs_Topics
Pubs Topics = Pubs_Topics
```

After you connected to, for example, `192.168.2.86`, the Browser will display the following picture:

<p align="center">
    <img src="https://github.com/khoih-prog/BlynkEthernet_STM32_WM/blob/master/pics/Selection_2.png">
</p>

Enter your credentials (Blynk Server and Port). If you prefer static IP, input it (for example `192.168.2.79`) in the corresponding field. Otherwise, just leave it `blank` or `nothing` to use auto IP assigned by DHCP server.

<p align="center">
    <img src="https://github.com/khoih-prog/BlynkEthernet_STM32_WM/blob/master/pics/Selection_3.png">
</p>

Then click `Save`. After the  board auto-restarted, you will see if it's connected to your Blynk server successfully as in the following terminal output:

```
Start BI_Ethernet_Blynk on NUCLEO_F767ZI using LAN8742A Ethernet & STM32Ethernet Library

EEPROM size = 16384, start = 0
Flag read = 0xd0d04321
No doubleResetDetected
SetFlag write = 0xd0d01234
[2408] CCSum=0x2a68,RCSum=0x2a68
[2408] ChkCrR:CrCCsum=0x15bd,CrRCsum=0x15bd
[2411] CrCCsum=0x15bd,CrRCsum=0x15bd
[2415] ======= Start Stored Config Data =======
[2419] Hdr=LAN8742A,BName=F767ZI_BI
[2422] Svr=account.duckdns.org,Tok=token
[2428] Svr1=account.duckdns.org,Tok1=token1
[2434] Prt=8080,SIP=blank
[2437] MAC: FE-C6-B0-96-A9-DF
[11054] IP:192.168.2.163
[11054] bg:ECon.TryB
[11054] 
    ___  __          __
   / _ )/ /_ _____  / /__
  / _  / / // / _ \/  '_/
 /____/_/\_, /_//_/_/\_\
        /___/ v0.6.1 on STM32 NUCLEO_F767ZI

[11067] BlynkArduinoClient.connect: Connecting to account.duckdns.org:8080
[11152] Ready (ping: 6ms).
[11219] Connected to BlynkServer=account.duckdns.org,Token=token
[11221] bg:EBCon
Conn2Blynk: server = account.duckdns.org, port = 8080
Token = token
IP = 192.168.2.163
Stop doubleResetDetecting
ClearFlag write = 0xd0d04321
B
Your stored Credentials :
MQTT Server = mqtt_server
Port = 1883
MQTT UserName = mqtt_user
MQTT PWD = mqtt_pwd
Subs Topics = Subs_Topics
Pubs Topics = Pubs_Topics
BBBBBBBBBB BBBBBBBBBB BBBBBBBBBB
```

This library's `Blynk.begin()` is not a blocking call, so you can use it for critical functions requiring in loop(). 
Anyway, this is better for projects using Blynk just for GUI (graphical user interface).

In operation, if Ethernet or Blynk connection is lost, `Blynk.run()` will try reconnecting automatically. Therefore, `Blynk.run()` must be called in the `loop()` function. Don't use:

```cpp
void loop()
{
  if (Blynk.connected())
     Blynk.run();
     
  ...
}
```

just

```cpp
void loop()
{
  Blynk.run();
  ...
}
```

---
---

### Example [BI_Ethernet_Blynk](examples/BI_Ethernet_Blynk) 

#### 1. File [BI_Ethernet_Blynk.ino](examples/BI_Ethernet_Blynk/BI_Ethernet_Blynk.ino)

```
#include "defines.h"
#include "Credentials.h"
#include "dynamicParams.h"

#include <SPI.h>

#define BLYNK_PIN_FORCED_CONFIG           V10
#define BLYNK_PIN_FORCED_PERS_CONFIG      V20

// Use button V10 (BLYNK_PIN_FORCED_CONFIG) to forced Config Portal
BLYNK_WRITE(BLYNK_PIN_FORCED_CONFIG)
{ 
  if (param.asInt())
  {
    Serial.println( F("\nCP Button Hit. Rebooting") ); 

    // This will keep CP once, clear after reset, even you didn't enter CP at all.
    Blynk.resetAndEnterConfigPortal(); 
  }
}

// Use button V20 (BLYNK_PIN_FORCED_PERS_CONFIG) to forced Persistent Config Portal
BLYNK_WRITE(BLYNK_PIN_FORCED_PERS_CONFIG)
{ 
  if (param.asInt())
  {
    Serial.println( F("\nPersistent CP Button Hit. Rebooting") ); 
   
    // This will keep CP forever, until you successfully enter CP, and Save data to clear the flag.
    Blynk.resetAndEnterConfigPortalPersistent();
  }
}

void heartBeatPrint()
{
  static int num = 1;

  if (Blynk.connected())
    Serial.print(F("B"));
  else
    Serial.print(F("F"));

  if (num == 80)
  {
    Serial.println();
    num = 1;
  }
  else if (num++ % 10 == 0)
  {
    Serial.print(F(" "));
  }
}

void check_status()
{
  static unsigned long checkstatus_timeout = 0;

#define STATUS_CHECK_INTERVAL     60000L

  // Send status report every STATUS_REPORT_INTERVAL (60) seconds: we don't need to send updates frequently if there is no status change.
  if ((millis() > checkstatus_timeout) || (checkstatus_timeout == 0))
  {
    heartBeatPrint();
    checkstatus_timeout = millis() + STATUS_CHECK_INTERVAL;
  }
}

void setup()
{
  // Debug console
  Serial.begin(115200);
  while (!Serial);

  delay(200);
  
  Serial.print(F("\nStart BI_Ethernet_Blynk on ")); Serial.print(BOARD_NAME);
  Serial.print(F(" using ")); Serial.println(SHIELD_TYPE);
  Serial.println(BLYNK_ETHERNET_STM32_WM_VERSION);
  
#if !(USE_BUILTIN_ETHERNET || USE_UIP_ETHERNET)
  pinMode(SDCARD_CS, OUTPUT);
  digitalWrite(SDCARD_CS, HIGH); // Deselect the SD card
#endif

#if USE_BLYNK_WM
  Blynk.begin();
#else
#if USE_LOCAL_SERVER
  Blynk.begin(auth, server, BLYNK_HARDWARE_PORT);
#else
  Blynk.begin(auth);
  // You can also specify server:
  //Blynk.begin(auth, server, BLYNK_HARDWARE_PORT);
#endif
#endif

  if (Blynk.connected())
  {
#if USE_BLYNK_WM
    Serial.print(F("Conn2Blynk: server = "));
    Serial.print(Blynk.getServerName());
    Serial.print(F(", port = "));
    Serial.println(Blynk.getHWPort());
    Serial.print(F("Token = "));
    Serial.println(Blynk.getToken());
#endif
    Serial.print(F("IP = "));
    Serial.println(Ethernet.localIP());
  }
}

#if (USE_BLYNK_WM && USE_DYNAMIC_PARAMETERS)
void displayCredentials()
{
  Serial.println(F("\nYour stored Credentials :"));

  for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
  {
    Serial.print(myMenuItems[i].displayName);
    Serial.print(F(" = "));
    Serial.println(myMenuItems[i].pdata);
  }
}
#endif

void loop()
{
  Blynk.run();
  check_status();

#if (USE_BLYNK_WM && USE_DYNAMIC_PARAMETERS)
  static bool displayedCredentials = false;

  if (!displayedCredentials)
  {
    for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
    {
      if (!strlen(myMenuItems[i].pdata))
      {
        break;
      }

      if ( i == (NUM_MENU_ITEMS - 1) )
      {
        displayedCredentials = true;
        displayCredentials();
      }
    }
  }
#endif    
}
```

#### 2. File [defines.h](examples/W5500_Blynk/defines.h)

```
#ifndef defines_h
#define defines_h

#if !( defined(STM32F0) || defined(STM32F1) || defined(STM32F2) || defined(STM32F3)  ||defined(STM32F4) || defined(STM32F7) || \
       defined(STM32L0) || defined(STM32L1) || defined(STM32L4) || defined(STM32H7)  ||defined(STM32G0) || defined(STM32G4) || \
       defined(STM32WB) || defined(STM32MP1) )
  #error This code is designed to run on STM32F/L/H/G/WB/MP1 platform! Please check your Tools->Board setting.
#endif

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

#define DEBUG_ETHERNET_WEBSERVER_PORT       Serial

// Debug Level from 0 to 4
#define BLYNK_WM_DEBUG                      1
#define _ETHERNET_WEBSERVER_LOGLEVEL_       2

#define DRD_GENERIC_DEBUG                   true

// If USE_BUILTIN_ETHERNET == false and USE_UIP_ETHERNET == false => 
// either use W5x00 with EthernetXYZ library
// or ENC28J60 with EthernetENC library
#define USE_BUILTIN_ETHERNET    true
#define USE_UIP_ETHERNET        false

// To override the default CS/SS pin. Don't use unless you know exactly which pin to use
// You can define here or customize for each board at same place with BOARD_TYPE
//#define USE_THIS_SS_PIN   22  //21  //5 //4 //2 //15
// Default pin 10 to SS/CS. To change according to your board, if necessary
#define USE_THIS_SS_PIN       10

#if !(USE_BUILTIN_ETHERNET || USE_UIP_ETHERNET)
  // Only one if the following to be true
  #define USE_ETHERNET          false
  #define USE_ETHERNET2         false
  #define USE_ETHERNET3         false
  #define USE_ETHERNET_LARGE    false
  #define USE_ETHERNET_ENC      false
  #define USE_CUSTOM_ETHERNET   false
#endif

#if ( USE_ETHERNET2 || USE_ETHERNET3 || USE_ETHERNET_LARGE || USE_ETHERNET_ENC )
  #ifdef USE_CUSTOM_ETHERNET
    #undef USE_CUSTOM_ETHERNET
  #endif
  #define USE_CUSTOM_ETHERNET   false //true
#endif

#if (USE_BUILTIN_ETHERNET)
  #warning Using LAN8742A Ethernet & STM32Ethernet lib
  #define SHIELD_TYPE           "LAN8742A Ethernet & STM32Ethernet Library"
#elif (USE_UIP_ETHERNET)
  #warning Using ENC28J60 & UIPEthernet lib
  #define SHIELD_TYPE           "ENC28J60 & UIPEthernet Library"
#elif USE_ETHERNET3
  //#include "Ethernet3.h"
  #warning Using W5x00 & Ethernet3 lib
  #define SHIELD_TYPE           "W5x00 & Ethernet3 Library"
#elif USE_ETHERNET2
  //#include "Ethernet2.h"
  #warning Using W5x00 & Ethernet2 lib
  #define SHIELD_TYPE           "W5x00 & Ethernet2 Library"
#elif USE_ETHERNET_LARGE
  //#include "EthernetLarge.h"
  #warning Using W5x00 & EthernetLarge lib
  #define SHIELD_TYPE           "W5x00 & EthernetLarge Library"
#elif USE_ETHERNET_ENC
  //#include "EthernetENC.h"
  #warning Using ENC28J60 & EthernetENC lib
  #define SHIELD_TYPE           "ENC28J60 & EthernetENC Library"
#elif USE_CUSTOM_ETHERNET
  //#include "Ethernet_XYZ.h"
  #include "EthernetENC.h"
  #warning Using Custom Ethernet library. You must include a library and initialize.
  #define SHIELD_TYPE           "Custom Ethernet & Ethernet_XYZ Library"
#else
  #define USE_ETHERNET          true
  //#include "Ethernet.h"
  #warning Using Ethernet lib
  #define SHIELD_TYPE           "W5x00 & Ethernet Library"
#endif

#define BLYNK_NO_YIELD

// Start location in emulated-EEPROM to store config data. Default 0.
// Config data Size currently is 128 bytes w/o chksum, 132 with chksum)
#define EEPROM_START     0

#define USE_BLYNK_WM      true

#define USE_SSL           false

#if USE_BLYNK_WM

  #define USE_DYNAMIC_PARAMETERS                    true
 
  #if USE_SSL
    // Need ArduinoECCX08 and ArduinoBearSSL libraries
    // Currently, error not enough memory for many STM32 boards. Don't use
    #error SSL not support
  #else
    #if USE_BUILTIN_ETHERNET
      #include <BlynkSTM32BIEthernet_WM.h>
    #elif USE_UIP_ETHERNET
      #include <BlynkSTM32UIPEthernet_WM.h>
    #elif USE_ETHERNET_ENC
      #include <BlynkSTM32EthernetENC_WM.h>
    #else
      #include <BlynkSTM32Ethernet_WM.h>
    #endif
  #endif

#else   //USE_BLYNK_WM

  #if USE_BUILTIN_ETHERNET
    #include <BlynkSimple_STM32BI_Ethernet.h>
  #elif USE_UIP_ETHERNET
    #include <BlynkSimpleUIPEthernet.h>
  #else
    #include <BlynkSimpleEthernet.h>
  #endif
  
  #define USE_LOCAL_SERVER      true
  
  #if USE_LOCAL_SERVER
    char auth[] = "******";
    char server[] = "account.duckdns.org";
    //char server[] = "192.168.2.112";
  
  #else
    char auth[] = "******";
    char server[] = "blynk-cloud.com";
  #endif
  
  #define BLYNK_HARDWARE_PORT       8080

#endif    //USE_BLYNK_WM

#if !(USE_BUILTIN_ETHERNET || USE_UIP_ETHERNET)
  #define W5100_CS  10
  #define SDCARD_CS 4
#endif

#define BLYNK_HOST_NAME   "STM32-Master-Controller"

#endif      //defines_h
```

#### 3. File [Credentials.h](examples/W5500_Blynk/Credentials.h)

```
#ifndef Credentials_h
#define Credentials_h

#include "defines.h"

#if USE_BLYNK_WM

/// Start Default Config Data //////////////////

/*
  #define BLYNK_SERVER_MAX_LEN      32
#define BLYNK_TOKEN_MAX_LEN       36

typedef struct
{
  char blynk_server[BLYNK_SERVER_MAX_LEN];
  char blynk_token [BLYNK_TOKEN_MAX_LEN];
}  Blynk_Credentials;

#define NUM_BLYNK_CREDENTIALS     2

// Configurable items besides fixed Header
#define NUM_CONFIGURABLE_ITEMS    ( 3 + (2 * NUM_BLYNK_CREDENTIALS) )

typedef struct Configuration
{
  char header         [16];
  Blynk_Credentials Blynk_Creds [NUM_BLYNK_CREDENTIALS];
  int  blynk_port;
  char static_IP      [16];
  char board_name     [24];
  int  checkSum;
} Blynk_Configuration;
*/

#define TO_LOAD_DEFAULT_CONFIG_DATA      true

#if TO_LOAD_DEFAULT_CONFIG_DATA

bool LOAD_DEFAULT_CONFIG_DATA = false;

Blynk_Configuration defaultConfig =
{
  //char header[16], dummy, not used
#if USE_SSL
  "SSL",
#else
  "NonSSL",
#endif
  // Blynk_Credentials Blynk_Creds [NUM_BLYNK_CREDENTIALS];
  // Blynk_Creds.blynk_server and Blynk_Creds.blynk_token
  "account.duckdns.org",  "token1",
  "blynk-cloud.com",     "<<my real Blynk auth>>",
  //int  blynk_port;
#if USE_SSL
  9443,
#else
  8080,
#endif
  // char static_IP      [16];
  //"192.168.2.230",
  // Use dynamic DHCP IP
  "",
  //char board_name     [24];
  "Air-Control",
  // terminate the list
  //int  checkSum, dummy, not used
  0
  /////////// End Default Config Data /////////////
};

#else

bool LOAD_DEFAULT_CONFIG_DATA = false;

Blynk_Configuration defaultConfig;

#endif    // TO_LOAD_DEFAULT_CONFIG_DATA

/////////// End Default Config Data /////////////

#else     //#if USE_BLYNK_WM

#define USE_LOCAL_SERVER      true

#if USE_LOCAL_SERVER
char auth[] = "******";
char server[] = "account.duckdns.org";
//char server[] = "192.168.2.112";
#else
char auth[] = "******";
char server[] = "blynk-cloud.com";
#endif

#define BLYNK_HARDWARE_PORT       8080

#endif      //#if USE_BLYNK_WM

#endif    //Credentials_h
```

#### 4. File [dynamicParams.h](examples/W5500_Blynk/dynamicParams.h)

```
#ifndef dynamicParams_h
#define dynamicParams_h

#include "defines.h"

#if USE_BLYNK_WM

#if (USE_DYNAMIC_PARAMETERS)
  #warning USE_DYNAMIC_PARAMETERS
#endif

// USE_DYNAMIC_PARAMETERS defined in defined.h

/////////////// Start dynamic Credentials ///////////////

//Defined in BlynkEthernet_WM.h, <BlynkEthernet_ESP8266_WM.h>, <BlynkEthernet_ESP32 or_WM.h>
/**************************************
  #define MAX_ID_LEN                5
  #define MAX_DISPLAY_NAME_LEN      16

  typedef struct
  {
  char id             [MAX_ID_LEN + 1];
  char displayName    [MAX_DISPLAY_NAME_LEN + 1];
  char *pdata;
  uint8_t maxlen;
  } MenuItem;
**************************************/

#if USE_DYNAMIC_PARAMETERS

#define MAX_MQTT_SERVER_LEN      34
char MQTT_Server  [MAX_MQTT_SERVER_LEN + 1]   = "default-mqtt-server";

#define MAX_MQTT_PORT_LEN        6
char MQTT_Port   [MAX_MQTT_PORT_LEN + 1]  = "1883";

#define MAX_MQTT_USERNAME_LEN      34
char MQTT_UserName  [MAX_MQTT_USERNAME_LEN + 1]   = "default-mqtt-username";

#define MAX_MQTT_PW_LEN        34
char MQTT_PW   [MAX_MQTT_PW_LEN + 1]  = "default-mqtt-password";

#define MAX_MQTT_SUBS_TOPIC_LEN      34
char MQTT_SubsTopic  [MAX_MQTT_SUBS_TOPIC_LEN + 1]   = "default-mqtt-SubTopic";

#define MAX_MQTT_PUB_TOPIC_LEN       34
char MQTT_PubTopic   [MAX_MQTT_PUB_TOPIC_LEN + 1]  = "default-mqtt-PubTopic";

MenuItem myMenuItems [] =
{
  { "mqtt", "MQTT Server",      MQTT_Server,      MAX_MQTT_SERVER_LEN },
  { "mqpt", "Port",             MQTT_Port,        MAX_MQTT_PORT_LEN   },
  { "user", "MQTT UserName",    MQTT_UserName,    MAX_MQTT_USERNAME_LEN },
  { "mqpw", "MQTT PWD",         MQTT_PW,          MAX_MQTT_PW_LEN },
  { "subs", "Subs Topics",      MQTT_SubsTopic,   MAX_MQTT_SUBS_TOPIC_LEN },
  { "pubs", "Pubs Topics",      MQTT_PubTopic,    MAX_MQTT_PUB_TOPIC_LEN },
};

uint16_t NUM_MENU_ITEMS = sizeof(myMenuItems) / sizeof(MenuItem);  //MenuItemSize;

#else

MenuItem myMenuItems [] = {};

uint16_t NUM_MENU_ITEMS = 0;
#endif


/////// // End dynamic Credentials ///////////

#endif      //#if USE_BLYNK_WM


#endif      //dynamicParams_h
```


---
---

### Debug Terminal Output Samples

### 1. BI_Ethernet_Blynk on NUCLEO_F767ZI using LAN8742A Ethernet and STM32Ethernet Library

The following is the sample terminal output when running example [BI_Ethernet_Blynk](examples/BI_Ethernet_Blynk) on Nucleo-144 F767ZI with built-in LAN8742A Ethernet using STM32Ethernet Library.

#### 1.1 No DoubleReset Detected => Running normally

```
Start BI_Ethernet_Blynk on NUCLEO_F767ZI using LAN8742A Ethernet & STM32Ethernet Library
BlynkEthernet_STM32_WM v1.2.1

EEPROM size = 16384, start = 0
Flag read = 0xd0d04321
No doubleResetDetected
SetFlag write = 0xd0d01234
[2408] CCSum=0x2a68,RCSum=0x2a68
[2408] ChkCrR:CrCCsum=0x15bd,CrRCsum=0x15bd
[2411] CrCCsum=0x15bd,CrRCsum=0x15bd
[2415] ======= Start Stored Config Data =======
[2419] Hdr=LAN8742A,BName=F767ZI_BI
[2422] Svr=account.duckdns.org,Tok=token
[2428] Svr1=account.duckdns.org,Tok1=token1
[2434] Prt=8080,SIP=blank
[2437] MAC: FE-C6-B0-96-A9-DF
[11054] IP:192.168.2.163
[11054] bg:ECon.TryB
[11054] 
    ___  __          __
   / _ )/ /_ _____  / /__
  / _  / / // / _ \/  '_/
 /____/_/\_, /_//_/_/\_\
        /___/ v0.6.1 on STM32 NUCLEO_F767ZI

[11067] BlynkArduinoClient.connect: Connecting to account.duckdns.org:8080
[11152] Ready (ping: 6ms).
[11219] Connected to BlynkServer=account.duckdns.org,Token=token
[11221] bg:EBCon
Conn2Blynk: server = account.duckdns.org, port = 8080
Token = token
IP = 192.168.2.163
Stop doubleResetDetecting
ClearFlag write = 0xd0d04321
B
Your stored Credentials :
MQTT Server = mqtt_server
Port = 1883
MQTT UserName = mqtt_user
MQTT PWD = mqtt_pwd
Subs Topics = Subs_Topics
Pubs Topics = Pubs_Topics
```

#### 1.2 DoubleReset Detected => Enter Config Portal


```
Start BI_Ethernet_Blynk on NUCLEO_F767ZI using LAN8742A Ethernet & STM32Ethernet Library
BlynkEthernet_STM32_WM v1.2.1

EEPROM size = 16384, start = 0
Flag read = 0xd0d01234
doubleResetDetected
ClearFlag write = 0xd0d04321
[2394] CCSum=0x2a68,RCSum=0x2a68
[2394] ChkCrR:CrCCsum=0x15bd,CrRCsum=0x15bd
[2398] CrCCsum=0x15bd,CrRCsum=0x15bd
[2401] ======= Start Stored Config Data =======
[2405] Hdr=LAN8742A,BName=F767ZI_BI
[2409] Svr=account.duckdns.org,Tok=token
[2414] Svr1=account.duckdns.org,Tok1=token1
[2421] Prt=8080,SIP=blank
[2423] MAC: FE-C6-B0-96-A9-DF
[10748] IP:192.168.2.163
[10748] bg:Stay forever in CP:DRD/MRD
[11875] CfgIP=192.168.2.163
F
Your stored Credentials :
MQTT Server = mqtt_server
Port = 1883
MQTT UserName = mqtt_user
MQTT PWD = mqtt_pwd
Subs Topics = Subs_Topics
Pubs Topics = Pubs_Topics
```

#### 1.3 Enter non-persistent ConfigPortal

```
CP Button Hit. Rebooting

Start BI_Ethernet_Blynk on NUCLEO_F767ZI using LAN8742A Ethernet & STM32Ethernet Library
BlynkEthernet_STM32_WM v1.2.1

EEPROM size = 16384, start = 0
Flag read = 0xd0d04321
No doubleResetDetected
SetFlag write = 0xd0d01234
[2409] CCSum=0x2a68,RCSum=0x2a68
[2409] ChkCrR:CrCCsum=0x15bd,CrRCsum=0x15bd
[2412] CrCCsum=0x15bd,CrRCsum=0x15bd
[2416] ======= Start Stored Config Data =======
[2420] Hdr=LAN8742A,BName=F767ZI_BI
[2423] Svr=account.duckdns.org,Tok=token
[2429] Svr1=account.duckdns.org,Tok1=token1
[2435] Prt=8080,SIP=blank
[2438] MAC: FE-C6-B0-96-A9-DF
[9055] IP:192.168.2.163
[9055] bg:Stay forever in CP:Forced-non-Persistent
[10193] CfgIP=192.168.2.163
Stop doubleResetDetecting
ClearFlag write = 0xd0d04321
F
Your stored Credentials :
MQTT Server = mqtt_server
Port = 1883
MQTT UserName = mqtt_user
MQTT PWD = mqtt_pwd
Subs Topics = Subs_Topics
Pubs Topics = Pubs_Topics
```

#### 1.4 Enter persistent ConfigPortal

```
Persistent CP Button Hit. Rebooting

Start BI_Ethernet_Blynk on NUCLEO_F767ZI using LAN8742A Ethernet & STM32Ethernet Library
BlynkEthernet_STM32_WM v1.2.1

EEPROM size = 16384, start = 0
Flag read = 0xd0d04321
No doubleResetDetected
SetFlag write = 0xd0d01234
[2406] CCSum=0x2a68,RCSum=0x2a68
[2406] ChkCrR:CrCCsum=0x15bd,CrRCsum=0x15bd
[2410] CrCCsum=0x15bd,CrRCsum=0x15bd
[2413] ======= Start Stored Config Data =======
[2418] Hdr=LAN8742A,BName=F767ZI_BI
[2421] Svr=account.duckdns.org,Tok=token
[2427] Svr1=account.duckdns.org,Tok1=token1
[2433] Prt=8080,SIP=blank
[2436] MAC: FE-C6-B0-96-A9-DF
[9552] IP:192.168.2.163
[9552] bg:Stay forever in CP:Forced-Persistent
[9552] CfgIP=192.168.2.163
F
Your stored Credentials :
MQTT Server = mqtt_server
Port = 1883
MQTT UserName = mqtt_user
MQTT PWD = mqtt_pwd
Subs Topics = Subs_Topics
Pubs Topics = Pubs_Topics
Stop doubleResetDetecting
ClearFlag write = 0xd0d04321
```

---

### 2. EthernetENC_Blynk on NUCLEO_F767ZI using ENC28J60 and EthernetENC Library

The following is the sample terminal output when running example [EthernetENC_Blynk](examples/EthernetENC_Blynk) on Nucleo-144 F767ZI with ENC28J60 using EthernetENC Library.

#### 2.1 No DoubleReset Detected => Running normally

```
Start EthernetENC_Blynk on NUCLEO_F767ZI using ENC28J60 & EthernetENC Library
BlynkEthernet_STM32_WM v1.2.1

EEPROM size = 16384, start = 0
Flag read = 0xd0d04321
No doubleResetDetected
SetFlag write = 0xd0d01234
[3244] CCSum=0x2e09,RCSum=0x2e09
[3244] ChkCrR:CrCCsum=0x15bd,CrRCsum=0x15bd
[3248] CrCCsum=0x15bd,CrRCsum=0x15bd
[3251] ======= Start Stored Config Data =======
[3256] Hdr=ENC28J60,BName=F767ZI_UIPEthernet
[3260] Svr=account.duckdns.org,Tok=token
[3266] Svr1=account.duckdns.org,Tok1=token1
[3272] Prt=8080,SIP=blank
[3274] MAC: FE-C6-B0-96-A9-DF
[9054] IP:192.168.2.163
[9054] bg:ECon.TryB
[9054] 
    ___  __          __
   / _ )/ /_ _____  / /__
  / _  / / // / _ \/  '_/
 /____/_/\_, /_//_/_/\_\
        /___/ v0.6.1 on STM32 NUCLEO_F767ZI

[9066] BlynkArduinoClient.connect: Connecting to account.duckdns.org:8080
[9152] Ready (ping: 6ms).
[9219] Connected to BlynkServer=account.duckdns.org,Token=token
[9221] bg:EBCon
Conn2Blynk: server = account.duckdns.org, port = 8080
Token = token1
IP = 192.168.2.163
Stop doubleResetDetecting
ClearFlag write = 0xd0d04321
B
Your stored Credentials :
MQTT Server = mqtt_server
Port = 1883
MQTT UserName = mqtt_user
MQTT PWD = mqtt_pwd
Subs Topics = Subs_Topics
Pubs Topics = Pubs_Topics
```

#### 2.2 DoubleReset Detected => Enter Config Portal


```
Start EthernetENC_Blynk on NUCLEO_F767ZI using ENC28J60 & EthernetENC Library
BlynkEthernet_STM32_WM v1.2.1

EEPROM size = 16384, start = 0
Flag read = 0xd0d01234
doubleResetDetected
ClearFlag write = 0xd0d04321
[3266] CCSum=0x2e09,RCSum=0x2e09
[3266] ChkCrR:CrCCsum=0x15bd,CrRCsum=0x15bd
[3270] CrCCsum=0x15bd,CrRCsum=0x15bd
[3274] ======= Start Stored Config Data =======
[3278] Hdr=ENC28J60,BName=F767ZI_UIPEthernet
[3282] Svr=account.duckdns.org,Tok=token
[3288] Svr1=account.duckdns.org,Tok1=token1
[3294] Prt=8080,SIP=blank
[3296] MAC: FE-C6-B0-96-A9-DF
[8619] IP:192.168.2.163
[8619] bg:Stay forever in CP:DRD/MRD
[9641] CfgIP=192.168.2.163
F
Your stored Credentials :
MQTT Server = mqtt_server
Port = 1883
MQTT UserName = mqtt_user
MQTT PWD = mqtt_pwd
Subs Topics = Subs_Topics
Pubs Topics = Pubs_Topics
```

#### 2.3 Enter non-persistent ConfigPortal

```
CP Button Hit. Rebooting

Start EthernetENC_Blynk on NUCLEO_F767ZI using ENC28J60 & EthernetENC Library
BlynkEthernet_STM32_WM v1.2.1

EEPROM size = 16384, start = 0
Flag read = 0xd0d04321
No doubleResetDetected
SetFlag write = 0xd0d01234
[3259] CCSum=0x2e09,RCSum=0x2e09
[3259] ChkCrR:CrCCsum=0x15bd,CrRCsum=0x15bd
[3263] CrCCsum=0x15bd,CrRCsum=0x15bd
[3266] ======= Start Stored Config Data =======
[3271] Hdr=ENC28J60,BName=F767ZI_UIPEthernet
[3275] Svr=account.duckdns.org,Tok=token
[3281] Svr1=account.duckdns.org,Tok1=token1
[3287] Prt=8080,SIP=blank
[3289] MAC: FE-C6-B0-96-A9-DF
[4461] IP:192.168.2.163
[4461] bg:Stay forever in CP:Forced-non-Persistent
[4524] CfgIP=192.168.2.163
F
Your stored Credentials :
MQTT Server = mqtt_server
Port = 1883
MQTT UserName = mqtt_user
MQTT PWD = mqtt_pwd
Subs Topics = Subs_Topics
Pubs Topics = Pubs_Topics
Stop doubleResetDetecting
ClearFlag write = 0xd0d04321
```

#### 2.4 Enter persistent ConfigPortal

```
Persistent CP Button Hit. Rebooting

Start EthernetENC_Blynk on NUCLEO_F767ZI using ENC28J60 & EthernetENC Library
BlynkEthernet_STM32_WM v1.2.1

EEPROM size = 16384, start = 0
Flag read = 0xd0d04321
No doubleResetDetected
SetFlag write = 0xd0d01234
[3169] CCSum=0x2e09,RCSum=0x2e09
[3169] ChkCrR:CrCCsum=0x15bd,CrRCsum=0x15bd
[3173] CrCCsum=0x15bd,CrRCsum=0x15bd
[3176] ======= Start Stored Config Data =======
[3181] Hdr=ENC28J60,BName=F767ZI_UIPEthernet
[3185] Svr=account.duckdns.org,Tok=token
[3191] Svr1=account.duckdns.org,Tok1=token1
[3197] Prt=8080,SIP=blank
[3199] MAC: FE-C6-B0-96-A9-DF
[8422] IP:192.168.2.163
[8422] bg:Stay forever in CP:Forced-Persistent
[8422] CfgIP=192.168.2.163
F
Your stored Credentials :
MQTT Server = mqtt_server
Port = 1883
MQTT UserName = mqtt_user
MQTT PWD = mqtt_pwd
Subs Topics = Subs_Topics
Pubs Topics = Pubs_Topics
Stop doubleResetDetecting
ClearFlag write = 0xd0d04321
FFFFFFFFF FFFFFFFFFF FF[1322491] h:UpdEEPROM
[1322491] SaveEEPROM,Sz=16384,DataSz=380,WCSum=0x2e09
[1324544] CrCCSum=0x15bd
[1325574] h:Rst
```

#### 2.5. Lost Blynk Server => autoreconnect to another Blynk Server

```
Start EthernetENC_Blynk on NUCLEO_F767ZI using ENC28J60 & EthernetENC Library
BlynkEthernet_STM32_WM v1.2.1

EEPROM size = 16384, start = 0
Flag read = 0xd0d04321
No doubleResetDetected
SetFlag write = 0xd0d01234
[1337] CCSum=0x25aa,RCSum=0x25aa
[1337] ChkCrR:CrCCsum=0x15bd,CrRCsum=0x15bd
[1340] CrCCsum=0x15bd,CrRCsum=0x15bd
[1344] ======= Start Stored Config Data =======
[1348] Hdr=ENC28J60,BName=F767ZI_UIPEthernet
[1352] Svr=192.168.2.112,Tok=token
[1358] Svr1=192.168.2.32,Tok1=token1
[1363] Prt=8080,SIP=blank
[1366] MAC: FE-C6-B0-96-A9-DF
[6589] IP:192.168.2.163
[6589] bg:ECon.TryB
[6589] Try connecting to BlynkServer=192.168.2.112,Token=token
[6595] 
    ___  __          __
   / _ )/ /_ _____  / /__
  / _  / / // / _ \/  '_/
 /____/_/\_, /_//_/_/\_\
        /___/ v0.6.1 on STM32 NUCLEO_F767ZI

[6610] BlynkArduinoClient.connect: Connecting to 192.168.2.112:8080
[7302] Ready (ping: 92ms).
[7369] Connected to BlynkServer=192.168.2.112,Token=token
[7371] bg:EBCon
Conn2Blynk: server = 192.168.2.112, port = 8080
Token = token
IP = 192.168.2.163
B
Your stored Credentials :
MQTT Server = mqtt_server
Port = 1883
MQTT UserName = mqtt_user
MQTT PWD = mqtt_pwd
Subs Topics = Subs_Topics
Pubs Topics = Pubs_Topics
Stop doubleResetDetecting
ClearFlag write = 0xd0d04321
[36377] Heartbeat timeout
[36377] r:BLost.TryB
[36377] Try connecting to BlynkServer=192.168.2.112,Token=token
[36384] 
    ___  __          __
   / _ )/ /_ _____  / /__
  / _  / / // / _ \/  '_/
 /____/_/\_, /_//_/_/\_\
        /___/ v0.6.1 on STM32 NUCLEO_F767ZI

[36398] BlynkArduinoClient.connect: Connecting to 192.168.2.112:8080
[41405] Try connecting to BlynkServer=192.168.2.32,Token=token1
[41407] 
    ___  __          __
   / _ )/ /_ _____  / /__
  / _  / / // / _ \/  '_/
 /____/_/\_, /_//_/_/\_\
        /___/ v0.6.1 on STM32 NUCLEO_F767ZI

[41421] BlynkArduinoClient.connect: Connecting to 192.168.2.32:8080
[41586] Ready (ping: 20ms).
[41653] Connected to BlynkServer=192.168.2.32,Token=token1
[41655] r:BRecon
BBBBB
```

---

### 3. ENC28J60_Blynk on NUCLEO_F767ZI using ENC28J60 and UIPEthernet Library

The following is the sample terminal output when running example [ENC28J60_Blynk](examples/ENC28J60_Blynk) on Nucleo-144 F767ZI with ENC28J60 using UIPEthernet Library.

#### 3.1 No DoubleReset Detected => Running normally

```
Start ENC28J60_Blynk on NUCLEO_F767ZI using ENC28J60 & UIPEthernet Library
BlynkEthernet_STM32_WM v1.2.1

EEPROM size = 16384, start = 0
Flag read = 0xd0d04321
No doubleResetDetected
SetFlag write = 0xd0d01234
[2202] CCSum=0x2e09,RCSum=0x2e09
[2202] ChkCrR:CrCCsum=0x15bd,CrRCsum=0x15bd
[2205] CrCCsum=0x15bd,CrRCsum=0x15bd
[2209] ======= Start Stored Config Data =======
[2213] Hdr=ENC28J60,BName=F767ZI_UIPEthernet
[2217] Svr=account.duckdns.org,Tok=token
[2223] Svr1=account.duckdns.org,Tok1=token1
[2229] Prt=8080,SIP=blank
[2232] MAC: FE-C6-B0-96-A9-DF
ENC28J60_CONTROL_CS =10
SS =10
SPI_MOSI =11
SPI_MISO =12
SPI_SCK =13
[7477] IP:192.168.2.163
[7477] bg:ECon.TryB
[7477] 
    ___  __          __
   / _ )/ /_ _____  / /__
  / _  / / // / _ \/  '_/
 /____/_/\_, /_//_/_/\_\
        /___/ v0.6.1 on STM32 NUCLEO_F767ZI

[7490] BlynkArduinoClient.connect: Connecting to account.duckdns.org:8080
[8263] Ready (ping: 14ms).
[8330] Connected to BlynkServer=account.duckdns.org,Token=token
[8332] bg:EBCon
Conn2Blynk: server = account.duckdns.org, port = 8080
Token = token
IP = 192.168.2.163
B
Your stored Credentials :
MQTT Server = mqtt_server
Port = 1883
MQTT UserName = mqtt_user
MQTT PWD = mqtt_pwd
Subs Topics = Subs_Topics
Pubs Topics = Pubs_Topics
Stop doubleResetDetecting
ClearFlag write = 0xd0d04321
BBBBBBBBB
```

#### 3.2 DoubleReset Detected => Enter Config Portal


```
Start ENC28J60_Blynk on NUCLEO_F767ZI using ENC28J60 & UIPEthernet Library
BlynkEthernet_STM32_WM v1.2.1

EEPROM size = 16384, start = 0
Flag read = 0xd0d01234
doubleResetDetected
ClearFlag write = 0xd0d04321
[3245] CCSum=0xecf,RCSum=0xecf
[3245] ChkCrR:CrCCsum=0xc30,CrRCsum=0xc30
[3248] CrCCsum=0xc30,CrRCsum=0xc30
[3251] ======= Start Stored Config Data =======
[3256] Hdr=ENC28J60,BName=blank
[3259] Svr=blank,Tok=blank
[3261] Svr1=blank,Tok1=blank
[3264] Prt=8080,SIP=blank
[3266] MAC: FE-C9-A1-8E-D4-B7
ENC28J60_CONTROL_CS =10
SS =10
SPI_MOSI =11
SPI_MISO =12
SPI_SCK =13
[4460] IP:192.168.2.162
[4460] bg:Stay forever in CP:DRD/MRD
[4523] CfgIP=192.168.2.162
F
Your stored Credentials :
MQTT Server = blank
Port = blank
MQTT UserName = blank
MQTT PWD = blank
Subs Topics = blank
Pubs Topics = blank
FF

Your stored Credentials :
MQTT Server = blank
Port = blank
MQTT UserName = blank
MQTT PWD = blank
Subs Topics = blank
Pubs Topics = blank
FFF[233631] h:UpdEEPROM
[233631] SaveEEPROM,Sz=16384,DataSz=380,WCSum=0x2e09
[235667] CrCCSum=0x15bd
[235667] h:Rst
```

#### 3.3 Enter non-persistent ConfigPortal

```
CP Button Hit. Rebooting

Start ENC28J60_Blynk on NUCLEO_F767ZI using ENC28J60 & UIPEthernet Library
BlynkEthernet_STM32_WM v1.2.1

EEPROM size = 16384, start = 0
Flag read = 0xd0d04321
No doubleResetDetected
SetFlag write = 0xd0d01234
[2297] CCSum=0x2e09,RCSum=0x2e09
[2297] ChkCrR:CrCCsum=0x15bd,CrRCsum=0x15bd
[2300] CrCCsum=0x15bd,CrRCsum=0x15bd
[2304] ======= Start Stored Config Data =======
[2308] Hdr=ENC28J60,BName=F767ZI_UIPEthernet
[2312] Svr=account.duckdns.org,Tok=token
[2318] Svr1=account.duckdns.org,Tok1=token1
[2324] Prt=8080,SIP=blank
[2327] MAC: FE-C6-B0-96-A9-DF
ENC28J60_CONTROL_CS =10
SS =10
SPI_MOSI =11
SPI_MISO =12
SPI_SCK =13
[3520] IP:192.168.2.163
[3520] bg:Stay forever in CP:Forced-non-Persistent
[4544] CfgIP=192.168.2.163
F
Your stored Credentials :
MQTT Server = mqtt_server
Port = 1883
MQTT UserName = mqtt_user
MQTT PWD = mqtt_pwd
Subs Topics = Subs_Topics
Pubs Topics = Pubs_Topics
Stop doubleResetDetecting
ClearFlag write = 0xd0d04321
```

#### 3.4 Enter persistent ConfigPortal

```
Persistent CP Button Hit. Rebooting

Start ENC28J60_Blynk on NUCLEO_F767ZI using ENC28J60 & UIPEthernet Library
BlynkEthernet_STM32_WM v1.2.1

EEPROM size = 16384, start = 0
Flag read = 0xd0d04321
No doubleResetDetected
SetFlag write = 0xd0d01234
[2298] CCSum=0x2e09,RCSum=0x2e09
[2298] ChkCrR:CrCCsum=0x15bd,CrRCsum=0x15bd
[2301] CrCCsum=0x15bd,CrRCsum=0x15bd
[2305] ======= Start Stored Config Data =======
[2309] Hdr=ENC28J60,BName=F767ZI_UIPEthernet
[2313] Svr=account.duckdns.org,Tok=token
[2319] Svr1=account.duckdns.org,Tok1=token1
[2325] Prt=8080,SIP=blank
[2328] MAC: FE-C6-B0-96-A9-DF
ENC28J60_CONTROL_CS =10
SS =10
SPI_MOSI =11
SPI_MISO =12
SPI_SCK =13
[7524] IP:192.168.2.163
[7524] bg:Stay forever in CP:Forced-Persistent
[7524] CfgIP=192.168.2.163
F
Your stored Credentials :
MQTT Server = mqtt_server
Port = 1883
MQTT UserName = mqtt_user
MQTT PWD = mqtt_pwd
Subs Topics = Subs_Topics
Pubs Topics = Pubs_Topics
Stop doubleResetDetecting
ClearFlag write = 0xd0d04321
```

---

---

### 4. W5100_Blynk on NUCLEO_F767ZI using W5x00 and EthernetLarge Library

The following is the sample terminal output when running example [W5100_Blynk](examples/W5100_Blynk) on Nucleo-144 F767ZI with W5x00 using EthernetLarge Library.

#### 4.1 No DoubleReset Detected => Running normally

```
Start W5100_Blynk on NUCLEO_F767ZI using W5x00 & EthernetLarge Library
BlynkEthernet_STM32_WM v1.2.1

EEPROM size = 16384, start = 0
Flag read = 0xd0d04321
No doubleResetDetected
SetFlag write = 0xd0d01234
[2380] CCSum=0x2a68,RCSum=0x2a68
[2380] ChkCrR:CrCCsum=0x15bd,CrRCsum=0x15bd
[2384] CrCCsum=0x15bd,CrRCsum=0x15bd
[2387] ======= Start Stored Config Data =======
[2392] Hdr=LAN8742A,BName=F767ZI_BI
[2395] Svr=account.duckdns.org,Tok=token
[2401] Svr1=account.duckdns.org,Tok1=token1
[2407] Prt=8080,SIP=blank
[2409] MAC: FE-C6-B0-96-A9-DF
_pinCS = 0
W5100 init, using SS_PIN_DEFAULT = 10, new ss_pin = 10, W5100Class::ss_pin = 10
W5100::init: W5500, SSIZE =8192
[4079] IP:192.168.2.163
[4079] bg:ECon.TryB
[4079] Try connecting to BlynkServer=account.duckdns.org,Token=token
[4086] 
    ___  __          __
   / _ )/ /_ _____  / /__
  / _  / / // / _ \/  '_/
 /____/_/\_, /_//_/_/\_\
        /___/ v0.6.1 on STM32 NUCLEO_F767ZI

[4100] BlynkArduinoClient.connect: Connecting to account.duckdns.org:8080
[4215] Ready (ping: 4ms).
[4282] Connected to BlynkServer=account.duckdns.org,Token=token
[4284] bg:EBCon
Conn2Blynk: server = account.duckdns.org, port = 8080
Token = token
IP = 192.168.2.163
B
Your stored Credentials :
MQTT Server = mqtt_server
Port = 1883
MQTT UserName = mqtt_user
MQTT PWD = mqtt_pwd
Subs Topics = Subs_Topics
Pubs Topics = Pubs_Topics
Stop doubleResetDetecting
ClearFlag write = 0xd0d04321
BBBBBBBBB B
```

#### 4.2 DoubleReset Detected => Enter Config Portal


```
Start W5100_Blynk on NUCLEO_F767ZI using W5x00 & EthernetLarge Library
BlynkEthernet_STM32_WM v1.2.1

EEPROM size = 16384, start = 0
Flag read = 0xd0d01234
doubleResetDetected
ClearFlag write = 0xd0d04321
[2327] CCSum=0x24d7,RCSum=0x24d7
[2327] ChkCrR:CrCCsum=0x15bd,CrRCsum=0x15bd
[2331] CrCCsum=0x15bd,CrRCsum=0x15bd
[2335] ======= Start Stored Config Data =======
[2339] Hdr=W5100,BName=F767ZI_UIPEthernet
[2343] Svr=192.168.2.112,Tok=token
[2348] Svr1=192.168.2.32,Tok1=token1
[2354] Prt=8080,SIP=blank
[2356] MAC: FE-C6-B0-96-A9-DF
_pinCS = 0
W5100 init, using SS_PIN_DEFAULT = 10, new ss_pin = 10, W5100Class::ss_pin = 10
W5100::init: W5500, SSIZE =8192
[4026] IP:192.168.2.163
[4026] bg:Stay forever in CP:DRD/MRD
[4042] CfgIP=192.168.2.163
F
Your stored Credentials :
MQTT Server = mqtt_server
Port = 1883
MQTT UserName = mqtt_user
MQTT PWD = mqtt_pwd
Subs Topics = Subs_Topics
Pubs Topics = Pubs_Topics
```

#### 4.3 Enter non-persistent ConfigPortal

```
CP Button Hit. Rebooting

Start W5100_Blynk on NUCLEO_F767ZI using W5x00 & EthernetLarge Library
BlynkEthernet_STM32_WM v1.2.1

EEPROM size = 16384, start = 0
Flag read = 0xd0d04321
No doubleResetDetected
SetFlag write = 0xd0d01234
[1335] CCSum=0x2a68,RCSum=0x2a68
[1335] ChkCrR:CrCCsum=0x15bd,CrRCsum=0x15bd
[1339] CrCCsum=0x15bd,CrRCsum=0x15bd
[1342] ======= Start Stored Config Data =======
[1347] Hdr=LAN8742A,BName=F767ZI_BI
[1350] Svr=account.duckdns.org,Tok=token
[1356] Svr1=account.duckdns.org,Tok1=token1
[1362] Prt=8080,SIP=blank
[1364] MAC: FE-C6-B0-96-A9-DF
_pinCS = 0
W5100 init, using SS_PIN_DEFAULT = 10, new ss_pin = 10, W5100Class::ss_pin = 10
W5100::init: W5500, SSIZE =8192
[3034] IP:192.168.2.163
[3034] bg:Stay forever in CP:Forced-non-Persistent
[4151] CfgIP=192.168.2.163
F
Your stored Credentials :
MQTT Server = mqtt_server
Port = 1883
MQTT UserName = mqtt_user
MQTT PWD = mqtt_pwd
Subs Topics = Subs_Topics
Pubs Topics = Pubs_Topics
```

#### 4.4 Enter persistent ConfigPortal

```
Persistent CP Button Hit. Rebooting

Start W5100_Blynk on NUCLEO_F767ZI using W5x00 & EthernetLarge Library
BlynkEthernet_STM32_WM v1.2.1

EEPROM size = 16384, start = 0
Flag read = 0xd0d04321
No doubleResetDetected
SetFlag write = 0xd0d01234
[2321] CCSum=0x2d36,RCSum=0x2d36
[2321] ChkCrR:CrCCsum=0x15bd,CrRCsum=0x15bd
[2325] CrCCsum=0x15bd,CrRCsum=0x15bd
[2328] ======= Start Stored Config Data =======
[2333] Hdr=W5100,BName=F767ZI_UIPEthernet
[2337] Svr=account.duckdns.org,Tok=token
[2343] Svr1=account.duckdns.org,Tok1=token1
[2349] Prt=8080,SIP=blank
[2351] MAC: FE-C6-B0-96-A9-DF
_pinCS = 0
W5100 init, using SS_PIN_DEFAULT = 10, new ss_pin = 10, W5100Class::ss_pin = 10
W5100::init: W5500, SSIZE =8192
[4021] IP:192.168.2.163
[4021] bg:Stay forever in CP:Forced-Persistent
[4021] CfgIP=192.168.2.163
F
Your stored Credentials :
MQTT Server = mqtt_server
Port = 1883
MQTT UserName = mqtt_user
MQTT PWD = mqtt_pwd
Subs Topics = Subs_Topics
Pubs Topics = Pubs_Topics
Stop doubleResetDetecting
ClearFlag write = 0xd0d04321
```

---

### 5. LAN8720_Ethernet_Blynk on STM32F4 BLACK_F407VE with LAN8720 Ethernet using STM32Ethernet Library

The following is the sample terminal output when running example [LAN8720_Ethernet_Blynk](examples/LAN8720_Ethernet_Blynk) on STM32F4 BLACK_F407VE with LAN8720 Ethernet using STM32Ethernet Library.

### 5.1. DoubleReset Detected => Enter Config Portal

```
Start LAN8720_Ethernet_Blynk on BLACK_F407VE using LAN8720 Ethernet & STM32Ethernet Library
BlynkEthernet_STM32_WM v1.2.1

EEPROM size = 16384, start = 0
Flag read = 0xd0d01234
doubleResetDetected
ClearFlag write = 0xd0d04321
[3053] CCSum=0x23bd,RCSum=0x0
[3053] ChkCrR:CrCCsum=0x8a73,CrRCsum=0xffffffff
[3057] InitCfgFile,Sz=200
[3060] InitCfgFile,DataSz=0
[3062] SaveEEPROM,Sz=16384,DataSz=0,WCSum=0xed0
[3101] CrCCSum=0xc30
[3101] MAC: FE-C9-A1-8E-D4-B7
[9229] IP:192.168.2.167
[9229] bg:Stay forever in CP:DRD/MRD
[9246] CfgIP=192.168.2.167
F
Your stored Credentials :
MQTT Server = blank
Port = blank
MQTT UserName = blank
MQTT PWD = blank
Subs Topics = blank
Pubs Topics = blank
FF[178269] h:UpdEEPROM
[178269] SaveEEPROM,Sz=16384,DataSz=0,WCSum=0x2a72
[178304] CrCCSum=0x15d7
[178304] h:Rst
```

### 5.2. Config Data Saved => Connect to Blynk

```
Start LAN8720_Ethernet_Blynk on BLACK_F407VE using LAN8720 Ethernet & STM32Ethernet Library
BlynkEthernet_STM32_WM v1.2.1

EEPROM size = 16384, start = 0
Flag read = 0xd0d04321
No doubleResetDetected
SetFlag write = 0xd0d01234
[3054] CCSum=0x2a72,RCSum=0x2a72
[3054] ChkCrR:CrCCsum=0x15d7,CrRCsum=0x15d7
[3058] CrCCsum=0x15d7,CrRCsum=0x15d7
[3061] ======= Start Stored Config Data =======
[3066] Hdr=LAN8742A,BName=BLACK_F407VE
[3070] Svr=account.duckdns.org,Tok=token1
[3076] Svr1=account.ddns.net,Tok1=token2
[3082] Prt=8080,SIP=192.168.2.167
[3086] connectEthernet: Use static_IP=192.168.2.167
[3091] MAC: FE-C6-B0-96-A9-DF
[5715] IP:192.168.2.167
[5715] bg:ECon.TryB
[5715] Try connecting to BlynkServer=account.duckdns.org,Token=token1
[5722] 
    ___  __          __
   / _ )/ /_ _____  / /__
  / _  / / // / _ \/  '_/
 /____/_/\_, /_//_/_/\_\
        /___/ v0.6.1 on STM32 BLACK_F407VE

[5813] Ready (ping: 7ms).
[5880] Connected to BlynkServer=account.duckdns.org,Token=token1
[5882] bg:EBCon
Conn2Blynk: server = account.duckdns.org, port = 8080
Token = token1
IP = 192.168.2.167
B
Your stored Credentials :
MQTT Server = mqtt_server
Port = 1883
MQTT UserName = mqtt-User
MQTT PWD = mqtt_pass
Subs Topics = Subs_Topics
Pubs Topics = Pubs_Topics
Stop doubleResetDetecting
ClearFlag write = 0xd0d04321
```


---
---

### Debug

Debug is enabled by default on Serial.

You can also change the debugging level from 0 to 4

```cpp
/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

#define DEBUG_ETHERNET_WEBSERVER_PORT       Serial

// Debug Level from 0 to 4
#define BLYNK_WM_DEBUG                      1
#define _ETHERNET_WEBSERVER_LOGLEVEL_       2

#define DRD_GENERIC_DEBUG                   true
```
---

### Troubleshooting

If you get compilation errors, more often than not, you may need to install a newer version of the core for Arduino boards.

Sometimes, the library will only work if you update the board core to the latest version because I am using newly added functions.


---
---

## Releases

### Releases v1.2.1

1. Add Packages' Patches for **STM32 core v2.0.0** to use LAN8720 with STM32Ethernet and LwIP libraries
2. Updated and tested with latest **STM32 core v2.0.0**

### Releases v1.2.0

1. Add support to **LAN8720** Ethernet for many **STM32F4** (F407xx, NUCLEO_F429ZI) and **STM32F7** (DISCO_F746NG, NUCLEO_F746ZG, NUCLEO_F756ZG) boards.
2. Add LAN8720 examples
3. Add Packages' Patches for STM32 to use LAN8720 with STM32Ethernet and LwIP libraries

### Releases v1.1.1

1. To permit autoreset after configurable timeout if DRD/MRD or non-persistent forced-CP. Check [**Good new feature: Blynk.resetAndEnterConfigPortal() Thanks & question #27**](https://github.com/khoih-prog/Blynk_WM/issues/27)

### Major Releases v1.1.0

1. Fix Config Portal Bug. 
2. Add functions to control Config Portal from software or Virtual Switches. Check [How to trigger a Config Portal from code #25](https://github.com/khoih-prog/Blynk_WM/issues/25)
3. Use more efficient [FlashStorage_STM32 Library](https://github.com/khoih-prog/FlashStorage_STM32) to save data to emulaled-EEPROM.
4. Add support to new [**`EthernetENC library`**](https://github.com/jandrassy/EthernetENC) for ENC28J60.


### Releases v1.0.4

1. New ***powerful-yet-simple-to-use feature to enable adding dynamic custom parameters*** from sketch and input using the same Config Portal. Config Portal will be auto-adjusted to match the number of dynamic parameters.
2. Dynamic custom parameters to be saved ***automatically in EEPROM***.
3. Permit to input special chars such as ***%*** and ***#*** into data fields.
4. MultiBlynk Servers and Tokens with Auto(Re)Connect feature.

### Releases v1.0.3
1. Reduce html and code size for faster Config Portal response. Enhance GUI.
2. Change default macAddress for boards to avoid macAddress conflict while simultaneously testing multiple boards.

### Releases v1.0.2

1. Fix crashing bug when using dynamic EthernetServer
2. Enhance examples, fix indentation, update README.md

### Releases v1.0.1

***New in this version***

1. Fix hanging bug in STM32 boards with built-in Ethernet LAN8742A.

### Releases v1.0.0

***New in this version***

1. Add support to STM32 boards with built-in Ethernet LAN8742A, ENC28J60 or W5x00 Ethernet shields 

---
---

### Issues

Submit issues to: [BlynkEthernet_STM32_WM issues](https://github.com/khoih-prog/BlynkEthernet_STM32_WM/issues)

---

### TO DO

 1. Same features for other boards with Ethernet shields.
 2. To write code and make SSL working. Currently, Ethernet SSL is not supported by Blynk code yet.
 

---

### DONE

 1. Permit EEPROM size and location configurable to avoid conflict with others.
 2. More flexible to configure reconnection timeout.
 3. For fresh config data, don't need to wait for connecting timeout before entering config portal.
 4. If the config data not entered completely (Server, HardwarePort and Blynk token), entering config portal
 5. Change Synch XMLHttpRequest to Async
 6. Reduce memory usage.
 7. Support W5x00, ENC28J60 Ethernet shield as well as built-in Ethernet LAN8742A
 8. Add checksums
 9. Support **STM32F/L/H/G/WB/MP1** boards
10. Add **MultiBlynk** features with Auto(Re)Connect to the available Server.
11. Easy-to-use **Dynamic Parameters** without the necessity to write complicated ArduinoJSon functions
12. Permit to input special chars such as ***%*** and ***#*** into data fields. 
13. Make **emulated-EEPROM** work on all STM32 boards
14. **DoubleDetectDetector** to force Config Portal when double reset is detected within predetermined time, default 10s.
15. Configurable Config Portal Title
16. Re-structure all examples to separate Credentials / Defines / Dynamic Params / Code so that you can change Credentials / Dynamic Params quickly for each device.
17. Add support to new [**`EthernetENC library`**](https://github.com/jandrassy/EthernetENC) for ENC28J60.
18. Add Table of Contents and Version String


---

### Contributions and Thanks

1. Thanks to [thorathome in GitHub](https://github.com/thorathome) to test, suggest and encourage to add those new features to [Blynk_WM](https://github.com/khoih-prog/Blynk_WM), such as Default Credentials/Dynamic Params, Configurable Config Portal Title, DRD. Those features are included in this library now.

<table>
  <tr>
    <td align="center"><a href="https://github.com/thorathome"><img src="https://github.com/thorathome.png" width="100px;" alt="thorathome"/><br /><sub><b>⭐️ Thor Johnson</b></sub></a><br /></td>
  </tr> 
</table>

---

## Contributing

If you want to contribute to this project:

- Report bugs and errors
- Ask for enhancements
- Create issues and pull requests
- Tell other people about this library

---

### License

- The library is licensed under [MIT](https://github.com/khoih-prog/BlynkEthernet_Manager/blob/master/LICENSE)

---


## Copyright

Copyright 2020- Khoi Hoang
