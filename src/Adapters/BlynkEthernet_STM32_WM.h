/****************************************************************************************************************************
  BlynkSTM32Ethernet_WM.h
  For STM32 running built-in Ethernet

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

#ifndef BlynkEthernet_STM32_WM_h
#define BlynkEthernet_STM32_WM_h

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

#define USE_STATIC_SERVER         true

#if !defined(BLYNK_WM_DEBUG)
  #define BLYNK_WM_DEBUG      0
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

#include <EthernetWebServer_STM32.h>

//Use EEPROM
//#include <EEPROM.h>

#include <IWatchdog.h>

///////// NEW for DRD /////////////
// These defines must be put before #include <DoubleResetDetector_Generic.h>
// to select where to store DoubleResetDetector_Generic's variable.
// Otherwise, library will use default EEPROM storage
#define  DRD_FLAG_DATA_SIZE     4

#ifndef DOUBLERESETDETECTOR_DEBUG
#define DOUBLERESETDETECTOR_DEBUG     false
#endif

#include <DoubleResetDetector_Generic.h>      //https://github.com/khoih-prog/DoubleResetDetector_Generic

// Number of seconds after reset during which a
// subsequent reset will be considered a double reset.
#define DRD_TIMEOUT 10

// RTC Memory Address for the DoubleResetDetector_Generic to use
#define DRD_ADDRESS 0

DoubleResetDetector_Generic* drd;

///////// NEW for DRD /////////////

//NEW
#define MAX_ID_LEN                5
#define MAX_DISPLAY_NAME_LEN      16

typedef struct
{
  char id             [MAX_ID_LEN + 1];
  char displayName    [MAX_DISPLAY_NAME_LEN + 1];
  char *pdata;
  uint8_t maxlen;
} MenuItem;
//

#if USE_DYNAMIC_PARAMETERS
  #warning Using Dynamic Parameters
  ///NEW
  extern uint16_t NUM_MENU_ITEMS;
  extern MenuItem myMenuItems [];
  bool *menuItemUpdated = NULL;
#else
  #warning Not using Dynamic Parameters
#endif

#define BLYNK_HEADER_MAX_LEN      16

#define BLYNK_SERVER_MAX_LEN      32
#define BLYNK_TOKEN_MAX_LEN       36

#define STATIC_IP_MAX_LEN         16
#define BOARD_NAME_MAX_LEN        24

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
  char header         [BLYNK_HEADER_MAX_LEN];
  Blynk_Credentials Blynk_Creds [NUM_BLYNK_CREDENTIALS];
  int  blynk_port;
  char static_IP      [STATIC_IP_MAX_LEN];
  char board_name     [BOARD_NAME_MAX_LEN];
  int  checkSum;
} Blynk_Configuration;

// Currently CONFIG_DATA_SIZE  =  ( 64 + (68 * NUM_BLYNK_CREDENTIALS) ) = 200
// Currently 200 (chsum)
uint16_t CONFIG_DATA_SIZE = sizeof(Blynk_Configuration);

///New from v1.1.0
extern bool LOAD_DEFAULT_CONFIG_DATA;
extern Blynk_Configuration defaultConfig;

// -- HTML page fragments
const char BLYNK_WM_HTML_HEAD[]     /*PROGMEM*/ = "<!DOCTYPE html><html><head><title>BlynkEthernetSTM32_WM</title><style>div,input{padding:2px;font-size:1em;}input{width:95%;}\
body{text-align: center;}button{background-color:#16A1E7;color:#fff;line-height:2.4rem;font-size:1.2rem;width:100%;}fieldset{border-radius:0.5rem;margin:0px;}\
</style></head><div style=\"text-align:left;display:inline-block;min-width:260px;\">\
<fieldset><div><label>Blynk Server</label><input value=\"[[sv]]\"id=\"sv\"><div></div></div>\
<div><label>Token</label><input value=\"[[tk]]\"id=\"tk\"><div></div></div>\
<div><label>Blynk Server1</label><input value=\"[[sv1]]\"id=\"sv1\"><div></div></div>\
<div><label>Token1</label><input value=\"[[tk1]]\"id=\"tk1\"><div></div></div>\
<div><label>Port</label><input value=\"[[pt]]\"id=\"pt\"><div></div></div>\
<div><label>StaticIP</label><input value=\"[[ip]]\"id=\"ip\"><div></div></div></fieldset>\
<fieldset><div><label>Board Name</label><input value=\"[[nm]]\"id=\"nm\"><div></div></div></fieldset>";

const char BLYNK_WM_FLDSET_START[]  /*PROGMEM*/ = "<fieldset>";
const char BLYNK_WM_FLDSET_END[]    /*PROGMEM*/ = "</fieldset>";
const char BLYNK_WM_HTML_PARAM[]    /*PROGMEM*/ = "<div><label>{b}</label><input value='[[{v}]]'id='{i}'><div></div></div>";
const char BLYNK_WM_HTML_BUTTON[]   /*PROGMEM*/ = "<button onclick=\"sv()\">Save</button></div>";
const char BLYNK_WM_HTML_SCRIPT[]   /*PROGMEM*/ = "<script id=\"jsbin-javascript\">\
function udVal(key,val){var request=new XMLHttpRequest();var url='/?key='+key+'&value='+encodeURIComponent(val);request.open('GET',url,false);request.send(null);}\
function sv(){udVal('sv',document.getElementById('sv').value);udVal('tk',document.getElementById('tk').value);\
udVal('sv1',document.getElementById('sv1').value);udVal('tk1',document.getElementById('tk1').value);\
udVal('pt',document.getElementById('pt').value);udVal('ip',document.getElementById('ip').value);\
udVal('nm',document.getElementById('nm').value);";

const char BLYNK_WM_HTML_SCRIPT_ITEM[]  /*PROGMEM*/ = "udVal('{d}',document.getElementById('{d}').value);";
const char BLYNK_WM_HTML_SCRIPT_END[]   /*PROGMEM*/ = "alert('Updated');}</script>";
const char BLYNK_WM_HTML_END[]          /*PROGMEM*/ = "</html>";
///

#define BLYNK_SERVER_HARDWARE_PORT    8080

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
#if (BLYNK_WM_DEBUG > 1)
      BLYNK_LOG1(BLYNK_F("GetIP:"));
#endif

      if (! (ethernetConnected = Ethernet.begin(SelectMacAddress(auth, mac))) ) {
        BLYNK_FATAL(BLYNK_F("DHCP 0"));
      }

      // give the Ethernet shield a second to initialize:
      BlynkDelay(1000);
      IPAddress myip = Ethernet.localIP();
      BLYNK_LOG_IP("IP:", myip);

      config(auth, domain, port);
      while (this->connect() != true) {}
    }

    // Static IP with domain
    void begin( const char* auth,
                const char* domain,
                uint16_t port,
                IPAddress local,
                IPAddress dns,
                const byte mac[] = NULL)
    {
#if (BLYNK_WM_DEBUG > 1)
      BLYNK_LOG1(BLYNK_F("UseStatIP"));
#endif

      Ethernet.begin(SelectMacAddress(auth, mac), local, dns);
      ethernetConnected = true;
      // give the Ethernet shield a second to initialize:
      BlynkDelay(1000);
      IPAddress myip = Ethernet.localIP();
      BLYNK_LOG_IP("IP:", myip);

      config(auth, domain, port);
      while (this->connect() != true) {}
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
#if (BLYNK_WM_DEBUG > 1)
      BLYNK_LOG1(BLYNK_F("UseStatIP"));
#endif

      Ethernet.begin(SelectMacAddress(auth, mac), local, dns, gateway, subnet);
      ethernetConnected = true;
      // give the Ethernet shield a second to initialize:
      BlynkDelay(1000);
      IPAddress myip = Ethernet.localIP();
      BLYNK_LOG_IP("IP:", myip);

      config(auth, domain, port);
      while (this->connect() != true) {}
    }

    // DHCP with server IP
    void begin( const char* auth,
                IPAddress addr,
                uint16_t port    = BLYNK_SERVER_PORT,
                const byte mac[] = NULL)
    {
#if (BLYNK_WM_DEBUG > 1)
      BLYNK_LOG1(BLYNK_F("GetIP:"));
#endif

      if (! (ethernetConnected = Ethernet.begin(SelectMacAddress(auth, mac))) ) {
        BLYNK_FATAL(BLYNK_F("DHCP 0"));
      }
      // give the Ethernet shield a second to initialize:
      BlynkDelay(1000);
      IPAddress myip = Ethernet.localIP();
      BLYNK_LOG_IP("IP:", myip);

      config(auth, addr, port);
      while (this->connect() != true) {}
    }

    // Static IP with server IP
    void begin( const char* auth,
                IPAddress addr,
                uint16_t port,
                IPAddress local,
                const byte mac[] = NULL)
    {
#if (BLYNK_WM_DEBUG > 1)
      BLYNK_LOG1(BLYNK_F("UseStatIP"));
#endif

      Ethernet.begin(SelectMacAddress(auth, mac), local);
      ethernetConnected = true;
      // give the Ethernet shield a second to initialize:
      BlynkDelay(1000);
      IPAddress myip = Ethernet.localIP();
      BLYNK_LOG_IP("IP:", myip);

      config(auth, addr, port);
      while (this->connect() != true) {}
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
#if (BLYNK_WM_DEBUG > 1)
      BLYNK_LOG1(BLYNK_F("UseStatIP"));
#endif

      Ethernet.begin(SelectMacAddress(auth, mac), local, dns, gateway, subnet);
      ethernetConnected = true;
      // give the Ethernet shield a second to initialize:
      BlynkDelay(1000);
      IPAddress myip = Ethernet.localIP();
      BLYNK_LOG_IP("IP:", myip);

      config(auth, addr, port);
      while (this->connect() != true) {}
    }

#ifndef LED_BUILTIN
  #define LED_BUILTIN       13
#endif

#define LED_OFF     LOW
#define LED_ON      HIGH

    void begin()
    {   
      //Turn OFF
      pinMode(LED_BUILTIN, OUTPUT);
      digitalWrite(LED_BUILTIN, LED_OFF);
      
      //// New DRD ////
      drd = new DoubleResetDetector_Generic(DRD_TIMEOUT, DRD_ADDRESS);  
      bool noConfigPortal = true;
   
      if (drd->detectDoubleReset())
      {
#if ( BLYNK_WM_DEBUG > 1)
        BLYNK_LOG1(BLYNK_F("DRD. Run ConfigPortal"));
#endif        
        noConfigPortal = false;
      }
      //// New DRD ////
      
#if ( BLYNK_WM_DEBUG > 2)    
      if (LOAD_DEFAULT_CONFIG_DATA) 
      {   
        BLYNK_LOG1(BLYNK_F("======= Start Default Config Data ======="));
        displayConfigData(defaultConfig);
      }
#endif

      hadConfigData = getConfigData();

      connectEthernet();

      isForcedConfigPortal = isForcedCP();
      
      //// New DRD/MRD ////
      //  noConfigPortal when getConfigData() OK and no MRD/DRD'ed
      //if (getConfigData() && noConfigPortal)
      if (hadConfigData && noConfigPortal && (!isForcedConfigPortal) )
      {
        hadConfigData = true;
        
#if ( BLYNK_WM_DEBUG > 2)        
        BLYNK_LOG1(noConfigPortal? BLYNK_F("bg: noConfigPortal = true") : BLYNK_F("bg: noConfigPortal = false"));
#endif 

        if (ethernetConnected)
        {
          BLYNK_LOG1(BLYNK_F("bg:ECon.TryB"));

          int i = 0;
          while ( (i++ < 10) && !this->connectMultiBlynk() )
          {
          }

          if  (connected())
          {
            BLYNK_LOG1(BLYNK_F("bg:EBCon"));
          }
          else
          {
            BLYNK_LOG1(BLYNK_F("bg:ECon,BNo"));
            // failed to connect to Blynk server, will start configuration mode
            startConfigurationMode();
          }
        }
        else
        {
          // Can't do anything here
          BLYNK_LOG1(BLYNK_F("bg:E&BNoCon"));
          // failed to connect to Blynk server, will start configuration mode
          //startConfigurationMode();
        }
      }
      else
      { 
#if ( BLYNK_WM_DEBUG > 2)        
        BLYNK_LOG1(isForcedConfigPortal? BLYNK_F("bg: isForcedConfigPortal = true") : BLYNK_F("bg: isForcedConfigPortal = false"));
#endif
                                
        // If not persistent => clear the flag so that after reset. no more CP, even CP not entered and saved
        if (persForcedConfigPortal)
        {
          BLYNK_LOG2(BLYNK_F("bg:Stay forever in CP:"), isForcedConfigPortal ? BLYNK_F("Forced-Persistent") : (noConfigPortal ? BLYNK_F("No ConfigDat") : BLYNK_F("DRD/MRD")));
        }
        else
        {
          BLYNK_LOG2(BLYNK_F("bg:Stay forever in CP:"), isForcedConfigPortal ? BLYNK_F("Forced-non-Persistent") : (noConfigPortal ? BLYNK_F("No ConfigDat") : BLYNK_F("DRD/MRD")));
          clearForcedCP();
        }
          
        hadConfigData = isForcedConfigPortal ? true : (noConfigPortal ? false : true);
        
        // failed to connect to Blynk server, will start configuration mode
        startConfigurationMode();
      }
    }

    void run()
    {
#if RESET_IF_CONFIG_TIMEOUT    
      static int retryTimes = 0;
#endif
      
      //// New DRD ////
      // Call the double reset detector loop method every so often,
      // so that it can recognise when the timeout expires.
      // You can also call drd.stop() when you wish to no longer
      // consider the next reset as a double reset.
      drd->loop();
      //// New DRD ////

      // Be sure to reconnect Ethernet first
      if (!ethernetConnected)
      {
        connectEthernet();
      }

      // Lost connection in running. Give chance to reconfig.
      if ( !connected() )
      {
        // If configTimeout but user hasn't connected to configWeb => try to reconnect Blynk.
        // But if user has connected to configWeb, stay there until done, then reset hardware
        if ( configuration_mode && ( configTimeout == 0 ||  millis() < configTimeout ) )
        {
#if RESET_IF_CONFIG_TIMEOUT        
          retryTimes = 0;
#endif

#if !USE_STATIC_SERVER
          if (server)
          {
            server->handleClient();
          }
#else
          server.handleClient();
#endif

          return;
        }
        else
        {
#if RESET_IF_CONFIG_TIMEOUT
          // If we're here but still in configuration_mode, permit running TIMES_BEFORE_RESET times before reset hardware
          // to permit user another chance to config.
          if ( configuration_mode && (configTimeout != 0) )
          {
            if (++retryTimes <= CONFIG_TIMEOUT_RETRYTIMES_BEFORE_RESET)
            {
              BLYNK_LOG2(BLYNK_F("r:BLost,TOut.TryB.#:"), retryTimes);
            }
            else
            {
              resetFunc();
            }
          }
#endif

          // Not in config mode, try reconnecting before forcing to config mode
          BLYNK_LOG1(BLYNK_F("r:BLost.TryB"));

          //if (connectMultiBlynk())
          if (this->connectMultiBlynk())         
          {
            // turn the LED_BUILTIN OFF to tell us we exit configuration mode.
            digitalWrite(LED_BUILTIN, HIGH);
            BLYNK_LOG1(BLYNK_F("r:BRecon"));
          }
        }
      }
      else if (configuration_mode)
      {
        configuration_mode = false;
        BLYNK_LOG1(BLYNK_F("r:E&B OK"));
        
        // Turn the LED_BUILTIN OFF when out of configuration mode. 
        digitalWrite(LED_BUILTIN, LED_OFF);
      }

      if (connected())
      {
        Base::run();
      }
    }

    String getBoardName()
    {
      return (String(BlynkEthernet_WM_config.board_name));
    }

    String getServerName(uint8_t index = 255)
    {
      if (index == 255)
      {
        // Current connected Blynk Server
        index = currentBlynkServerIndex;
      }
        
      if (index >= NUM_BLYNK_CREDENTIALS)
        return String("");

      if (!hadConfigData)
        getConfigData();

      return (String(BlynkEthernet_WM_config.Blynk_Creds[index].blynk_server));
    }

    String getToken(uint8_t index = 255)
    {
      if (index == 255)
      {
        // Current connected Blynk Server
        index = currentBlynkServerIndex;
      }
          
      if (index >= NUM_BLYNK_CREDENTIALS)
        return String("");

      if (!hadConfigData)
        getConfigData();

      return (String(BlynkEthernet_WM_config.Blynk_Creds[index].blynk_token));
    }

    int getHWPort()
    {
      return (BlynkEthernet_WM_config.blynk_port);
    }
    
    Blynk_Configuration* getFullConfigData(Blynk_Configuration *configData)
    {
      if (!hadConfigData)
        getConfigData();

      // Check if NULL pointer
      if (configData)
        memcpy(configData, &BlynkEthernet_WM_config, sizeof(BlynkEthernet_WM_config));

      return (configData);
    }

    void clearConfigData()
    {
      memset(&BlynkEthernet_WM_config, 0, sizeof(BlynkEthernet_WM_config));

#if USE_DYNAMIC_PARAMETERS      
      for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
      {
        // Actual size of pdata is [maxlen + 1]
        memset(myMenuItems[i].pdata, 0, myMenuItems[i].maxlen + 1);
      }
#endif
      
      saveConfigData();
    }
    
    // Forced CP => Flag = 0xBEEFBEEF. Else => No forced CP
    // Flag to be stored at (EEPROM_START + DRD_FLAG_DATA_SIZE + CONFIG_DATA_SIZE) 
    // to avoid corruption to current data
    //#define FORCED_CONFIG_PORTAL_FLAG_DATA              ( (uint32_t) 0xDEADBEEF)
    //#define FORCED_PERS_CONFIG_PORTAL_FLAG_DATA         ( (uint32_t) 0xBEEFDEAD)
    
    const uint32_t FORCED_CONFIG_PORTAL_FLAG_DATA       = 0xDEADBEEF;
    const uint32_t FORCED_PERS_CONFIG_PORTAL_FLAG_DATA  = 0xBEEFDEAD;
    
    #define FORCED_CONFIG_PORTAL_FLAG_DATA_SIZE     4
    
    void resetAndEnterConfigPortal()
    {
      persForcedConfigPortal = false;
      
      setForcedCP(false);
      
      // Delay then reset the ESP8266 after save data
      delay(1000);
      resetFunc();
    }
    
    // This will keep CP forever, until you successfully enter CP, and Save data to clear the flag.
    void resetAndEnterConfigPortalPersistent()
    {
      persForcedConfigPortal = true;
      
      setForcedCP(true);
      
      // Delay then reset the ESP8266 after save data
      delay(1000);
      resetFunc();
    }

    void resetFunc()
    {    
      // Initialize the IWDG with 2 seconds timeout.
      // This would cause a CPU reset if the IWDG timer
      // is not reloaded in approximately 2 seconds.
      IWatchdog.begin(2000000);
    }
       
  private:

    // Initialize the Ethernet server library
    // with the IP address and port you want to use
    // (port 80 is default for HTTP):
#if USE_STATIC_SERVER
    EthernetWebServer server;
#else
    EthernetWebServer *server;
#endif

    bool ethernetConnected = false;

    bool configuration_mode = false;

    unsigned long configTimeout;
    bool hadConfigData = false;
    
    bool isForcedConfigPortal   = false;
    bool persForcedConfigPortal = false;

    Blynk_Configuration BlynkEthernet_WM_config;
    
    uint16_t totalDataSize = 0;
    
    uint8_t currentBlynkServerIndex = 255;    

#define RFC952_HOSTNAME_MAXLEN      24
    char RFC952_hostname[RFC952_HOSTNAME_MAXLEN + 1];

    void setRFC952_hostname(const char* iHostname = "")
    {
      if (iHostname[0] == 0)
      {
        String _hostname = "W5X00-XXXXXX";    // + String(macAddress, HEX);
        _hostname.toUpperCase();

        getRFC952_hostname(_hostname.c_str());

      }
      else
      {
        // Prepare and store the hostname only not NULL
        getRFC952_hostname(iHostname);
      }

#if (BLYNK_WM_DEBUG > 0)
      BLYNK_LOG2(BLYNK_F("Hname="), RFC952_hostname);
#endif
    }

    char* getRFC952_hostname(const char* iHostname)
    {
      memset(RFC952_hostname, 0, sizeof(RFC952_hostname));

      size_t len = ( RFC952_HOSTNAME_MAXLEN < strlen(iHostname) ) ? RFC952_HOSTNAME_MAXLEN : strlen(iHostname);

      size_t j = 0;

      for (size_t i = 0; i < len - 1; i++)
      {
        if ( isalnum(iHostname[i]) || iHostname[i] == '-' )
        {
          RFC952_hostname[j] = iHostname[i];
          j++;
        }
      }
      // no '-' as last char
      if ( isalnum(iHostname[len - 1]) || (iHostname[len - 1] != '-') )
        RFC952_hostname[j] = iHostname[len - 1];

      return RFC952_hostname;
    }

    void displayConfigData(Blynk_Configuration configData)
    {
      BLYNK_LOG4(BLYNK_F("Hdr="),       configData.header,
                 BLYNK_F(",BName="),    configData.board_name);
      BLYNK_LOG4(BLYNK_F("Svr="),       configData.Blynk_Creds[0].blynk_server,
                 BLYNK_F(",Tok="),      configData.Blynk_Creds[0].blynk_token);
      BLYNK_LOG4(BLYNK_F("Svr1="),      configData.Blynk_Creds[1].blynk_server,
                 BLYNK_F(",Tok1="),     configData.Blynk_Creds[1].blynk_token);
      BLYNK_LOG4(BLYNK_F("Prt="),       configData.blynk_port,
                 BLYNK_F(",SIP="),      configData.static_IP);
                 
#if (USE_DYNAMIC_PARAMETERS && ( BLYNK_WM_DEBUG > 2))  
      for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
      {
        BLYNK_LOG6("i=", i, ",id=", myMenuItems[i].id, ",data=", myMenuItems[i].pdata);
      }      
#endif                 
    }

#define BLYNK_BOARD_TYPE      BLYNK_INFO_CONNECTION

#define WM_NO_CONFIG          "blank"

#ifndef EEPROM_SIZE
  #define EEPROM_SIZE     4096
#else
  #if (EEPROM_SIZE > 4096)
    #warning EEPROM_SIZE must be <= 4096. Reset to 4096
    #undef EEPROM_SIZE
    #define EEPROM_SIZE     4096
  #endif
  #if (EEPROM_SIZE < CONFIG_DATA_SIZE)
    #warning EEPROM_SIZE must be > CONFIG_DATA_SIZE. Reset to 512
    #undef EEPROM_SIZE
    #define EEPROM_SIZE     512
  #endif
#endif

#ifndef EEPROM_START
  #define EEPROM_START     0      //define 256 in DRD
  #warning EEPROM_START not defined. Set to 0
#else
  #if ( (EEPROM_START + DRD_FLAG_DATA_SIZE + CONFIG_DATA_SIZE + FORCED_CONFIG_PORTAL_FLAG_DATA_SIZE) > (EEPROM_SIZE) )
    #error EPROM_START + DRD_FLAG_DATA_SIZE + CONFIG_DATA_SIZE + FORCED_CONFIG_PORTAL_FLAG_DATA_SIZE > EEPROM_SIZE. Please adjust.
  #endif
#endif

// Stating positon to store Blynk8266_WM_config
#define BLYNK_EEPROM_START    (EEPROM_START + DRD_FLAG_DATA_SIZE)

    //////////////////////////////////////////////

    int calcChecksum()
    {
      int checkSum = 0;
      for (uint16_t index = 0; index < (sizeof(BlynkEthernet_WM_config) - sizeof(BlynkEthernet_WM_config.checkSum)); index++)
      {
        checkSum += * ( ( (byte*) &BlynkEthernet_WM_config ) + index);
      }

      return checkSum;
    }
    
    //////////////////////////////////////////////
    
    void NULLTerminateConfig()
    {
      //#define HEADER_MAX_LEN      16
      //#define BLYNK_SERVER_MAX_LEN      32
      //#define BLYNK_TOKEN_MAX_LEN       36
      //#define STATIC_IP_MAX_LEN         16
      //#define BOARD_NAME_MAX_LEN        24
      
      // NULL Terminating to be sure
      BlynkEthernet_WM_config.header[BLYNK_HEADER_MAX_LEN - 1] = 0;
      BlynkEthernet_WM_config.Blynk_Creds[0].blynk_server[BLYNK_SERVER_MAX_LEN - 1] = 0;
      BlynkEthernet_WM_config.Blynk_Creds[0].blynk_token [BLYNK_TOKEN_MAX_LEN - 1]  = 0;
      BlynkEthernet_WM_config.Blynk_Creds[1].blynk_server[BLYNK_SERVER_MAX_LEN - 1] = 0;
      BlynkEthernet_WM_config.Blynk_Creds[1].blynk_token [BLYNK_TOKEN_MAX_LEN - 1]  = 0;
      BlynkEthernet_WM_config.blynk_port = BLYNK_SERVER_HARDWARE_PORT;
      BlynkEthernet_WM_config.static_IP[STATIC_IP_MAX_LEN - 1] = 0;
      BlynkEthernet_WM_config.board_name [BOARD_NAME_MAX_LEN - 1]  = 0;
    }
       
//////////////////////////////////////////////
    
#if defined(DATA_EEPROM_BASE)
    // For STM32 devices having integrated EEPROM.
    #include <EEPROM.h>
    #warning STM32 devices have integrated EEPROM. Not using buffered API.   
#else  
    /**
     Most STM32 devices don't have an integrated EEPROM. To emulate a EEPROM, the STM32 Arduino core emulated
     the operation of an EEPROM with the help of the embedded flash.
     Writing to a flash is very expensive operation, since a whole flash page needs to be written, even if you only
     want to access the flash byte-wise.
     The STM32 Arduino core provides a buffered access API to the emulated EEPROM. The library has allocated the
     buffer even if you don't use the buffered API, so it's strongly suggested to use the buffered API anyhow.
     */
    #include <FlashStorage_STM32.h>       // https://github.com/khoih-prog/FlashStorage_STM32
    #warning STM32 devices have no integrated EEPROM. Using buffered API with FlashStorage_STM32 library
#endif    // #if defined(DATA_EEPROM_BASE)
//////////////////////////////////////////////
          
    void setForcedCP(bool isPersistent)
    {
      uint32_t readForcedConfigPortalFlag = isPersistent? FORCED_PERS_CONFIG_PORTAL_FLAG_DATA : FORCED_CONFIG_PORTAL_FLAG_DATA;

#if ( BLYNK_WM_DEBUG > 2)      
      BLYNK_LOG1(isPersistent ? BLYNK_F("setForcedCP Persistent") : BLYNK_F("setForcedCP non-Persistent"));
#endif
           
      EEPROM.put(BLYNK_EEPROM_START + CONFIG_DATA_SIZE, readForcedConfigPortalFlag);
    }
    
    //////////////////////////////////////////////
    
    void clearForcedCP()
    {
      EEPROM.put(BLYNK_EEPROM_START + CONFIG_DATA_SIZE, 0);
    }
    
    //////////////////////////////////////////////

    bool isForcedCP()
    {
      uint32_t readForcedConfigPortalFlag;
      
      // Return true if forced CP (0xDEADBEEF read at offset EPROM_START + DRD_FLAG_DATA_SIZE + CONFIG_DATA_SIZE)
      // => set flag noForcedConfigPortal = false
      EEPROM.get(BLYNK_EEPROM_START + CONFIG_DATA_SIZE, readForcedConfigPortalFlag);
      
      // Return true if forced CP (0xDEADBEEF read at offset EPROM_START + DRD_FLAG_DATA_SIZE + CONFIG_DATA_SIZE)
      // => set flag noForcedConfigPortal = false     
      if (readForcedConfigPortalFlag == FORCED_CONFIG_PORTAL_FLAG_DATA)
      {       
        persForcedConfigPortal = false;
        return true;
      }
      else if (readForcedConfigPortalFlag == FORCED_PERS_CONFIG_PORTAL_FLAG_DATA)
      {       
        persForcedConfigPortal = true;
        return true;
      }
      else
      {       
        return false;
      }
    }
    
    //////////////////////////////////////////////

#if USE_DYNAMIC_PARAMETERS

    bool checkDynamicData()
    {
      int checkSum = 0;
      int readCheckSum;
      
      #define BUFFER_LEN      128
      char readBuffer[BUFFER_LEN + 1];
      
      uint16_t offset = BLYNK_EEPROM_START + sizeof(BlynkEthernet_WM_config) + FORCED_CONFIG_PORTAL_FLAG_DATA_SIZE;
                
      // Find the longest pdata, then dynamically allocate buffer. Remember to free when done
      // This is used to store tempo data to calculate checksum to see of data is valid
      // We dont like to destroy myMenuItems[i].pdata with invalid data
      
      for (int i = 0; i < NUM_MENU_ITEMS; i++)
      {       
        if (myMenuItems[i].maxlen > BUFFER_LEN)
        {
          // Size too large, abort and flag false
          BLYNK_LOG1(BLYNK_F("ChkCrR: Error Small Buffer."));
          return false;
        }
      }
         
      for (int i = 0; i < NUM_MENU_ITEMS; i++)
      {       
        char* _pointer = readBuffer;
        
        // Prepare buffer, more than enough
        memset(readBuffer, 0, sizeof(readBuffer));
        
        // Read more than necessary, but OK and easier to code
        EEPROM.get(offset, readBuffer);
        // NULL terminated
        readBuffer[myMenuItems[i].maxlen] = 0;

#if ( BLYNK_WM_DEBUG > 2) 
        BLYNK_LOG4(BLYNK_F("ChkCrR:pdata="), readBuffer, BLYNK_F(",len="), myMenuItems[i].maxlen);     
#endif
               
        for (uint16_t j = 0; j < myMenuItems[i].maxlen; j++,_pointer++)
        {         
          checkSum += *_pointer;  
        }   
        
        offset += myMenuItems[i].maxlen;    
      }

      EEPROM.get(offset, readCheckSum);
           
      BLYNK_LOG4(BLYNK_F("ChkCrR:CrCCsum=0x"), String(checkSum, HEX), BLYNK_F(",CrRCsum=0x"), String(readCheckSum, HEX));
           
      if ( checkSum != readCheckSum)
      {
        return false;
      }
      
      return true;    
    }
    
    //////////////////////////////////////////////
    
    bool EEPROM_getDynamicData()
    {
      int readCheckSum;
      int checkSum = 0;
      uint16_t offset = BLYNK_EEPROM_START + sizeof(BlynkEthernet_WM_config) + FORCED_CONFIG_PORTAL_FLAG_DATA_SIZE;
           
      totalDataSize = sizeof(BlynkEthernet_WM_config) + sizeof(readCheckSum);
      
      for (int i = 0; i < NUM_MENU_ITEMS; i++)
      {       
        char* _pointer = myMenuItems[i].pdata;
        totalDataSize += myMenuItems[i].maxlen;
        
        // Actual size of pdata is [maxlen + 1]
        memset(myMenuItems[i].pdata, 0, myMenuItems[i].maxlen + 1);
               
        for (uint16_t j = 0; j < myMenuItems[i].maxlen; j++,_pointer++,offset++)
        {
          *_pointer = EEPROM.read(offset);
          
          checkSum += *_pointer;  
         }       
      }
      
      EEPROM.get(offset, readCheckSum);
      
      BLYNK_LOG4(BLYNK_F("CrCCsum=0x"), String(checkSum, HEX), BLYNK_F(",CrRCsum=0x"), String(readCheckSum, HEX));
      
      if ( checkSum != readCheckSum)
      {
        return false;
      }
      
      return true;
    }
    
    //////////////////////////////////////////////

    void EEPROM_putDynamicData()
    {
      int checkSum = 0;
      uint16_t offset = BLYNK_EEPROM_START + sizeof(BlynkEthernet_WM_config) + FORCED_CONFIG_PORTAL_FLAG_DATA_SIZE;
                
      for (int i = 0; i < NUM_MENU_ITEMS; i++)
      {       
        char* _pointer = myMenuItems[i].pdata;
 
#if ( BLYNK_WM_DEBUG > 2)         
        BLYNK_LOG4(BLYNK_F("pdata="), myMenuItems[i].pdata, BLYNK_F(",len="), myMenuItems[i].maxlen);
#endif                            
        for (uint16_t j = 0; j < myMenuItems[i].maxlen; j++,_pointer++,offset++)
        {
          EEPROM.write(offset, *_pointer);
          
          checkSum += *_pointer;     
         }
      }
      
      EEPROM.put(offset, checkSum);
      
      BLYNK_LOG2(BLYNK_F("CrCCSum=0x"), String(checkSum, HEX));
    }
#endif    // #if USE_DYNAMIC_PARAMETERS

    

    //////////////////////////////////////////////
    
    bool EEPROM_get()
    {
      EEPROM.get(BLYNK_EEPROM_START, BlynkEthernet_WM_config);
      NULLTerminateConfig();
      
      return true;
    }
    
    //////////////////////////////////////////////
    
    void EEPROM_put()
    {
      EEPROM.put(BLYNK_EEPROM_START, BlynkEthernet_WM_config);
    }
    
    //////////////////////////////////////////////
    
    void saveConfigData()
    {
      int calChecksum = calcChecksum();
      BlynkEthernet_WM_config.checkSum = calChecksum;
      
      BLYNK_LOG6(BLYNK_F("SaveEEPROM,Sz="), EEPROM.length(), BLYNK_F(",DataSz="), totalDataSize, BLYNK_F(",WCSum=0x"), String(calChecksum, HEX));
      
      EEPROM_put();
        
#if USE_DYNAMIC_PARAMETERS        
      EEPROM_putDynamicData();
#endif        
    }

    //////////////////////////////////////////////
    
    void loadAndSaveDefaultConfigData()
    {
      // Load Default Config Data from Sketch
      memcpy(&BlynkEthernet_WM_config, &defaultConfig, sizeof(BlynkEthernet_WM_config));
      strcpy(BlynkEthernet_WM_config.header, BLYNK_BOARD_TYPE);
      
      // Including config and dynamic data, and assume valid
      saveConfigData();
      
#if ( BLYNK_WM_DEBUG > 2)      
      BLYNK_LOG1(BLYNK_F("======= Start Loaded Config Data ======="));
      displayConfigData(BlynkEthernet_WM_config);
#endif      
    }
    
    //////////////////////////////////////////////
    
    bool getConfigData()
    {      
      bool dynamicDataValid = true;
      int calChecksum; 
      
      hadConfigData = false; 
      
      // Use new LOAD_DEFAULT_CONFIG_DATA logic
      if (LOAD_DEFAULT_CONFIG_DATA)
      {     
        // Load Config Data from Sketch
        loadAndSaveDefaultConfigData();
        
        // Don't need Config Portal anymore
        return true; 
      }
      else
      {   
        // Load stored config from EEPROM-simulated FlashStorage
        EEPROM_get();
                
        // Verify ChkSum
        calChecksum = calcChecksum();

        BLYNK_LOG4(BLYNK_F("CCSum=0x"), String(calChecksum, HEX),
                   BLYNK_F(",RCSum=0x"), String(BlynkEthernet_WM_config.checkSum, HEX));

#if USE_DYNAMIC_PARAMETERS        
        // Load stored dynamic data from dueFlashStorage
        dynamicDataValid = checkDynamicData();
#endif
        // If checksum = 0 => DueFlashStorage has been cleared (by uploading new FW, etc) => force to CP
        // If bad checksum = 0 => force to CP
        if ( (calChecksum != 0) && (calChecksum == BlynkEthernet_WM_config.checkSum) )
        {                   
          if (dynamicDataValid)
          {
  #if USE_DYNAMIC_PARAMETERS
            // CkSum verified, Now get valid dynamic data
            EEPROM_getDynamicData();
            
    #if ( BLYNK_WM_DEBUG > 2 )
            BLYNK_LOG1(BLYNK_F("Valid Stored Dynamic Data"));
    #endif
  #endif  
                 
            BLYNK_LOG1(BLYNK_F("======= Start Stored Config Data ======="));
            displayConfigData(BlynkEthernet_WM_config);
            
            // Don't need Config Portal anymore
            return true;
          }
          else
          {
            // Invalid Stored config data => Config Portal
            BLYNK_LOG1(BLYNK_F("Invalid Stored Dynamic Data. Load default from Sketch"));
            
            // Load Default Config Data from Sketch, better than just "blank"
            loadAndSaveDefaultConfigData();
                             
            // Need Config Portal here as data can be just dummy
            // Even if you don't open CP, you're OK on next boot if your default config data is valid 
            return false;
          }
        }   
      } 

      if ( (strncmp(BlynkEthernet_WM_config.header, BLYNK_BOARD_TYPE, strlen(BLYNK_BOARD_TYPE)) != 0) ||
           (calChecksum != BlynkEthernet_WM_config.checkSum) || !dynamicDataValid || 
           ( (calChecksum == 0) && (BlynkEthernet_WM_config.checkSum == 0) ) )
      {
        // Including Credentials CSum
        BLYNK_LOG2(F("InitCfgFile,Sz="), sizeof(BlynkEthernet_WM_config));

        // doesn't have any configuration        
        if (LOAD_DEFAULT_CONFIG_DATA)
        {
          memcpy(&BlynkEthernet_WM_config, &defaultConfig, sizeof(BlynkEthernet_WM_config));
        }
        else
        {  
          memset(&BlynkEthernet_WM_config, 0, sizeof(BlynkEthernet_WM_config));

#if USE_DYNAMIC_PARAMETERS
          for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
          {
            // Actual size of pdata is [maxlen + 1]
            memset(myMenuItems[i].pdata, 0, myMenuItems[i].maxlen + 1);
          }
#endif
          
          // Including Credentials CSum
          BLYNK_LOG2(BLYNK_F("InitCfgFile,DataSz="), totalDataSize);

          // doesn't have any configuration
          strcpy(BlynkEthernet_WM_config.Blynk_Creds[0].blynk_server,   WM_NO_CONFIG);
          strcpy(BlynkEthernet_WM_config.Blynk_Creds[0].blynk_token,    WM_NO_CONFIG);
          strcpy(BlynkEthernet_WM_config.Blynk_Creds[1].blynk_server,   WM_NO_CONFIG);
          strcpy(BlynkEthernet_WM_config.Blynk_Creds[1].blynk_token,    WM_NO_CONFIG);
          BlynkEthernet_WM_config.blynk_port = BLYNK_SERVER_HARDWARE_PORT;
          strcpy(BlynkEthernet_WM_config.static_IP,   WM_NO_CONFIG);
          strcpy(BlynkEthernet_WM_config.board_name,  WM_NO_CONFIG);

#if USE_DYNAMIC_PARAMETERS          
          for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
          {
            strncpy(myMenuItems[i].pdata, WM_NO_CONFIG, myMenuItems[i].maxlen);
          }
#endif          
        }
    
        strcpy(BlynkEthernet_WM_config.header, BLYNK_BOARD_TYPE);
        
#if ( BLYNK_WM_DEBUG > 2) && USE_DYNAMIC_PARAMETERS
        for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
        {
          BLYNK_LOG4(BLYNK_F("g:myMenuItems["), i, BLYNK_F("]="), myMenuItems[i].pdata );
        }
#endif
                
        // Don't need
        BlynkEthernet_WM_config.checkSum = 0;

        saveConfigData();

        return false;
      }
      else if ( !strncmp(BlynkEthernet_WM_config.Blynk_Creds[0].blynk_server, WM_NO_CONFIG, strlen(WM_NO_CONFIG) )  ||
                !strncmp(BlynkEthernet_WM_config.Blynk_Creds[0].blynk_token,  WM_NO_CONFIG, strlen(WM_NO_CONFIG) )  ||
                !strncmp(BlynkEthernet_WM_config.Blynk_Creds[1].blynk_server, WM_NO_CONFIG, strlen(WM_NO_CONFIG) )  ||
                !strncmp(BlynkEthernet_WM_config.Blynk_Creds[1].blynk_token,  WM_NO_CONFIG, strlen(WM_NO_CONFIG) ) )
      {
        // If SSID, PW, Server,Token ="nothing", stay in config mode forever until having config Data.
        return false;
      }
      else
      {
        displayConfigData(BlynkEthernet_WM_config);
      }

      return true;
    }
    
    //////////////////////////////////////////////

    bool connectMultiBlynk()
    {
#define BLYNK_CONNECT_TIMEOUT_MS      5000L

      for (int i = 0; i < NUM_BLYNK_CREDENTIALS; i++)
      {
        BLYNK_LOG4(BLYNK_F("Try connecting to BlynkServer="), BlynkEthernet_WM_config.Blynk_Creds[i].blynk_server,
                     BLYNK_F(",Token="), BlynkEthernet_WM_config.Blynk_Creds[i].blynk_token);
                     
        config(BlynkEthernet_WM_config.Blynk_Creds[i].blynk_token,
               BlynkEthernet_WM_config.Blynk_Creds[i].blynk_server, BlynkEthernet_WM_config.blynk_port);

        if (connect(BLYNK_CONNECT_TIMEOUT_MS) )
        {
          BLYNK_LOG4(BLYNK_F("Connected to BlynkServer="), BlynkEthernet_WM_config.Blynk_Creds[i].blynk_server,
                     BLYNK_F(",Token="), BlynkEthernet_WM_config.Blynk_Creds[i].blynk_token);
                     
          currentBlynkServerIndex = i;           
          return true;
        }
      }

      BLYNK_LOG1(BLYNK_F("Blynk not connected"));

      return false;
    }
     

    //////////////////////////////////////////////
    
    void createHTML(String& root_html_template)
    {
      String pitem;
      
      root_html_template = String(BLYNK_WM_HTML_HEAD);

#if USE_DYNAMIC_PARAMETERS     
      if (NUM_MENU_ITEMS > 0)
      {
        root_html_template += String(BLYNK_WM_FLDSET_START);
           
        for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
        {
          pitem = String(BLYNK_WM_HTML_PARAM);

          pitem.replace("{b}", myMenuItems[i].displayName);
          pitem.replace("{v}", myMenuItems[i].id);
          pitem.replace("{i}", myMenuItems[i].id);
          
          root_html_template += pitem;      
        }
            
        root_html_template += String(BLYNK_WM_FLDSET_END);
      }
#endif
      
      root_html_template += String(BLYNK_WM_HTML_BUTTON) + String(BLYNK_WM_HTML_SCRIPT);   

#if USE_DYNAMIC_PARAMETERS          
      if (NUM_MENU_ITEMS > 0)
      {        
        for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
        {
          pitem = String(BLYNK_WM_HTML_SCRIPT_ITEM);
          
          pitem.replace("{d}", myMenuItems[i].id);
          
          root_html_template += pitem;        
        }
      }
#endif
      
      root_html_template += String(BLYNK_WM_HTML_SCRIPT_END) + String(BLYNK_WM_HTML_END);
      
      return;      
    }
    
    //////////////////////////////////////////////

    void handleRequest()
    {
#if !USE_STATIC_SERVER
      if (server)
#endif
      {
#if USE_STATIC_SERVER
        String key = server.arg("key");
        String value = server.arg("value");
#else
        String key = server->arg("key");
        String value = server->arg("value");
#endif

        static int number_items_Updated = 0;

        if (key == "" && value == "")
        {
          String result;
          createHTML(result);

#if (BLYNK_WM_DEBUG > 2)
          BLYNK_LOG2(BLYNK_F("h:Repl:"), result);
#endif

          // Reset configTimeout to stay here until finished.
          configTimeout = 0;
          
          if ( RFC952_hostname[0] != 0 )
          {
            // Replace only if Hostname is valid
            result.replace("BlynkEthernet_SAMD_WM", RFC952_hostname);
          }
          else if ( BlynkEthernet_WM_config.board_name[0] != 0 )
          {
            // Or replace only if board_name is valid.  Otherwise, keep intact
            result.replace("BlynkEthernet_SAMD_WM", BlynkEthernet_WM_config.board_name);
          }

          result.replace("[[sv]]",     BlynkEthernet_WM_config.Blynk_Creds[0].blynk_server);
          result.replace("[[tk]]",     BlynkEthernet_WM_config.Blynk_Creds[0].blynk_token);
          result.replace("[[sv1]]",    BlynkEthernet_WM_config.Blynk_Creds[1].blynk_server);
          result.replace("[[tk1]]",    BlynkEthernet_WM_config.Blynk_Creds[1].blynk_token);
          result.replace("[[pt]]",     String(BlynkEthernet_WM_config.blynk_port));
          result.replace("[[ip]]",     BlynkEthernet_WM_config.static_IP);
          result.replace("[[nm]]",     BlynkEthernet_WM_config.board_name);

#if USE_DYNAMIC_PARAMETERS
          for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
          {
            String toChange = String("[[") + myMenuItems[i].id + "]]";
            result.replace(toChange, myMenuItems[i].pdata);

#if ( BLYNK_WM_DEBUG > 2)                 
            BLYNK_LOG4(BLYNK_F("h1:myMenuItems["), i, BLYNK_F("]="), myMenuItems[i].pdata );
#endif            
          }
#endif

#if USE_STATIC_SERVER
          server.send(200, "text/html", result);
#else
          server->send(200, "text/html", result);
#endif

          return;
        }

        if (number_items_Updated == 0)
        {
          memset(&BlynkEthernet_WM_config, 0, sizeof(BlynkEthernet_WM_config));
          strcpy(BlynkEthernet_WM_config.header, BLYNK_BOARD_TYPE);
        }

#if USE_DYNAMIC_PARAMETERS
        if (!menuItemUpdated)
        {
          // Don't need to free
          menuItemUpdated = new bool[NUM_MENU_ITEMS];
          
          if (menuItemUpdated)
          {
            for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
            {           
              // To flag item is not yet updated
              menuItemUpdated[i] = false;           
            }
  #if ( BLYNK_WM_DEBUG > 2)                 
            BLYNK_LOG1(BLYNK_F("h: Init menuItemUpdated" ));
  #endif                        
          }
          else
          {
            BLYNK_LOG1(BLYNK_F("h: Error can't alloc memory for menuItemUpdated" ));
          }
        }  
#endif

        static bool sv_Updated  = false;
        static bool tk_Updated  = false;
        static bool sv1_Updated = false;
        static bool tk1_Updated = false;     
        static bool pt_Updated  = false;
        static bool ip_Updated  = false;
        static bool nm_Updated  = false;
   
        //if (key == "sv")
        if (!sv_Updated && (key == String("sv")))
        {
#if (BLYNK_WM_DEBUG > 2)
          BLYNK_LOG1(BLYNK_F("h:sv"));
#endif
          sv_Updated = true;
          number_items_Updated++;
          
          if (strlen(value.c_str()) < sizeof(BlynkEthernet_WM_config.Blynk_Creds[0].blynk_server) - 1)
            strcpy(BlynkEthernet_WM_config.Blynk_Creds[0].blynk_server, value.c_str());
          else
            strncpy(BlynkEthernet_WM_config.Blynk_Creds[0].blynk_server, value.c_str(), sizeof(BlynkEthernet_WM_config.Blynk_Creds[0].blynk_server) - 1);
        }
        else if (!tk_Updated && (key == String("tk")))
        {
#if ( BLYNK_WM_DEBUG > 2)        
          BLYNK_LOG1(BLYNK_F("h:tk"));
#endif
          tk_Updated = true;         
          number_items_Updated++;
          
          if (strlen(value.c_str()) < sizeof(BlynkEthernet_WM_config.Blynk_Creds[0].blynk_token) - 1)
            strcpy(BlynkEthernet_WM_config.Blynk_Creds[0].blynk_token, value.c_str());
          else
            strncpy(BlynkEthernet_WM_config.Blynk_Creds[0].blynk_token, value.c_str(), sizeof(BlynkEthernet_WM_config.Blynk_Creds[0].blynk_token) - 1);
        }    
        else if (!sv1_Updated && (key == String("sv1")))
        {
#if (BLYNK_WM_DEBUG > 2)
          BLYNK_LOG1(BLYNK_F("h:sv1"));
#endif
          sv1_Updated = true;
          number_items_Updated++;
          
          if (strlen(value.c_str()) < sizeof(BlynkEthernet_WM_config.Blynk_Creds[1].blynk_server) - 1)
            strcpy(BlynkEthernet_WM_config.Blynk_Creds[1].blynk_server, value.c_str());
          else
            strncpy(BlynkEthernet_WM_config.Blynk_Creds[1].blynk_server, value.c_str(), sizeof(BlynkEthernet_WM_config.Blynk_Creds[1].blynk_server) - 1);
        }
        else if (!tk1_Updated && (key == String("tk1")))
        {
#if ( BLYNK_WM_DEBUG > 2)        
          BLYNK_LOG1(BLYNK_F("h:tk1"));
#endif
          tk1_Updated = true;         
          number_items_Updated++;
          
          if (strlen(value.c_str()) < sizeof(BlynkEthernet_WM_config.Blynk_Creds[1].blynk_token) - 1)
            strcpy(BlynkEthernet_WM_config.Blynk_Creds[1].blynk_token, value.c_str());
          else
            strncpy(BlynkEthernet_WM_config.Blynk_Creds[1].blynk_token, value.c_str(), sizeof(BlynkEthernet_WM_config.Blynk_Creds[1].blynk_token) - 1);
        }               
        else if (!pt_Updated && (key == String("pt")))
        {
#if (BLYNK_WM_DEBUG > 2)
          BLYNK_LOG1(BLYNK_F("h:pt"));
#endif
          pt_Updated = true;
          number_items_Updated++;
          BlynkEthernet_WM_config.blynk_port = value.toInt();
        }
        else if (!ip_Updated && (key == String("ip")))
        {
#if ( BLYNK_WM_DEBUG > 2)        
          BLYNK_LOG1(BLYNK_F("h:ip"));
#endif
          ip_Updated = true;         
          number_items_Updated++;
          
          if (strlen(value.c_str()) < sizeof(BlynkEthernet_WM_config.static_IP) - 1)
            strcpy(BlynkEthernet_WM_config.static_IP, value.c_str());
          else
            strncpy(BlynkEthernet_WM_config.static_IP, value.c_str(), sizeof(BlynkEthernet_WM_config.static_IP) - 1);
        }
        else if (!nm_Updated && (key == String("nm")))
        {
#if ( BLYNK_WM_DEBUG > 2)
          BLYNK_LOG1(BLYNK_F("h:nm"));
#endif
          nm_Updated = true;         
          number_items_Updated++;
          
          if (strlen(value.c_str()) < sizeof(BlynkEthernet_WM_config.board_name) - 1)
            strcpy(BlynkEthernet_WM_config.board_name, value.c_str());
          else
            strncpy(BlynkEthernet_WM_config.board_name, value.c_str(), sizeof(BlynkEthernet_WM_config.board_name) - 1);
        }

#if USE_DYNAMIC_PARAMETERS        
        for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
        {
          if ( !menuItemUpdated[i] && (key == myMenuItems[i].id) )
          {
#if ( BLYNK_WM_DEBUG > 2)          
            BLYNK_LOG4(BLYNK_F("h:"), myMenuItems[i].id, BLYNK_F("="), value.c_str() );
#endif
            
            menuItemUpdated[i] = true;
            
            number_items_Updated++;

            // Actual size of pdata is [maxlen + 1]
            memset(myMenuItems[i].pdata, 0, myMenuItems[i].maxlen + 1);

            if ((int) strlen(value.c_str()) < myMenuItems[i].maxlen)
              strcpy(myMenuItems[i].pdata, value.c_str());
            else
              strncpy(myMenuItems[i].pdata, value.c_str(), myMenuItems[i].maxlen);
          }
        }
#endif
        
#if ( BLYNK_WM_DEBUG > 3)   
        BLYNK_LOG2(F("h:items updated ="), number_items_Updated);
        BLYNK_LOG4(F("h:key ="), key, ", value =", value);
#endif

#if !USE_STATIC_SERVER        
        server->send(200, "text/html", "OK");
#else
        server.send(200, "text/html", "OK");
#endif        

#if USE_DYNAMIC_PARAMETERS        
        if (number_items_Updated == NUM_CONFIGURABLE_ITEMS + NUM_MENU_ITEMS)
#else
        if (number_items_Updated == NUM_CONFIGURABLE_ITEMS)
#endif
        {
          BLYNK_LOG1(BLYNK_F("h:UpdEEPROM"));

          saveConfigData();
          
          // Done with CP, Clear CP Flag here if forced
          if (isForcedConfigPortal)
            clearForcedCP();

          BLYNK_LOG1(BLYNK_F("h:Rst"));

          // Delay then reset after save data
          delay(200);
          resetFunc();
        }
      }     // if (server)
    }
    
    //////////////////////////////////////////////

    void startConfigurationMode()
    {
#define CONFIG_TIMEOUT			60000L

      // turn the LED_BUILTIN ON to tell us we are in configuration mode.
      digitalWrite(LED_BUILTIN, LED_ON);

      BLYNK_LOG2(BLYNK_F("CfgIP="), Ethernet.localIP() );

#if !USE_STATIC_SERVER
      if (!server)
      {
        server = new EthernetWebServer;
      }
#endif

      //See https://stackoverflow.com/questions/39803135/c-unresolved-overloaded-function-type?rq=1

#if !USE_STATIC_SERVER
      if (server)
#endif
      {
#if USE_STATIC_SERVER
        server.on("/", [this]() { handleRequest(); } );
        server.begin();
#else
        server->on("/", [this]() { handleRequest(); } );
        server->begin();
#endif
      }

      // If there is no saved config Data, stay in config mode forever until having config Data.
      // or SSID, PW, Server,Token ="nothing"
      if (hadConfigData)
      {
        configTimeout = millis() + CONFIG_TIMEOUT;
        
#if ( BLYNK_WM_DEBUG > 2)                   
        BLYNK_LOG4(BLYNK_F("s:millis() = "), millis(), BLYNK_F(", configTimeout = "), configTimeout);
#endif
      }
      else
      {
        configTimeout = 0;
#if ( BLYNK_WM_DEBUG > 2)                   
        BLYNK_LOG1(BLYNK_F("s:configTimeout = 0"));
#endif        
      }

      configuration_mode = true;
    }
    
    bool connectEthernet()
    {
      // Check go see if static IP is required
      IPAddress staticIP;  

      if (staticIP.fromString(BlynkEthernet_WM_config.static_IP))
      {
        
        // Use static IP
        BLYNK_LOG2(BLYNK_F("connectEthernet: Use static_IP="), BlynkEthernet_WM_config.static_IP);
                
        Ethernet.begin(SelectMacAddress(BlynkEthernet_WM_config.Blynk_Creds[0].blynk_token, NULL), staticIP);
        ethernetConnected = true;
      }
      else
      {
        // If static_IP ="nothing"  or NULL, use DHCP dynamic IP
        ethernetConnected = Ethernet.begin(SelectMacAddress(BlynkEthernet_WM_config.Blynk_Creds[0].blynk_token, NULL));
      }

      // give the Ethernet shield a second to initialize:
      BlynkDelay(1000);

      if (ethernetConnected)
      {
        IPAddress myip = Ethernet.localIP();
        BLYNK_LOG_IP("IP:", myip);
      }
      else
      {
        BLYNK_LOG1(BLYNK_F("DHCPFailed"));
        
#if (USE_ETHERNET2 || USE_ETHERNET3)
        // To modify Ethernet2 library to add function link()
        if (Ethernet.link() != 1)
        {
          BLYNK_LOG1(BLYNK_F("BadECable."));
        }
#else      
        if (Ethernet.linkStatus() != LinkON)
        {
          BLYNK_LOG1(BLYNK_F("BadECable."));
        }
#endif        
      }

      return ethernetConnected;
    }

    //////////////////////////////////////////////

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

        if (++mac_index > 5) 
        {
          mac_index = 1;
        }
      }
      
      BLYNK_LOG("MAC: %02X-%02X-%02X-%02X-%02X-%02X",
                macAddress[0], macAddress[1],
                macAddress[2], macAddress[3],
                macAddress[4], macAddress[5]);

      return macAddress;
    }

    byte macAddress[6];

};

#endif
