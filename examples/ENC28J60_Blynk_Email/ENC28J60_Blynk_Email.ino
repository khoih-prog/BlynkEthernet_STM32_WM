/****************************************************************************************************************************
 * ENC28J60_Blynk_Email.ino
 * For STM32 running ENC28J60 Ethernet shields
 *
 * BlynkSTM32Ethernet_WM is a library for the STM32 running built-in Ethernet, ENC28J60 or W5x00 Ethernet shields
 * to enable easy configuration/reconfiguration and autoconnect/autoreconnect to Blynk
 * Forked from Blynk library v0.6.1 https://github.com/blynkkk/blynk-library/releases
 * Built by Khoi Hoang https://github.com/khoih-prog/BlynkGSM_ESPManager
 * Licensed under MIT license
 * Version: 1.0.2
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
 *  1.0.2   K Hoang      06/03/2020 Fix crashing bug when using dynamic EthernetServer
 *****************************************************************************************************************************/
 
#if defined(ESP8266) || defined(ESP32) || defined(AVR) || (ARDUINO_SAM_DUE)
#error This code is designed to run on STM32 platform, not AVR, SAM DUE, SAMD, ESP8266 nor ESP32! Please check your Tools->Board setting.
#endif

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

#define USE_BUILTIN_ETHERNET    false
//  If don't use USE_BUILTIN_ETHERNET, and USE_UIP_ETHERNET => use W5x00 with Ethernet library
#define USE_UIP_ETHERNET        true 

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

BlynkTimer timer;

#define BUTTON_PIN      2

volatile unsigned int count       = 0;
volatile bool isButtonPressed     = false;

void emailOnButtonPress()
{
  //isButtonPressed = !digitalRead(BUTTON_PIN); // Invert state, since button is "Active LOW"
  
  if ( !isButtonPressed && !digitalRead(BUTTON_PIN)) // You can write any condition to trigger e-mail sending
  {
    isButtonPressed = true;
    count++;
    Serial.println("Button pressed");
  }
}

void processButton(void)
{
  // *** WARNING: You are limited to send ONLY ONE E-MAIL PER 5 SECONDS! ***
  // Let's send an e-mail when you press the button
  // connected to digital pin BUTTON_PIN (2) on your Arduino
  static String body;
  
  if (isButtonPressed) // You can write any condition to trigger e-mail sending
  {
    body = String("You pushed the button ") + count + " times.";

    // This can be seen in the Serial Monitor
    Serial.println(body);

    Blynk.email("your_email@gmail.com", "Subject: Button Logger", body);

    isButtonPressed = false;
  }
}

void setup()
{
  // Debug console
  Serial.begin(115200);
  Serial.println("\nStart ENC28J60_Blynk_Email on " + String(DEVICE_NAME) + " board, running " + String(ETHERNET_NAME));

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  
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

  // Attach pin BUTTON_PIN (2) interrupt to our handler
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), emailOnButtonPress, FALLING /*CHANGE*/);

  timer.setInterval(30000L, processButton);
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

void loop()
{
  Blynk.run();
  timer.run();
  check_status();
}
