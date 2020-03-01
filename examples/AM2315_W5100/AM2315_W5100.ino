/****************************************************************************************************************************
 * AM2315_W5100.ino
 * For STM32 running built-in Ethernet
 *
 * BlynkSimpleEthernet_WM is a library for the AVR / Teensy platform to enable easy
 * configuration/reconfiguration and autoconnect/autoreconnect of Ethernet Shield W5x00/Blynk
 * Forked from Blynk library v0.6.1 https://github.com/blynkkk/blynk-library/releases
 * Built by Khoi Hoang https://github.com/khoih-prog/BlynkGSM_ESPManager
 * Licensed under MIT license
 * Version: 1.0.0
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
 *****************************************************************************************************************************/

#if defined(ESP8266) || defined(ESP32)
#error This code is designed to run on Arduino AVR, SAM, SAMD, Teensy platform, not ESP8266 nor ESP32! Please check your Tools->Board setting.
#endif

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

#if defined(ARDUINO_ARCH_STM32F1)
  #define DEVICE_NAME  "STM32F1"
  #define BLYNK_NO_YIELD
#elif defined(ARDUINO_ARCH_STM32F3)
  #define DEVICE_NAME  "STM32F3"
  #define BLYNK_NO_YIELD
#elif defined(ARDUINO_ARCH_STM32F4)
  #define DEVICE_NAME  "STM32F4"
  #define BLYNK_NO_YIELD
#elif defined(ARDUINO_ARCH_STM32F7)
  #define DEVICE_NAME  "STM32F7"  
  #define BLYNK_NO_YIELD
#else
  #define DEVICE_NAME  "STM32 Unknown"  
  #define BLYNK_NO_YIELD
#endif
        

#define USE_BUILTIN_ETHERNET    false
//  If don't use USE_BUILTIN_ETHERNET, and USE_UIP_ETHERNET => use W5x00 with Ethernet library
#define USE_UIP_ETHERNET        true 

#if (USE_BUILTIN_ETHERNET)
  #define ETHERNET_NAME     "Built-in STM32 Ethernet"
#elif (USE_UIP_ETHERNET)
  #define ETHERNET_NAME     "ENC28J60 Ethernet Shield"
#else
  #define ETHERNET_NAME     "W5x00 Ethernet Shield"
#endif

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
#define W5100_CS  10
#define SDCARD_CS 4

#include <Wire.h>
#include <Adafruit_AM2315.h>        // To install Adafruit AM2315 library

// Connect RED of the AM2315 sensor to 5.0V
// Connect BLACK to Ground
// Connect WHITE to i2c clock (SCL) - on '168/'328 Arduino Uno/Duemilanove/etc that's Analog 5
// Connect YELLOW to i2c data (SDA) - on '168/'328 Arduino Uno/Duemilanove/etc that's Analog 4

Adafruit_AM2315 AM2315;

#define AM2315_DEBUG     false

BlynkTimer timer;

#define READ_INTERVAL        30000L          //read AM2315 interval 30s

void ReadData()
{
  static float temperature, humidity;
  
  if (!AM2315.readTemperatureAndHumidity(&temperature, &humidity)) 
  {
    #if AM2315_DEBUG
    Serial.println(F("Failed to read data from AM2315"));
    #endif
    
    return;
  }

  #if AM2315_DEBUG
  Serial.print(F("Temp *C: "));
  Serial.println(String(temperature));
  Serial.print(F("Humid %: "));
  Serial.println(String(humidity)); 
  #endif

  //V1 and V2 are Blynk Display widgets' VPIN
  Blynk.virtualWrite(V1, temperature);
  Blynk.virtualWrite(V2, humidity);
}

void setup()
{
  Serial.begin(115200);
  Serial.println("\nStart AM2315_W5100 on STM32 running " + String(ETHERNET_NAME) + " " + String(DEVICE_NAME));

#if !(USE_BUILTIN_ETHERNET || USE_UIP_ETHERNET)
  pinMode(SDCARD_CS, OUTPUT);
  digitalWrite(SDCARD_CS, HIGH); // Deselect the SD card
#endif
  
  if (!AM2315.begin()) 
  {
    Serial.println(F("Sensor not found, check wiring & pullups!"));
  }

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

  timer.setInterval(READ_INTERVAL, ReadData);
}

void loop()
{  
  Blynk.run();
  timer.run();
}
