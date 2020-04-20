/****************************************************************************************************************************
   BI_Ethernet_WMConfig.ino
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

#if defined(ESP8266) || defined(ESP32) || defined(AVR) || (ARDUINO_SAM_DUE) || defined(CORE_TEENSY)
#error This code is designed to run on STM32 platform, not AVR, Teensy, SAM DUE, SAMD, ESP8266 nor ESP32! Please check your Tools->Board setting.
#endif

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

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

#define USE_BLYNK_WM      true
//#define USE_BLYNK_WM      false

#define USE_DYNAMIC_PARAMETERS      true

// Start location in EEPROM to store config data. Default 0.
// Config data Size currently is 128 bytes w/o chksum, 132 with chksum)
#define EEPROM_START     0

#define USE_SSL     false

#if USE_BLYNK_WM

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

/////////////// Start dynamic Credentials ///////////////

//Defined in <BlynkEthernet_WM.h>
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

#else   //USE_BLYNK_WM

#if USE_BUILTIN_ETHERNET
#include <BlynkSimple_STM32BI_Ethernet.h>
#elif USE_UIP_ETHERNET
#include <BlynkSimpleUIPEthernet.h>
#else
#include <BlynkSimpleEthernet.h>
#endif

#include <BlynkSimple_STM32BI_Ethernet.h>

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

#include <DHT.h>

#define DHT_PIN     5
#define DHT_TYPE    DHT11

DHT dht(DHT_PIN, DHT_TYPE);
BlynkTimer timer;

void readAndSendData()
{
  float temperature = dht.readTemperature();
  float humidity    = dht.readHumidity();

  if (Blynk.connected())
  {
    if (!isnan(temperature) && !isnan(humidity))
    {
      Blynk.virtualWrite(V17, String(temperature, 1));
      Blynk.virtualWrite(V18, String(humidity, 1));
    }
    else
    {
      Blynk.virtualWrite(V17, F("NAN"));
      Blynk.virtualWrite(V18, F("NAN"));
    }
  }

  // Blynk Timer uses millis() and is still working even if WiFi/Blynk not connected
  Serial.print(F("R"));
}

void heartBeatPrint(void)
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
  Serial.println("\nStart BI_Ethernet_WM_Config on " + String(DEVICE_NAME) + " board, running " + String(ETHERNET_NAME));

  dht.begin();

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

  timer.setInterval(60000L, readAndSendData);
}

#if (USE_BLYNK_WM && USE_DYNAMIC_PARAMETERS)
void displayCredentials(void)
{
  Serial.println("\nYour stored Credentials :");

  for (int i = 0; i < NUM_MENU_ITEMS; i++)
  {
    Serial.println(String(myMenuItems[i].displayName) + " = " + myMenuItems[i].pdata);
  }
}
#endif

void loop()
{
  Blynk.run();
  timer.run();
  check_status();

#if (USE_BLYNK_WM && USE_DYNAMIC_PARAMETERS)
  static bool displayedCredentials = false;

  if (!displayedCredentials)
  {
    for (int i = 0; i < NUM_MENU_ITEMS; i++)
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
