/****************************************************************************************************************************
  Blynk_STM32BI_Ethernet.h
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

#ifndef Blynk_STM32BI_Ethernet_h
#define Blynk_STM32BI_Ethernet_h

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

#ifndef (BLYNK_ETHERNET_DEBUG)
  #define BLYNK_ETHERNET_DEBUG      0
#endif

#ifndef BLYNK_INFO_CONNECTION
  #if USING_LAN8720
    #define BLYNK_INFO_CONNECTION "LAN8720"
  #else
    #define BLYNK_INFO_CONNECTION "LAN8742A"
  #endif  
#endif

#ifdef BLYNK_USE_SSL
  #define BLYNK_SERVER_PORT BLYNK_DEFAULT_PORT_SSL
#else
  #define BLYNK_SERVER_PORT BLYNK_DEFAULT_PORT
#endif

#include <BlynkApiArduino.h>
#include <Blynk/BlynkProtocol.h>
#include <Adapters/BlynkArduinoClient.h>

class BlynkEthernet
    : public BlynkProtocol<BlynkArduinoClient>
{
    typedef BlynkProtocol<BlynkArduinoClient> Base;
public:
    BlynkEthernet(BlynkArduinoClient& transp)
        : Base(transp)
    {}

    void config(const char* auth,
                const char* domain = BLYNK_DEFAULT_DOMAIN,
                uint16_t    port   = BLYNK_SERVER_PORT)
    {
      // Base == BlynkProtocol.h
      Base::begin(auth);
      // conn == BlynkArduinoClient
      this->conn.begin(domain, port);
    }

    void config(const char* auth,
                IPAddress   ip,
                uint16_t    port = BLYNK_SERVER_PORT)
    {
        Base::begin(auth);
        this->conn.begin(ip, port);
    }

    // DHCP with domain
    void begin( const char* auth,
                const char* domain = BLYNK_DEFAULT_DOMAIN,
                uint16_t port      = BLYNK_SERVER_PORT,
                const byte mac[]   = NULL)
    {
#if (BLYNK_ETHERNET_DEBUG > 1)
      BLYNK_LOG1(BLYNK_F("GetIP:"));
#endif

        if (!Ethernet.begin(SelectMacAddress(auth, mac))) {
            BLYNK_FATAL(BLYNK_F("DHCP 0"));
        }
        // give the Ethernet shield a second to initialize:
        BlynkDelay(1000);
        IPAddress myip = Ethernet.localIP();
        BLYNK_LOG_IP("IP:", myip);

        config(auth, domain, port);
        while(this->connect() != true) {}
    }

    // Static IP with domain
    void begin( const char* auth,
                const char* domain,
                uint16_t port,
                IPAddress local,
                IPAddress dns,
                const byte mac[] = NULL)
    {
#if (BLYNK_ETHERNET_DEBUG > 1)
      BLYNK_LOG1(BLYNK_F("UseStatIP"));
#endif

        Ethernet.begin(SelectMacAddress(auth, mac), local, dns);
        // give the Ethernet shield a second to initialize:
        BlynkDelay(1000);
        IPAddress myip = Ethernet.localIP();
        BLYNK_LOG_IP("IP:", myip);

        config(auth, domain, port);
        while(this->connect() != true) {}
    }

    // Static IP with domain, gateway, etc
    void begin( const char* auth,
                const char* domain,
                uint16_t port,
                IPAddress local,
                IPAddress dns,
                IPAddress gateway,
                IPAddress subnet,
                const byte mac[] = NULL)
    {
#if (BLYNK_ETHERNET_DEBUG > 1)
      BLYNK_LOG1(BLYNK_F("UseStatIP"));
#endif

        Ethernet.begin(SelectMacAddress(auth, mac), local, dns, gateway, subnet);
        // give the Ethernet shield a second to initialize:
        BlynkDelay(1000);
        IPAddress myip = Ethernet.localIP();
        BLYNK_LOG_IP("IP:", myip);

        config(auth, domain, port);
        while(this->connect() != true) {}
    }

    // DHCP with server IP
    void begin( const char* auth,
                IPAddress addr,
                uint16_t port    = BLYNK_SERVER_PORT,
                const byte mac[] = NULL)
    {
#if (BLYNK_ETHERNET_DEBUG > 1)
      BLYNK_LOG1(BLYNK_F("UseStatIP"));
#endif

        if (!Ethernet.begin(SelectMacAddress(auth, mac))) {
            BLYNK_FATAL(BLYNK_F("DHCP 0"));
        }
        // give the Ethernet shield a second to initialize:
        BlynkDelay(1000);
        IPAddress myip = Ethernet.localIP();
        BLYNK_LOG_IP("IP:", myip);

        config(auth, addr, port);
        while(this->connect() != true) {}
    }

    // Static IP with server IP
    void begin( const char* auth,
                IPAddress addr,
                uint16_t port,
                IPAddress local,
                const byte mac[] = NULL)
    {
#if (BLYNK_ETHERNET_DEBUG > 1)
      BLYNK_LOG1(BLYNK_F("UseStatIP"));
#endif

        Ethernet.begin(SelectMacAddress(auth, mac), local);
        // give the Ethernet shield a second to initialize:
        BlynkDelay(1000);
        IPAddress myip = Ethernet.localIP();
        BLYNK_LOG_IP("IP:", myip);

        config(auth, addr, port);
        while(this->connect() != true) {}
    }

    // Static IP with server IP, DNS, gateway, etc
    void begin( const char* auth,
                IPAddress addr,
                uint16_t port,
                IPAddress local,
                IPAddress dns,
                IPAddress gateway,
                IPAddress subnet,
                const byte mac[] = NULL)
    {
#if (BLYNK_ETHERNET_DEBUG > 1)
      BLYNK_LOG1(BLYNK_F("UseStatIP"));
#endif

        Ethernet.begin(SelectMacAddress(auth, mac), local, dns, gateway, subnet);
        // give the Ethernet shield a second to initialize:
        BlynkDelay(1000);
        IPAddress myip = Ethernet.localIP();
        BLYNK_LOG_IP("IP:", myip);

        config(auth, addr, port);
        while(this->connect() != true) {}
    }

private:

    byte macAddress[6];

    byte* SelectMacAddress(const char* token, const byte mac[])
    {
      if (mac != NULL) 
      {
        return (byte*)mac;
      }

      macAddress[0] = 0xFE;
      macAddress[1] = 0xAB;
      macAddress[2] = 0xCD;
      macAddress[3] = 0xEF;
      macAddress[4] = 0xBA;
      macAddress[5] = 0xDC;

      int len = strlen(token);
      int mac_index = 1;

      for (int i = 0; i < len; i++)
      {
        macAddress[mac_index] ^= token[i];

        if (++mac_index > 5) {
          mac_index = 1;
        }
      }
      BLYNK_LOG("MAC:%02X-%02X-%02X-%02X-%02X-%02X",
                macAddress[0], macAddress[1],
                macAddress[2], macAddress[3],
                macAddress[4], macAddress[5]);

      return macAddress;
    }

    

};

#endif    //Blynk_STM32BI_Ethernet_h
