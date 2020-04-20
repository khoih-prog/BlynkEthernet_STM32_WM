/****************************************************************************************************************************
   BlynkSTM32BIEthernet_WM.h
   For STM32 running built-in Ethernet

   BlynkSTM32Ethernet_WM is a library for the STM32 running built-in Ethernet, ENC28J60 or W5x00 Ethernet shields
   to enable easy configuration/reconfiguration and autoconnect/autoreconnect to Blynk
   Forked from Blynk library v0.6.1 https://github.com/blynkkk/blynk-library/releases
   Built by Khoi Hoang https://github.com/khoih-prog/BlynkGSM_ESPManager
   Licensed under MIT license
   Version: 1.0.4

   Original Blynk Library author:
   @file       BlynkGsmClient.h
   @author     Volodymyr Shymanskyy
   @license    This project is released under the MIT License (MIT)
   @copyright  Copyright (c) 2015 Volodymyr Shymanskyy
   @date       Jan 2015
   @brief

   Version Modified By   Date      Comments
   ------- -----------  ---------- -----------
    1.0.0   K Hoang      28/02/2020 Initial coding for STM32 running built-in Ethernet, ENC28J60 or W5x00 Ethernet shields
    1.0.1   K Hoang      03/03/2020 Fix bug for built-in Ethernet LAN8742A
    1.0.2   K Hoang      06/03/2020 Fix crashing bug when using dynamic EthernetServer
    1.0.3   K Hoang      10/03/2020 Reduce html and code size
    1.0.4   K Hoang      20/04/2020 Add MultiBlynk, dynamic parameters, special chars input
 *****************************************************************************************************************************/

#ifndef BlynkSimpleEthernet_WM_h
#define BlynkSimpleEthernet_WM_h

#ifndef BLYNK_INFO_CONNECTION
#define BLYNK_INFO_CONNECTION "LAN8742A"
#endif

#include <LwIP.h>
#include <STM32Ethernet.h>

#include <Adapters/BlynkEthernet_STM32_WM.h>

static EthernetClient _blynkEthernetClient;
static BlynkArduinoClient _blynkTransport(_blynkEthernetClient);
BlynkEthernet Blynk(_blynkTransport);

#include <BlynkWidgets.h>

#endif
