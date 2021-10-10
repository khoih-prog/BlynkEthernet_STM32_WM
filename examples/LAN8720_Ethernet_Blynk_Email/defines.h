/****************************************************************************************************************************
  defines.h
  
  BlynkEthernet_STM32_WM is a library for the STM32 running built-in Ethernet, ENC28J60 or W5x00 Ethernet shields
  to enable easy configuration/reconfiguration and autoconnect/autoreconnect to Blynk
  Based on and modified from Blynk library v0.6.1 https://github.com/blynkkk/blynk-library/releases
  Built by Khoi Hoang https://github.com/khoih-prog/BlynkEthernet_STM32_WM
  Licensed under MIT license
 *****************************************************************************************************************************/

#ifndef defines_h
#define defines_h

#if ( defined(ARDUINO_BLACK_F407VE) || defined(ARDUINO_BLACK_F407VG) || defined(ARDUINO_BLACK_F407ZE) || defined(ARDUINO_BLACK_F407ZG)  || \
      defined(ARDUINO_BLUE_F407VE_Mini) || defined(ARDUINO_DIYMORE_F407VGT) || defined(ARDUINO_FK407M1) || defined(ARDUINO_VCCGND_F407ZG_MINI) || \
      defined(ARDUINO_GENERIC_F407VETX) || defined(ARDUINO_GENERIC_F407VGTX) || defined(ARDUINO_GENERIC_F407ZETX) || defined(ARDUINO_GENERIC_F407ZGTX) || \
      defined(ARDUINO_GENERIC_F417VETX) || defined(ARDUINO_GENERIC_F417VGTX) || defined(ARDUINO_GENERIC_F417ZETX) || defined(ARDUINO_GENERIC_F417ZGTX) || \
      defined(ARDUINO_GENERIC_F427ZGTX) || defined(ARDUINO_GENERIC_F427ZITX) || defined(ARDUINO_GENERIC_F429ZETX) || defined(ARDUINO_GENERIC_F429ZGTX) || \
      defined(ARDUINO_GENERIC_F429ZGYX) || defined(ARDUINO_GENERIC_F429ZITX) || defined(ARDUINO_GENERIC_F429ZIYX) || defined(ARDUINO_GENERIC_F437ZGTX) || \
      defined(ARDUINO_GENERIC_F437ZITX) || defined(ARDUINO_GENERIC_F439ZGTX) || defined(ARDUINO_GENERIC_F439ZITX) || defined(ARDUINO_GENERIC_F439ZGYX) || \
      defined(ARDUINO_GENERIC_F439ZIYX) || defined(ARDUINO_DISCO_F746NG)     || defined(ARDUINO_NUCLEO_F746ZG)    || defined(ARDUINO_NUCLEO_F756ZG)    || \
      defined(ARDUINO_NUCLEO_H743ZI) )
  #if defined(ETHERNET_USE_STM32)
    #undef ETHERNET_USE_STM32
  #endif
  #define ETHERNET_USE_STM32         true
  #define USE_DYNAMIC_PARAMETERS      true
#else
  #error This code is designed to run on some STM32F4X7XX, STM32F4X9XX NUCLEO-F429ZI, STM32F746 and STM32F756 platform! Please check your Tools->Board setting.
#endif

// To suppress boolean warnings of old libraries
#define boolean   bool

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

#define DEBUG_ETHERNET_WEBSERVER_PORT       Serial

// Debug Level from 0 to 4
#define BLYNK_WM_DEBUG                      1
#define _ETHERNET_WEBSERVER_LOGLEVEL_       2

#define DRD_GENERIC_DEBUG                   true

#define USING_LAN8720         true

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
  #if USING_LAN8720
    #warning Using LAN8720 Ethernet & STM32Ethernet lib
    #define SHIELD_TYPE           "LAN8720 Ethernet & STM32Ethernet Library"
  #else
    #warning Using LAN8742A Ethernet & STM32Ethernet lib
    #define SHIELD_TYPE           "LAN8742A Ethernet & STM32Ethernet Library"
  #endif
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
