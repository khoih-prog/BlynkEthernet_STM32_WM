## BlynkEthernet_STM32_Manager

[![arduino-library-badge](https://www.ardu-badge.com/badge/BlynkEthernet_STM32_WM.svg?)](https://www.ardu-badge.com/BlynkEthernet_STM32_WM)

### New in Version v1.0.2

1. Fix crashing bug when using dynamic EthernetServer
2. Enhance examples, fix indentation, update README.md

- This is the new library, adding to the current Blynk_WiFiManager. It's designed to help you eliminate `hardcoding` your Blynk credentials in `STM32` boards using with Ethernet (Built-in LAN8742A, W5100, W5200, W5500, ENC28J60, etc). It's currently not supporting SSL and can not saved config dada to non-volatile memory (EEPROM, battery-saved SRAM, SPIFFS, etc.). To be fixed in future releases.
- You can update Blynk Credentials any time you need to change via Configure Portal. Data to be saved in configurable locations in EEPROM.

This library currently supports
1. STM32 boards with built-in Ethernet LAN8742A such as :
  - ***Nucleo-144 (F429ZI, F767ZI)***
  - ***Discovery (STM32F746G-DISCOVERY)***
  - ***All STM32 Boards with Built-in Ethernet***, See [How To Use Built-in Ethernet](https://github.com/khoih-prog/EthernetWebServer_STM32/issues/1)
2. ***STM32 boards (with 64+K Flash) running ENC28J60 shields***
3. ***STM32 boards (with 64+K Flash) running W5x00 shields***

## Prerequisite
1. [`Arduino IDE 1.8.12 or later` for Arduino](https://www.arduino.cc/en/Main/Software)
2. [`Blynk library 0.6.1 or later`](https://www.arduino.cc/en/guide/libraries#toc3)
3. [`Arduino Core for STM32 1.8.0 or later`](https://github.com/stm32duino/Arduino_Core_STM32) for STM32 (Use Arduino Board Manager)
3. Depending on which Ethernet card you're using:
   - [`STM32Ethernet library`](https://github.com/stm32duino/STM32Ethernet) for built-in Ethernet LAN8742A on (Nucleo-144, Discovery, etc.)
   - [`UIPEthernet library`](https://github.com/UIPEthernet/UIPEthernet) for ENC28J60
   - [`Ethernet library`](https://www.arduino.cc/en/Reference/Ethernet) for W5100, W5200 and W5500
4. [`EthernetWebServer_STM32 library`](https://github.com/khoih-prog/EthernetWebServer_STM32)

### Installation

The suggested way to install is to:

#### Use Arduino Library Manager
The best way is to use `Arduino Library Manager`. Search for `BlynkEthernet_STM32_Manager`, then select / install the latest version. 
You can also use this link [![arduino-library-badge](https://www.ardu-badge.com/badge/BlynkEthernet_STM32_Manager.svg?)](https://www.ardu-badge.com/BlynkEthernet_STM32_Manager) for more detailed instructions.

#### Manual Install

1. Navigate to [BlynkEthernet_STM32_Manager](https://github.com/khoih-prog/BlynkEthernet_STM32_WM) page.
2. Download the latest release `BlynkEthernet_STM32_WM-master.zip`.
3. Extract the zip file to `BlynkEthernet_STM32_WM-master` directory 
4. Copy whole 
  - `BlynkEthernet_STM32_WM-master/src` folder to Arduino libraries' directory such as `~/Arduino/libraries/`.

### How to use

In your code, replace
1. `BlynkSimpleEthernet.h`      with `BlynkSTM32Ethernet_WM.h`        for board using W5100, W5200, W5500 `without SSL`
2. `BlynkSimpleUIPEthernet.h`   with `BlynkSTM32UIPEthernet_WM.h`     for board using ENC28J60 `without SSL`

For STM32 with built-in Ethernet, use 

3. `BlynkSTM32BIEthernet_WM.h`


Then replace `Blynk.begin(...)` with :

1. `Blynk.begin()`

in your code. Keep `Blynk.run()` intact.

That's it.

Also see examples: 
 1. [AM2315_W5100](examples/AM2315_W5100)
 2. [DHT11_W5100](examples/DHT11_W5100)
 3. [W5100_Blynk](examples/W5100_Blynk) 
 4. [W5100_WM_Config](examples/W5100_WM_Config)
 5. [W5100_Blynk_Email](examples/W5100_Blynk_Email)
 6. [ENC28J60_Blynk](examples/ENC28J60_Blynk) 
 7. [ENC28J60_WM_Config](examples/ENC28J60_WM_Config)
 8. [ENC28J60_Blynk_Email](examples/ENC28J60_Blynk_Email)
 9. [BI_Ethernet_Blynk](examples/BI_Ethernet_Blynk) 
10. [BI_Ethernet_WM_Config](examples/BI_Ethernet_WM_Config)
11. [BI_Ethernet_Blynk_Email](examples/BI_Ethernet_Blynk_Email)
12. [BlynkHTTPClient](examples/BlynkHTTPClient)


## So, how it works?
If no valid config data are stored in EEPROM, it will switch to `Configuration Mode`. Connect to access point at the IP address displayed on Terminal or Router's DHCP server as in the following picture:

<p align="center">
    <img src="https://github.com/khoih-prog/BlynkEthernet_STM32_WM/blob/master/pics/Selection_1.png">
</p>

After you connected to, for example, `192.168.2.86`, the Browser will display the following picture:

<p align="center">
    <img src="https://github.com/khoih-prog/BlynkEthernet_STM32_WM/blob/master/pics/Selection_2.png">
</p>

Enter your credentials (Blynk Server and Port). If you prefer static IP, input it (for example `192.168.2.79`) in the corresponding field. Otherwise, just leave it `blank` or `nothing` to use auto IP assigned by DHCP server.

<p align="center">
    <img src="https://github.com/khoih-prog/BlynkEthernet_STM32_WM/blob/master/pics/Selection_3.png">
</p>

Then click `Save`. After the  board auto-restarted, you will see if it's connected to your Blynk server successfully as in  the following picture:

<p align="center">
    <img src="https://github.com/khoih-prog/BlynkEthernet_STM32_WM/blob/master/pics/Selection_4.png">
</p>

This `Blynk.begin()` is not a blocking call, so you can use it for critical functions requiring in loop(). 
Anyway, this is better for projects using Blynk just for GUI (graphical user interface).

In operation, if Ethernet or Blynk connection is lost, `Blynk.run()` will try reconnecting automatically. Therefore, `Blynk.run()` must be called in the `loop()` function. Don't use:

```cpp
void loop()
{
  if (Blynk.connected())
     Blynk.run();
     
  ...
}
```
just

```cpp
void loop()
{
  Blynk.run();
  ...
}
```

## TO DO

1. Same features for other boards with Ethernet shields.

## DONE

 1. Permit EEPROM size and location configurable to avoid conflict with others.
 2. More flexible to configure reconnection timeout.
 3. For fresh config data, don't need to wait for connecting timeout before entering config portal.
 4. If the config data not entered completely (Server, HardwarePort and Blynk token), entering config portal
 5. Change Synch XMLHttpRequest to Async
 6. Reduce memory usage.
 7. Support W5x00, ENC28J60 Ethernet shield as well as built-in Ethernet LAN8742A
 8. Add checksum
 9. Support STM32 boards

## TO DO
 1. Make simulated EEPROM work on all STM32 boards
 2. Find out why EthernetServer dynamic allocation creates random crashes when using Blynk_WM

## Example
Please take a look at examples, as well.
```
#if defined(ESP8266) || defined(ESP32) || defined(AVR) || (ARDUINO_SAM_DUE)
#error This code is designed to run on STM32 platform, not AVR, SAM DUE, SAMD, ESP8266 nor ESP32! Please check your Tools->Board setting.
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
//#define USE_BLYNK_WM      false

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

#if !(USE_BUILTIN_ETHERNET || USE_UIP_ETHERNET)
  #define W5100_CS  10
  #define SDCARD_CS 4
#endif

void setup()
{
  // Debug console
  Serial.begin(115200);
  Serial.println("\nStart BI_Ethernet_Blynk on " + String(DEVICE_NAME) + " board, running " + String(ETHERNET_NAME));

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
  check_status();
}
```

The following is the sample terminal output when running example [BI_Ethernet_Blynk](examples/BI_Ethernet_Blynk) on Nucleo-144 F767ZI with built-in Ethernet PHY.

```
Start BI_Ethernet_Blynk on STM32F7 board, running Built-in LAN8742A Ethernet
[1] EEPROM, sz:16384
[3] CCksum=0x0,RCksum=0x0
[5] InitEEPROM
[7] Hdr=LAN8742A,Auth=nothing
[10] Svr=nothing,Port=8080
[12] SIP=nothing,BName=nothing
[15] MAC: FE-AB-C5-9B-D2-B5
[7324] Dynamic IP OK, connected
[8324] IP:192.168.2.116
[8324] bg: No cfgdat. Stay
F[12927] SaveEEPROM, chkSum=0x1b9a
[12927] Hdr=LAN8742A,Auth=****
[12930] Svr=account.duckdns.org,Port=8080
[12933] SIP=nothing,BName=STM32-F767ZI-WM
[12937] 
    ___  __          __
   / _ )/ /_ _____  / /__
  / _  / / // / _ \/  '_/
 /____/_/\_, /_//_/_/\_\
        /___/ v0.6.1 on Arduino

[12950] BlynkArduinoClient.connect: Connecting to account.duckdns.org:8080
[13030] Ready (ping: 4ms).
[13097] run: got E&B
BBBBBBBBBB BBBBBBBBBB BBBBBBBBBB BBBBBBBBBB BBBBBBBBBB BBBBBBBBBB BBBBBBBBBB BBBBBBBBBB
BBBBBBBBBB BBBBBBBBBB BBBBBBBBBB BBBBBBBBBB BBBBBBBBBB BBBBBBBBBB BBBBBBBBBB BBBBBBBBBB
BBBBBBBBBB BBBBBBBBBB BBBBBBBBBB BBBBBBBBBB BBBBBBBBBB BBBBBBBBBB BBBBBBBBBB BBBBBBBBBB
BBBBBBBBBB BBBBBBBBBB BBBB
```

### New in Version v1.0.2

1. Fix crashing bug when using dynamic EthernetServer
2. Enhance examples, fix indentation, update README.md

### Releases v1.0.1

***New in this version***

1. Fix hanging bug in STM32 boards with built-in Ethernet LAN8742A.

### Releases v1.0.0

***New in this version***

1. Add support to STM32 boards with built-in Ethernet LAN8742A, ENC28J60 or W5x00 Ethernet shields 

## Contributing

If you want to contribute to this project:
- Report bugs and errors
- Ask for enhancements
- Create issues and pull requests
- Tell other people about this library

## Copyright

Copyright 2020- Khoi Hoang
