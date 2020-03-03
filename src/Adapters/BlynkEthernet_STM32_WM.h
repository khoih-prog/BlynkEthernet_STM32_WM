/****************************************************************************************************************************
 * BlynkSTM32Ethernet_WM.h
 * For STM32 running built-in Ethernet LAN8742A, ENC28J60 or W5x00 Ethernet shields
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

#ifndef BlynkEthernet_STM32_WM_h
#define BlynkEthernet_STM32_WM_h

#define BLYNK_ETHERNET_DEBUG      0

#ifndef BLYNK_INFO_CONNECTION
#define BLYNK_INFO_CONNECTION "LAN8742A"
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
#include <EEPROM.h>

#include <IWatchdog.h>

// Comment out or define false in sketch to reduce sketch size
#ifndef USE_CHECKSUM
#define USE_CHECKSUM      false
#endif

// Configurable items besides fixed Header
#define NUM_CONFIGURABLE_ITEMS    5
typedef struct Configuration 
{
    char header         [16];
    char blynk_server   [32];
    int  blynk_port;
    char blynk_token    [36];
    char static_IP      [16];        
    char board_name     [24];
    #if USE_CHECKSUM
    int  checkSum;
    #endif
} Blynk_Configuration;

// Currently CONFIG_DATA_SIZE  =  132 with chksum, 128 wo chksum

#define root_html_template " \
<!DOCTYPE html> \
<meta name=\"robots\" content=\"noindex\"> \
<html> \
<head> \
<meta charset=\"utf-8\"> \
<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"> \
<title>BlynkEthernetSTM32_WM</title> \
</head> \
<body> \
<div align=\"center\"> \
<table> \
<tbody> \
<tr> \
<th colspan=\"2\">Blynk</th> \
</tr> \
<tr> \
<td>Server</td> \
<td><input type=\"text\" value=\"[[b_svr]]\" id=\"b_svr\"></td> \
</tr> \
<tr> \
<td>Port</td> \
<td><input type=\"text\" value=\"[[b_pt]]\" id=\"b_pt\"></td> \
</tr> \
<tr> \
<td>Token</td> \
<td><input type=\"text\" value=\"[[b_tok]]\" id=\"b_tok\"></td> \
</tr> \
<tr> \
<td>StaticIP</td> \
<td><input type=\"text\" value=\"[[s_ip]]\" id=\"s_ip\"></td> \
</tr> \
<tr> \
<th colspan=\"2\">Board</th> \
</tr> \
<tr> \
<td>Name</td> \
<td><input type=\"text\" value=\"[[b_nam]]\" id=\"b_nam\"></td> \
</tr> \
<tr> \
<td colspan=\"2\" align=\"center\"> \
<button onclick=\"save()\">Save</button> \
</td> \
</tr> \
</tbody> \
</table> \
</div> \
<script id=\"jsbin-javascript\"> \
function udVal(key, value) { \
var request = new XMLHttpRequest(); \
var url = '/?key=' + key + '&value=' + value; \
console.log('call ' + url + '...'); \
request.open('GET', url); \
request.send(null); \
} \
function save() { \
udVal('b_svr', document.getElementById('b_svr').value); \
udVal('b_pt', document.getElementById('b_pt').value); \
udVal('b_tok', document.getElementById('b_tok').value); \
udVal('s_ip', document.getElementById('s_ip').value); \
udVal('b_nam', document.getElementById('b_nam').value); \
alert('Reset'); \
} \
</script> \
</body> \
</html>";

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
        #if (BLYNK_ETHERNET_DEBUG > 1)
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
        BLYNK_LOG1(BLYNK_F("Use sIP"));
        #endif
        
        Ethernet.begin(SelectMacAddress(auth, mac), local, dns);
        ethernetConnected = true;
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
        BLYNK_LOG1(BLYNK_F("Use sIP"));
        #endif
        
        Ethernet.begin(SelectMacAddress(auth, mac), local, dns, gateway, subnet);
        ethernetConnected = true;
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
        BLYNK_LOG1(BLYNK_F("Use sIP"));
        #endif
        
        Ethernet.begin(SelectMacAddress(auth, mac), local);
        ethernetConnected = true;
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
        BLYNK_LOG1(BLYNK_F("Use sIP"));
        #endif
        
        Ethernet.begin(SelectMacAddress(auth, mac), local, dns, gateway, subnet);
        ethernetConnected = true;
        // give the Ethernet shield a second to initialize:
        BlynkDelay(1000);
        IPAddress myip = Ethernet.localIP();
        BLYNK_LOG_IP("IP:", myip);

        config(auth, addr, port);
        while(this->connect() != true) {}
    }

		void begin()
    {       
        hadConfigData = getConfigData();
        
        displayConfigData();
        
        connectEthernet();       
                      
        if (hadConfigData)
        {
          config( BlynkEthernet_WM_config.blynk_token, 
                  BlynkEthernet_WM_config.blynk_server, 
                  BlynkEthernet_WM_config.blynk_port);                
 
          if (ethernetConnected) 
          {
            BLYNK_LOG1(BLYNK_F("bg: E.con.Try B"));
            
            int i = 0;
            while ( (i++ < 10) && !this->connect() )
            {
            }
            
            if  (connected())
            {
              BLYNK_LOG1(BLYNK_F("bg: EBconn'd"));
            }
            else 
            {
              BLYNK_LOG1(BLYNK_F("bg: E conn'd, B no conn'd"));
              // failed to connect to Blynk server, will start configuration mode
              startConfigurationMode();
            }
          } 
          else 
          {
              // Can't do anything here
              BLYNK_LOG1(BLYNK_F("bg: Noconn E&B"));
              // failed to connect to Blynk server, will start configuration mode
              //startConfigurationMode();
          }
        }
        else
        {
            BLYNK_LOG1(BLYNK_F("bg: No cfgdat. Stay"));
            // failed to connect to Blynk server, will start configuration mode
            //hadConfigData = false;        
            startConfigurationMode();                  
        }
    }    
       
    void run()
    {     
      static int retryTimes = 0;
      
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
		      retryTimes = 0;
			    
			    if (server)
			      server->handleClient();
			      
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
		          BLYNK_LOG2(BLYNK_F("run: Blost, cfgTimeout. TryB. Num:"), retryTimes);
		        }
		        else
		        {
              STM32Reset();
		        }		        
		      }
		      #endif
		      	      
			    // Not in config mode, try reconnecting before forcing to config mode
			    BLYNK_LOG1(BLYNK_F("run: Blost. Try connB"));
			    if (connect()) 
			    {
			      // turn the LED_BUILTIN OFF to tell us we exit configuration mode.
            digitalWrite(LED_BUILTIN, HIGH);
				    BLYNK_LOG1(BLYNK_F("run: Breconn'd"));
			    }		
        }
      }
      else if (configuration_mode)
      {
      	configuration_mode = false;
      	BLYNK_LOG1(BLYNK_F("run: got E&B"));
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
       
    String getServerName()
    {
      return (String(BlynkEthernet_WM_config.blynk_server));
    }
         
    String getToken()
    {
      return (String(BlynkEthernet_WM_config.blynk_token));
    }
    
    int getHWPort()
    {
      return (BlynkEthernet_WM_config.blynk_port);
    }
    
    void clearConfigData()
    {
      memset(&BlynkEthernet_WM_config, 0, sizeof(BlynkEthernet_WM_config));
      //EEPROM.put(EEPROM_START, BlynkEthernet_WM_config);
    }   
                 
private:

    // Initialize the Ethernet server library
    // with the IP address and port you want to use
    // (port 80 is default for HTTP):
    EthernetWebServer *server;
    
    bool ethernetConnected = false;

    bool configuration_mode = false;
    
    unsigned long configTimeout;
    bool hadConfigData = false;    
    
    Blynk_Configuration BlynkEthernet_WM_config;

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
      
      #if (BLYNK_ETHERNET_DEBUG > 0)
			BLYNK_LOG2(BLYNK_F("Hname = "), RFC952_hostname);
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
      
    void displayConfigData(void)
		{
		    BLYNK_LOG4(BLYNK_F("Hdr="), BlynkEthernet_WM_config.header, BLYNK_F(",Auth="),  BlynkEthernet_WM_config.blynk_token);
        BLYNK_LOG4(BLYNK_F("Svr="), BlynkEthernet_WM_config.blynk_server, 
                   BLYNK_F(",Port="), BlynkEthernet_WM_config.blynk_port);
        BLYNK_LOG4(BLYNK_F("SIP="), BlynkEthernet_WM_config.static_IP, 
                   BLYNK_F(",BName="), BlynkEthernet_WM_config.board_name);     
		} 

//#define BLYNK_BOARD_TYPE      "W5X00"
#define BLYNK_BOARD_TYPE      BLYNK_INFO_CONNECTION
      
#define WM_NO_CONFIG       "nothing"
    
// Currently 128 + 4 (chsum)
uint16_t CONFIG_DATA_SIZE = sizeof(Blynk_Configuration);


#if USE_CHECKSUM
    int calcChecksum()
    {
      int checkSum = 0;
      for (uint16_t index = 0; index < (sizeof(BlynkEthernet_WM_config) - sizeof(BlynkEthernet_WM_config.checkSum)); index++)
      {
        checkSum += * ( ( (byte*) &BlynkEthernet_WM_config ) + index);
      }
     
      return checkSum;
    }
#endif

    //Functionality to 'get' and 'put' objects to and from EEPROM.
    template< typename T > T &EEPROM_get(int idx, T &t)
    {
      //EEPtr e = idx;
      int e = idx;
      uint8_t *ptr = (uint8_t *) &t;
      
      for (int count = sizeof(T) ; count ; --count, ++e) 
      {
        //*ptr++ = *e;
        *ptr++ = eeprom_buffered_read_byte(e);
      }
      return t;
    }

    template< typename T > const T &EEPROM_put(int idx, const T &t)
    {
      //EEPtr e = idx;
      int e = idx;  
      const uint8_t *ptr = (const uint8_t *) &t;
      
      for (int count = sizeof(T) ; count ; --count, ++e) 
      {
        //(*e).update(*ptr++);
        eeprom_buffered_write_byte(e, *ptr++);
      }

      eeprom_buffer_flush();

      return t;
    }

    bool getConfigData()
    {     
      //EEPROM.begin();
      BLYNK_LOG2(BLYNK_F("EEPROM, sz:"), EEPROM.length());  
      //EEPROM.get(EEPROM_START, BlynkEthernet_WM_config);
      //EEPROM_get(EEPROM_START, BlynkEthernet_WM_config);

#if USE_CHECKSUM
      int calChecksum = calcChecksum();
      
      BLYNK_LOG4(BLYNK_F("CCksum=0x"), String(calChecksum, HEX), 
                 BLYNK_F(",RCksum=0x"), String(BlynkEthernet_WM_config.checkSum, HEX)); 
      
      if ( (strncmp(BlynkEthernet_WM_config.header, BLYNK_BOARD_TYPE, strlen(BLYNK_BOARD_TYPE)) != 0) ||
           (calChecksum != BlynkEthernet_WM_config.checkSum) )           
#else                 

      if (strncmp(BlynkEthernet_WM_config.header, BLYNK_BOARD_TYPE, strlen(BLYNK_BOARD_TYPE)) != 0) 
#endif      
      {
          memset(&BlynkEthernet_WM_config, 0, sizeof(BlynkEthernet_WM_config));
                                   
          BLYNK_LOG1(BLYNK_F("InitEEPROM"));          
          // doesn't have any configuration
          strcpy(BlynkEthernet_WM_config.header,           BLYNK_BOARD_TYPE);
          strcpy(BlynkEthernet_WM_config.blynk_server,     WM_NO_CONFIG);
          BlynkEthernet_WM_config.blynk_port = BLYNK_SERVER_HARDWARE_PORT;
          strcpy(BlynkEthernet_WM_config.blynk_token,      WM_NO_CONFIG);
          strcpy(BlynkEthernet_WM_config.static_IP,        WM_NO_CONFIG);
          strcpy(BlynkEthernet_WM_config.board_name,       WM_NO_CONFIG);
          #if USE_CHECKSUM
          // Don't need
          BlynkEthernet_WM_config.checkSum = 0;
          #endif

          //EEPROM.put(EEPROM_START, BlynkEthernet_WM_config);
          //EEPROM_put(EEPROM_START, BlynkEthernet_WM_config);
          
          return false;
      }  
      else if ( !strncmp(BlynkEthernet_WM_config.blynk_server,    WM_NO_CONFIG, strlen(WM_NO_CONFIG) )  ||
                !strncmp(BlynkEthernet_WM_config.blynk_token,     WM_NO_CONFIG, strlen(WM_NO_CONFIG) ) ) 
      {
        // If SSID, PW, Server,Token ="nothing", stay in config mode forever until having config Data.
        return false;
      }  
      else
      {
        displayConfigData();                
      }
      
      return true;
    }      
    
    void saveConfigData()
    {      
      #if USE_CHECKSUM
      int calChecksum = calcChecksum();
      BlynkEthernet_WM_config.checkSum = calChecksum;    
      //BLYNK_LOG4(BLYNK_F("SaveEEPROM,sz="), EEPROM.length(), BLYNK_F(",chkSum=0x"), String(calChecksum, HEX));
      BLYNK_LOG2(BLYNK_F("SaveEEPROM, chkSum=0x"), String(calChecksum, HEX));
      #endif
      
      displayConfigData();
      
      //EEPROM.put(EEPROM_START, BlynkEthernet_WM_config);
      //EEPROM_put(EEPROM_START, BlynkEthernet_WM_config);
    }
    

    void handleRequest()
    {     
      if (server)
      {
        String key = server->arg("key");
        String value = server->arg("value");
         
        static int number_items_Updated = 0;

        if (key == "" && value == "") 
        {
            String result = root_html_template;
            
            #if (BLYNK_ETHERNET_DEBUG > 1)
            BLYNK_LOG1(BLYNK_F("hR: Repl.Result"));
            #endif
            
            // Reset configTimeout to stay here until finished.
            configTimeout = 0;

            result.replace("[[b_svr]]",     BlynkEthernet_WM_config.blynk_server);
            result.replace("[[b_pt]]",      String(BlynkEthernet_WM_config.blynk_port));
            result.replace("[[b_tok]]",     BlynkEthernet_WM_config.blynk_token);
            result.replace("[[s_ip]]",      BlynkEthernet_WM_config.static_IP);
            result.replace("[[b_nam]]",     BlynkEthernet_WM_config.board_name);
            
            server->send(200, "text/html", result);
          
            return;
        }
       
        if (number_items_Updated == 0)
        {
          memset(&BlynkEthernet_WM_config, 0, sizeof(BlynkEthernet_WM_config));
          strcpy(BlynkEthernet_WM_config.header, BLYNK_BOARD_TYPE);
        }
        
        if (key == "b_svr") 
        {
            #if (BLYNK_ETHERNET_DEBUG > 2)
            BLYNK_LOG1(BLYNK_F("hR: b_svr"));
            #endif
            number_items_Updated++;
            if (strlen(value.c_str()) < sizeof(BlynkEthernet_WM_config.blynk_server) -1)
              strcpy(BlynkEthernet_WM_config.blynk_server, value.c_str());
            else
              strncpy(BlynkEthernet_WM_config.blynk_server, value.c_str(), sizeof(BlynkEthernet_WM_config.blynk_server) -1);    
        }
        else if (key == "b_pt") 
        {
            #if (BLYNK_ETHERNET_DEBUG > 2)
            BLYNK_LOG1(BLYNK_F("hR: b_pt"));
            #endif
            number_items_Updated++;
            BlynkEthernet_WM_config.blynk_port = value.toInt();
        }
        else if (key == "b_tok") 
        {
            #if (BLYNK_ETHERNET_DEBUG > 2)
            BLYNK_LOG1(BLYNK_F("hR: b_tok"));
            #endif
            number_items_Updated++;
            if (strlen(value.c_str()) < sizeof(BlynkEthernet_WM_config.blynk_token) -1)
              strcpy(BlynkEthernet_WM_config.blynk_token, value.c_str());
            else
              strncpy(BlynkEthernet_WM_config.blynk_token, value.c_str(), sizeof(BlynkEthernet_WM_config.blynk_token) -1);              
        }
        else if (key == "s_ip") 
        {
            #if (BLYNK_ETHERNET_DEBUG > 2)
            BLYNK_LOG1(BLYNK_F("hR: s_ip"));
            #endif
            number_items_Updated++;
            if (strlen(value.c_str()) < sizeof(BlynkEthernet_WM_config.static_IP) -1)
              strcpy(BlynkEthernet_WM_config.static_IP, value.c_str());
            else
              strncpy(BlynkEthernet_WM_config.static_IP, value.c_str(), sizeof(BlynkEthernet_WM_config.static_IP) -1);              
        }      
        else if (key == "b_nam") 
        {
            #if (BLYNK_ETHERNET_DEBUG > 2)
            BLYNK_LOG1(BLYNK_F("hR: b_nam"));
            #endif
            number_items_Updated++;
            if (strlen(value.c_str()) < sizeof(BlynkEthernet_WM_config.board_name) -1)
              strcpy(BlynkEthernet_WM_config.board_name, value.c_str());
            else
              strncpy(BlynkEthernet_WM_config.board_name, value.c_str(), sizeof(BlynkEthernet_WM_config.board_name) -1);
        }
        
        #if (BLYNK_ETHERNET_DEBUG > 2)
        BLYNK_LOG1(BLYNK_F("hR: OK"));
        #endif
        
        server->send(200, "text/html", "OK");
        
        if (number_items_Updated == NUM_CONFIGURABLE_ITEMS)
        {
          #if (BLYNK_ETHERNET_DEBUG > 2)
          BLYNK_LOG1(BLYNK_F("hR: Upd EEPROM"));
          #endif

          saveConfigData();

          #if (BLYNK_ETHERNET_DEBUG > 2)
          BLYNK_LOG1(BLYNK_F("hR: Rst"));
          #endif
          
          #if 0
            STM32Reset();
          #else
            config(BlynkEthernet_WM_config.blynk_token, BlynkEthernet_WM_config.blynk_server, BlynkEthernet_WM_config.blynk_port);
            this->connect();
          #endif
        }  
      }     // if (server)
    }
    
    void STM32Reset()
    {
      // Initialize the IWDG with 2 seconds timeout.
      // This would cause a CPU reset if the IWDG timer
      // is not reloaded in approximately 2 seconds.
      IWatchdog.begin(2000000);   
    }
        
    void startConfigurationMode()
    {   
      #define CONFIG_TIMEOUT			60000L
                
	    BLYNK_LOG2(BLYNK_F("CfgIP="), Ethernet.localIP() );
	    
	    if (!server)
	      server = new EthernetWebServer;
	   
      //See https://stackoverflow.com/questions/39803135/c-unresolved-overloaded-function-type?rq=1
      
      if (server)
      {
        server->on("/", [this](){ handleRequest(); });
        server->begin();    
      }
                      
      // If there is no saved config Data, stay in config mode forever until having config Data.
      // or SSID, PW, Server,Token ="nothing"
      if (hadConfigData)
        configTimeout = millis() + CONFIG_TIMEOUT;                        
      else
        configTimeout = 0;
       
      configuration_mode = true;    
    }    

    bool connectEthernet(void)
    {
      // Check go see if static IP is required
      IPAddress staticIP;
      
      if (staticIP.fromString(BlynkEthernet_WM_config.static_IP))
      {
        // Use static IP      
        Ethernet.begin(SelectMacAddress(BlynkEthernet_WM_config.blynk_token, NULL), staticIP);
        BLYNK_LOG1(BLYNK_F("Static IP"));
        ethernetConnected = true;
      }
      else
      {       
        ethernetConnected = Ethernet.begin(SelectMacAddress(BlynkEthernet_WM_config.blynk_token, NULL));
        
        if (ethernetConnected)
          BLYNK_LOG1(BLYNK_F("Dynamic IP OK, connected"));
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
          BLYNK_LOG1(BLYNK_F("DHCP Failed"));
          
          if (Ethernet.linkStatus() == LinkOFF) 
          {
            BLYNK_LOG1(BLYNK_F("Bad Ecable."));
          }
      }
            
      return ethernetConnected;
    }
    
    byte* SelectMacAddress(const char* token, const byte mac[])
    {
        if (mac != NULL) {
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
        
        for (int i=0; i<len; i++) 
        {
            macAddress[mac_index] ^= token[i];

            if (++mac_index > 5) { mac_index = 1; }
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
