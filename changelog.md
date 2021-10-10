## BlynkEthernet_STM32_WM

[![arduino-library-badge](https://www.ardu-badge.com/badge/BlynkEthernet_STM32_WM.svg?)](https://www.ardu-badge.com/BlynkEthernet_STM32_WM)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/BlynkEthernet_STM32_WM.svg)](https://github.com/khoih-prog/BlynkEthernet_STM32_WM/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/BlynkEthernet_STM32_WM/blob/master/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/BlynkEthernet_STM32_WM.svg)](http://github.com/khoih-prog/BlynkEthernet_STM32_WM/issues)

---
---

## Table of Contents

* [Changelog](#changelog)
  * [Releases v1.2.2](#releases-v122)
  * [Releases v1.2.1](#releases-v121)
  * [Releases v1.2.0](#releases-v120)
  * [Releases v1.1.1](#releases-v111)
  * [Major Releases v1.1.0](#major-releases-v110)
  * [Releases v1.0.4](#releases-v104)
  * [Releases v1.0.3](#releases-v103)
  * [Releases v1.0.2](#releases-v102)


---
---

## Changelog

### Releases v1.2.2

1. Update `platform.ini` and `library.json` to use original `khoih-prog` instead of `khoih.prog` after PIO fix
2. Update `Packages' Patches`


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


