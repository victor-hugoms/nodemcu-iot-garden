// Load Wi-Fi library
#include <ESP8266WiFi.h>
#include "config.h"

// Replace with your network credentials
const char* ssid     = WIFI_SSID;
const char* password = WIFI_PASSWORD;

void initWifi()
{
    // Attempt to connect to Wifi network:
    if(Serial){
      Serial.printf("Attempting to connect to SSID: %s.\r\n", ssid);
    }

    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        // Get Mac Address and show it.
        // WiFi.macAddress(mac) save the mac address into a six length array, but the endian may be different. The huzzah board should
        // start from mac[0] to mac[5], but some other kinds of board run in the oppsite direction.
        uint8_t mac[6];
        WiFi.macAddress(mac);
        Serial.printf("You device with MAC address %02x:%02x:%02x:%02x:%02x:%02x connects to %s failed! Waiting 5 seconds to retry.\r\n",
                mac[0], mac[1], mac[2], mac[3], mac[4], mac[5], ssid);
        WiFi.begin(ssid, password);
        delay(5000); //try to connect again in 5 seconds
    }
    Serial.printf("Connected to wifi %s.\r\n", ssid);
    alertWifiConnected();
}

/**
 * @brief Reconnect stablished Wi-Fi connection.
 * Try every 5 second to reconnect.
 * Current implementation has no timeout or max. attempts
 */
void reconnectWifi()
{
    alertWifiDisconnected();

    while(WiFi.status() != WL_CONNECTED){
      Serial.printf("Attempting to reconnect to SSID: %s\n", ssid);
      WiFi.reconnect();
      int connectionStatus = WiFi.waitForConnectResult();
      Serial.printf("Connection status: %s\n", getWiFiStatus().c_str()); 

      delay(5000);
    }

    alertWifiConnected();
}


/**
 * Get the status of the Wi-Fi connection
 * 
 * @return String
 */
String getWiFiStatus(){
  switch(WiFi.status())
  {
    case 0:
      // WL_IDLE_STATUS
      return "Idle"; 
      break;  
    case 1:
      // WL_NO_SSID_AVAILABLE
      return "SSID Not Available"; 
      break;  
    case 2:
      // WL_SCAN_COMPLETED
      return "Scan Completed"; 
      break;  
    case 3:
      // WL_CONNECTED
      return "Connected"; 
      break;  
    case 4:
      // WL_CONNECT_FAILED
      return "Connection Failed"; 
      break;  
    case 5:
      // WL_CONNECTION_LOST
      return "Connection Lost"; 
      break;  
    case 6:
      // WL_DISCONNECTED
      return "Disconnected"; 
      break;     
    case 255:
      // WL_NO_SHIELD
      return "No Sheild"; 
      break;           
    default:
      return "Unknown";
    break;
  }
}


void alertWifiDisconnected(){
  digitalWrite(ALERT_PIN, LOW);
  return;
  //digitalWrite(LED_BUILTIN, LOW);  //Builtin LEDs work in invertd mode
}

void alertWifiConnected(){
  digitalWrite(ALERT_PIN, HIGH);
  return;
  //digitalWrite(LED_BUILTIN, HIGH); //Builtin LEDs work in invertd mode
}
