/****************************************************************************************************************************
  BlynkSimple_STM32BI_Ethernet.h
  For STM32 running LAN8720 and built-in LAN8742A Ethernet

  BlynkEthernet_STM32_WM is a library for the STM32 running built-in Ethernet, ENC28J60 or W5x00 Ethernet shields
  to enable easy configuration/reconfiguration and autoconnect/autoreconnect to Blynk
  Based on and modified from Blynk library v0.6.1 https://github.com/blynkkk/blynk-library/releases
  Built by Khoi Hoang https://github.com/khoih-prog/BlynkEthernet_STM32_WM
  Licensed under MIT license

  Version: 1.2.1

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.0.0   K Hoang      28/02/2020 Initial coding for STM32 running built-in Ethernet, ENC28J60 or W5x00 Ethernet shields
  1.0.1   K Hoang      03/03/2020 Fix bug for built-in Ethernet LAN8742A
  1.0.2   K Hoang      06/03/2020 Fix crashing bug when using dynamic EthernetServer
  1.0.3   K Hoang      10/03/2020 Reduce html and code size
  1.0.4   K Hoang      20/04/2020 Add MultiBlynk, dynamic parameters, special chars input
  1.1.0   K Hoang      30/01/2021 Fix ConfigPortal bug. Add software Config Portal request. Use FlashStorage_STM32.
  1.1.1   K Hoang      31/01/2021 To permit autoreset after timeout if DRD/MRD or non-persistent forced-CP
  1.2.0   K Hoang      22/04/2021 Add support to LAN8720 using STM32F4 or STM32F7
  1.2.1   K Hoang      22/04/2021 Add Packages' Patches for STM32 core v2.0.0 to use LAN8720
 *****************************************************************************************************************************/

#pragma once

#ifndef BlynkSimple_STM32BI_Ethernet_h
#define BlynkSimple_STM32BI_Ethernet_h

#if ( defined(STM32F0) || defined(STM32F1) || defined(STM32F2) || defined(STM32F3)  ||defined(STM32F4) || defined(STM32F7) || \
       defined(STM32L0) || defined(STM32L1) || defined(STM32L4) || defined(STM32H7)  ||defined(STM32G0) || defined(STM32G4) || \
       defined(STM32WB) || defined(STM32MP1) )
  #if defined(BLYNK_ETHERNET_USE_STM32)
    #undef BLYNK_ETHERNET_USE_STM32
  #endif
  #define BLYNK_ETHERNET_USE_STM32      true
#else
  #error This code is designed to run on STM32F/L/H/G/WB/MP1 platform! Please check your Tools->Board setting.
#endif

#ifndef BLYNK_ETHERNET_WM_VERSION
  #define BLYNK_ETHERNET_STM32_WM_VERSION     "BlynkEthernet_STM32_WM v1.2.1"
#endif

#ifndef BLYNK_INFO_CONNECTION
  #if USING_LAN8720
    #define BLYNK_INFO_CONNECTION "LAN8720"
  #else
    #define BLYNK_INFO_CONNECTION "LAN8742A"
  #endif  
#endif

#include <LwIP.h>
#include <STM32Ethernet.h>

#include <Adapters/Blynk_STM32BI_Ethernet.h>

static EthernetClient _blynkEthernetClient;
static BlynkArduinoClient _blynkTransport(_blynkEthernetClient);
BlynkEthernet Blynk(_blynkTransport);

#include <BlynkWidgets.h>

#endif    //BlynkSimple_STM32BI_Ethernet_h
