/****************************************************************************************************************************
   BlynkSTM32Ethernet_WM.h
   For STM32 running W5x00 Ethernet shields

   BlynkSTM32Ethernet_WM is a library for the STM32 running built-in Ethernet, ENC28J60 or W5x00 Ethernet shields
   to enable easy configuration/reconfiguration and autoconnect/autoreconnect to Blynk
   Forked from Blynk library v0.6.1 https://github.com/blynkkk/blynk-library/releases
   Built by Khoi Hoang https://github.com/khoih-prog/BlynkGSM_ESPManager
   Licensed under MIT license
   Version: 1.0.1

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
 *****************************************************************************************************************************/

#ifndef BlynkSTM32Ethernet_WM_h
#define BlynkSTM32Ethernet_WM_h

#ifndef BLYNK_INFO_CONNECTION
#define BLYNK_INFO_CONNECTION "W5100"
#endif

#include <Ethernet.h>
#include <EthernetClient.h>

#include <Adapters/BlynkEthernet_STM32_WM.h>

static EthernetClient _blynkEthernetClient;
static BlynkArduinoClient _blynkTransport(_blynkEthernetClient);
BlynkEthernet Blynk(_blynkTransport);

#include <BlynkWidgets.h>

#endif
