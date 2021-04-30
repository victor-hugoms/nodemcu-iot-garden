#pragma once
#ifndef _HEADER_FILE_H_
  #define _HEADER_FILE_H_
  
  #define USE_DHT_SENSOR true
  
  // Pin layout configuration
  #define ALERT_PIN 5 //D1
  #define DHT_PIN 4 //D2
  #define LUX_PIN A0 // In ESP8266 A0 is the only analog pin
  
  #define MESSAGE_MAX_LEN 256
  
  //Wi-Fi settings
  #define WIFI_SSID "YOUR_NETWORK_SSID_HERE"
  #define WIFI_PASSWORD "YOUR_NETWORK_PASSWORD_HERE"

  //Username
  #define PORTAL_USERNAME "YOUR_USER_NAME"
  
  //Password
  #define PORTAL_PASSWORD "YOUR_PASSWORD"

  #define ENDPOINT_LOGIN "LOGIN_ENDPOINT_HERE"
  #define ENDPOINT_POST_MEASUREMENTS "MEASUREMENTS_ENDPOINT_HERE"
#endif
