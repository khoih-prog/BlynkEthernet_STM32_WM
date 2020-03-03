/****************************************************************************************************************************
 * BlynkHTTPClient.ino
 * For STM32 running built-in Ethernet, ENC28J60, W5x00 Ethernet or GSM/GPRS shields
 *
 * BlynkSTM32Ethernet_WM is a library for the STM32 running built-in Ethernet, ENC28J60 or W5x00 Ethernet shields
 * to enable easy configuration/reconfiguration and autoconnect/autoreconnect to Blynk
 * Forked from Blynk library v0.6.1 https://github.com/blynkkk/blynk-library/releases
 * Built by Khoi Hoang https://github.com/khoih-prog/BlynkGSM_ESPManager
 * Licensed under MIT license
 * Version: 1.0.1
 *
 * Original Blynk Library author:
 * @file       BlynkGsmClient.h
 * @author     Volodymyr Shymanskyy
 * @license    This project is released under the MIT License (MIT)
 * @copyright  Copyright (c) 2015 Volodymyr Shymanskyy
 * @date       Jan 2015
 * @brief
 *
 * Version Modified By   Date      Comments
 * ------- -----------  ---------- -----------
 *  1.0.0   K Hoang      28/02/2020 Initial coding for STM32 running built-in Ethernet, ENC28J60 or W5x00 Ethernet shields
 *  1.0.1   K Hoang      03/03/2020 Fix bug for built-in Ethernet LAN8742A
 *****************************************************************************************************************************/
 
#if defined(ESP8266) || defined(ESP32) || defined(AVR) || (ARDUINO_SAM_DUE)
#error This code is designed to run on STM32 platform, not AVR, SAM DUE, SAMD, ESP8266 nor ESP32! Please check your Tools->Board setting.
#endif

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

#define USE_ETHERNET    true

#define USE_BUILTIN_ETHERNET    true
//  If don't use USE_BUILTIN_ETHERNET, and USE_UIP_ETHERNET => use W5x00 with Ethernet library
#define USE_UIP_ETHERNET        false 

#if (USE_BUILTIN_ETHERNET)
  #define ETHERNET_NAME     "Built-in LAN8742A Ethernet"
#elif (USE_UIP_ETHERNET)
  #define ETHERNET_NAME     "ENC28J60 Ethernet Shield"
#else
  #define ETHERNET_NAME     "W5x00 Ethernet Shield"
#endif

#if defined(STM32F0)
  #warning STM32F0 board selected
  #define DEVICE_NAME  "STM32F0"
#elif defined(STM32F1)
  #warning STM32F1 board selected
  #define DEVICE_NAME  "STM32F1"
#elif defined(STM32F2)
  #warning STM32F2 board selected
  #define DEVICE_NAME  "STM32F2"
#elif defined(STM32F3)
  #warning STM32F3 board selected
  #define DEVICE_NAME  "STM32F3"
#elif defined(STM32F4)
  #warning STM32F4 board selected
  #define DEVICE_NAME  "STM32F4"
#elif defined(STM32F7)
  #warning STM32F7 board selected
  #define DEVICE_NAME  "STM32F7"  
#else
  #warning STM32 unknown board selected
  #define DEVICE_NAME  "STM32 Unknown"  
#endif

#define BLYNK_NO_YIELD
        
// Default heartbeat interval for GSM is 60
// If you want override this value, uncomment and set this option:
//#define BLYNK_HEARTBEAT 30

// Set serial for debug console (to the Serial Monitor, default speed 115200)
#define SerialMon Serial

#if ( USE_ETHERNET )

  // Start location in EEPROM to store config data. Default 0.
  // Config data Size currently is 128 bytes w/o chksum, 132 with chksum)
  #define EEPROM_START     0
  
  #define USE_SSL     false
  
  #define USE_CHECKSUM      true
  
  #if USE_SSL
    // Need ArduinoECCX08 and ArduinoBearSSL libraries
    // Currently, error not enough memory for many STM32 boards. Don't use
    #error SSL not support
  #else
    #if USE_BUILTIN_ETHERNET
      #include <BlynkSTM32BIEthernet_WM.h>
    #elif USE_UIP_ETHERNET
      #include <BlynkSTM32UIPEthernet_WM.h>
    #else
      #include <BlynkSTM32Ethernet_WM.h>
    #endif 
  #endif
  
  #define USE_BLYNK_WM      true
  
  #if !USE_BLYNK_WM
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
  #endif

  // You can specify your board mac adress
  byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
  
  // Use this for static IP
  IPAddress local_ip      (192, 168, 2, 99);
  IPAddress local_dns     (192, 168, 2, 1);
  IPAddress local_gateway (192, 168, 2, 1);
  IPAddress local_subnet  (255, 255, 255, 0);

  #if !(USE_BUILTIN_ETHERNET || USE_UIP_ETHERNET)
    // Ethernet shield and SDcard pins
    #define W5100_CS  10
    #define SDCARD_CS 4
  #endif
  
  EthernetClient client;

#else
  // Select your modem:
  #define TINY_GSM_MODEM_SIM800
  // #define TINY_GSM_MODEM_SIM808
  // #define TINY_GSM_MODEM_SIM900
  // #define TINY_GSM_MODEM_UBLOX
  // #define TINY_GSM_MODEM_BG96
  // #define TINY_GSM_MODEM_A6
  // #define TINY_GSM_MODEM_A7
  // #define TINY_GSM_MODEM_M590
  // #define TINY_GSM_MODEM_ESP8266
  // #define TINY_GSM_MODEM_XBEE

  // Increase RX buffer if needed
  //#define TINY_GSM_RX_BUFFER 512

  #include <TinyGsmClient.h>
  //#include <BlynkSimpleSIM800.h>
  #include <BlynkSimpleTinyGSM.h>

  // Hardware Serial on Mega, Leonardo, Micro
  //#define SerialAT Serial1
  #define SerialAT SERIAL_PORT_HARDWARE

  // Your GPRS credentials
  // Leave empty, if missing user or pass
  #define apn     "YourAPN"
  #define user   "****"
  #define pass    "****"

  #define blynk_gsm_auth     "****"

  // Uncomment this if you want to see all AT commands
  //#define DUMP_AT_COMMANDS

  #ifdef DUMP_AT_COMMANDS
    #include <StreamDebugger.h>
    StreamDebugger debugger(SerialAT, SerialMon);
    TinyGsm modem(debugger);
  #else
    TinyGsm modem(SerialAT);
  #endif  

  TinyGsmClient client(modem);
#endif

#include <ArduinoHttpClient.h>

// Server details. Currently hardcoded.
//http://account.duckdns.org
//#define http_server     "account.duckdns.org"
//#define resource        "/"

#define http_server     "vsh.pp.ua"
#define resource        "/TinyGSM/logo.txt"

#define http_port       80

HttpClient http(client, http_server, http_port);

void setup()
{
  // Set console baud rate
  SerialMon.begin(115200);
  delay(10);

#if ( USE_ETHERNET )
  Serial.println("\nStart BlynkHTTPClient on " + String(DEVICE_NAME) + " board, running " + String(ETHERNET_NAME));
  
  #if !(USE_BUILTIN_ETHERNET || USE_UIP_ETHERNET)
    // Deselect the SD card
    pinMode(SDCARD_CS, OUTPUT);
    digitalWrite(SDCARD_CS, HIGH);
  #endif
  
#else
   Serial.println("\nStart BlynkHTTPClient on " + String(DEVICE_NAME) + " board, running GSM/GPRS Modem");
    
  // Set GSM module baud rate
  SerialAT.begin(115200);
  delay(3000);

  // Restart takes quite some time
  // To skip it, call init() instead of restart()
  SerialMon.println("Initializing modem...");
  modem.restart();

  String modemInfo = modem.getModemInfo();
  SerialMon.print("Modem: ");
  SerialMon.println(modemInfo);

  // Unlock your SIM card with a PIN
  //modem.simUnlock("1234");
#endif

  #if ( USE_ETHERNET )
    #if USE_BLYNK_WM
      Blynk.begin();
    #else
      #if USE_LOCAL_SERVER
        Blynk.begin(blynk_auth, blynk_server, BLYNK_HARDWARE_PORT);
      #else
        Blynk.begin(blynk_auth);
      #endif
    #endif
  #else
    Blynk.begin(blynk_gsm_auth, modem, apn, user, pass);
  #endif

  if (Blynk.connected())
    SerialMon.println("Blynk connected");  
}

void HTTPClientHandle(void)
{
  #if !( USE_ETHERNET )
  
    SerialMon.print(F("Waiting for network..."));
    if (!modem.waitForNetwork()) 
    {
      SerialMon.println(" fail");
      return;
    }
    
    SerialMon.println(" OK");  
    
    SerialMon.print(F("Connecting to "));
    SerialMon.print(apn);
    if (!modem.gprsConnect(apn, user, pass)) 
    {
      SerialMon.println(" fail");
      return;
    }
    SerialMon.println(" OK");
  #endif

#define USE_DIRECT_CLIENT     true

#if USE_DIRECT_CLIENT

  // Test client directly, see Arduino_TinyGSM.ino
  // https://github.com/Xinyuan-LilyGO/TTGO-T-Call/blob/master/examples/Arduino_TinyGSM/Arduino_TinyGSM.ino
  // Just added
  SerialMon.print(F("Connecting to "));
  SerialMon.print(http_server);
  if (!client.connect(http_server, http_port)) 
  {
    SerialMon.println(F(" fail"));
    //delay(10000);
    return;
  }
  SerialMon.println(F(" OK"));
  
    // Make a HTTP GET request:
  SerialMon.println(F("Performing HTTP GET request..."));
  client.print(String(F("GET ")) + resource + F(" HTTP/1.1\r\n"));
  client.print(String(F("Host: ")) + http_server + F("\r\n"));
  client.print(F("Connection: close\r\n\r\n"));
  client.println();
  
  unsigned long timeout = millis();
  while (client.connected() && millis() - timeout < 10000L) 
  {
    // Print available data
    while (client.available()) 
    {
      char c = client.read();
      SerialMon.print(c);
      timeout = millis();
    }
  }
  SerialMon.println();
  
  // Shutdown
  
  client.stop();
    
#else
  SerialMon.print(F("Performing HTTP GET request... "));
  int err = http.get(resource);
  if (err != 0) 
  {
    SerialMon.print(F("failed to connect, error = "));
    SerialMon.println(err);
    return;
  }

  int status = http.responseStatusCode();
  SerialMon.println(status);
  if (!status) 
  {
    SerialMon.print(F("Status Code is: "));
    SerialMon.println(status);
    return;
  }

  while (http.headerAvailable()) 
  {
    String headerName = http.readHeaderName();
    String headerValue = http.readHeaderValue();
    //SerialMon.println(headerName + " : " + headerValue);
  }

  int length = http.contentLength();
  if (length >= 0) 
  {
    SerialMon.print(F("Content length is: "));
    SerialMon.println(length);
  }
  
  if (http.isResponseChunked()) 
  {
    SerialMon.println(F("The response is chunked"));
  }

  String body = http.responseBody();
  SerialMon.println(F("Response:"));
  SerialMon.println(body);

  SerialMon.print(F("Body length is: "));
  SerialMon.println(body.length());

  // Shutdown

  http.stop();
#endif
  
  SerialMon.println(F("Server disconnected"));

  #if !( USE_ETHERNET )
    modem.gprsDisconnect();
    SerialMon.println(F("GPRS disconnected"));
  #endif
}

void check_status()
{
  static unsigned long checkstatus_timeout = 0;

#define STATUS_CHECK_INTERVAL     60000L

  // Send status report every STATUS_REPORT_INTERVAL (60) seconds: we don't need to send updates frequently if there is no status change.
  if ((millis() > checkstatus_timeout) || (checkstatus_timeout == 0))
  {
    HTTPClientHandle();
    checkstatus_timeout = millis() + STATUS_CHECK_INTERVAL;
  }
}

void loop()
{
  Blynk.run();
  check_status();
}
