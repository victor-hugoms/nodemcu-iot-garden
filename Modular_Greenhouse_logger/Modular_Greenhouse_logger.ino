/*
  BASED ON CODE FROM:
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/

// Import required libraries
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <FS.h>

#include "config.h"

float temperature, pressure, humidity, luminosity, altitude;
float soilHumidity1 = 1.23, soilHumidity2 = 0.12;
char renderJson[MESSAGE_MAX_LEN];
char jsonMeasurements[MESSAGE_MAX_LEN];

// Set LED GPIO
const int ledPin = 5; //D1

// Store last HTTP return code
int returnCode;

// Timing variables
unsigned long currentTime, lastTransmissionTime = 0L, transmissionIntervalTime = 60000L;

// Hugup Server variables
bool isAuthenticated = false;
//Token
String token = "NO_VAL";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

String getTemperature() {
  //float temperature = readTemperature();

  //Serial.println(temperature);
  return String(temperature);
}

String getHumidity() {
  //float humidity = readHumidity();
  //Serial.println(humidity);
  return String(humidity);
}

String getPressure() {
  //float pressure = readPressure()/ 100.0F;
  //Serial.println(pressure);
  return String(pressure);
}

String getLuminosity() {
  //float luminosity = readLuminosity();
  //Serial.println(luminosity);
  return String(luminosity);
}

String getSoilHumidity(int sensorId) {
  return String(readSoilHumidity(sensorId),2);
}

String getMeasurements() {
  createMeasurementsJson(jsonMeasurements);
  return String(jsonMeasurements);
}

// Replaces placeholder with sensor value
String processor(const String& var) {
  if (var == "TEMPERATURE") {
    return getTemperature();
  }
  else if (var == "HUMIDITY") {
    return getHumidity();
  }
  else if (var == "PRESSURE") {
    return getPressure();
  }
  else if (var == "LUMINOSITY") {
    return getLuminosity();
  }
  else if (var == "SOILHUM1") {
    return getSoilHumidity(1);
  }
  else if (var == "SOILHUM2") {
    return getSoilHumidity(2);
  }
  else {
    return "UNKNOWN";
  }
}

void setup() {
  // Serial port for debugging purposes
  initSerial(9600);

  // Prepare render JSON
  createRenderJson(renderJson);

  pinMode(ledPin, OUTPUT);
  alertWifiDisconnected();

  // Initialize the sensor
  initThermodynamicSensor();
  initLuxSensor();
  initSoilHumiditySensor(1);
  initSoilHumiditySensor(2);

  // Initialize SPIFFS
  if (!SPIFFS.begin()) {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  // Connect to Wi-Fi
  initWifi();

  // Print ESP8266 Local IP Address
  Serial.println(WiFi.localIP());

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    //Send index.htm with template processor function
    //request->send(SPIFFS, "/index.html", String(), false, processor);
    //Send index.htm with default content type
    request->send(SPIFFS, "/index.html");
  });

  // Route to load style.css file
  server.on("/styles.css", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/styles.css", "text/css");
  });

  /* server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/plain", getTemperature().c_str());
  });

  server.on("/humidity", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/plain", getHumidity().c_str());
  });

  server.on("/pressure", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/plain", getPressure().c_str());
  });

  server.on("/luminosity", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/plain", getLuminosity().c_str());
  }); */

  server.on("/render", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "application/json; charset=utf-8", renderJson);
  });

  server.on("/updateValues", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "application/json; charset=utf-8", getMeasurements().c_str());
  });

  // Start server
  server.begin();
  Serial.println("Web server initialized!");

  // Start client to login
  Serial.println("Logging in...");
  isAuthenticated = login(token);
  Serial.print("Return message from hugup server: ");
  Serial.println(token);
}

void loop() {
  currentTime = millis();
  updateThermodynamicReadings();
  luminosity = readLuminosity();
  soilHumidity1 = readSoilHumidity(1);
  soilHumidity2 = readSoilHumidity(2);

  //printThermodynamicState();
  Serial.print(".");

  // POST on hugup server every transmissionIntervalTime
  if (currentTime - lastTransmissionTime >= transmissionIntervalTime) {
    Serial.println("");
    if (isAuthenticated) {
      Serial.print("POST request using token: ");
      Serial.println(token);
      returnCode = postMeasurement(temperature);
      Serial.print("Returned code: ");
      Serial.println(returnCode, DEC);

      if ( returnCode == 200 || returnCode == 201 ) {
        lastTransmissionTime = currentTime;
      }
      else if (returnCode == 401 || returnCode == 403) {
        isAuthenticated = false;
      }
    }
    else {
      Serial.print("Returned code: ");
      isAuthenticated = login(token);
    }
  }

  delay(1000);
}
