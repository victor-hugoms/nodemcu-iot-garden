#include <ESP8266HTTPClient.h>
#include "config.h"

String portalUsername = PORTAL_USERNAME;
String portalPassword = PORTAL_PASSWORD;
//Endpoint to login
String endpointLogin = ENDPOINT_LOGIN;

//Endpoint to measurement
String endpointMeasurement = ENDPOINT_POST_MEASUREMENTS;

int postMeasurement(float value){
    HTTPClient http;
    char messagePayload[MESSAGE_MAX_LEN];

    // Your Domain name with URL path or IP address with path
    http.begin(endpointMeasurement);
    // Content-type header of HTTP request
    http.addHeader("Content-Type", "application/json");
    http.addHeader("x-auth-token", token);

    // Create JSON with ArduinoJson
    createTemperatureJson(messagePayload);

    int httpResponseCode = http.POST(messagePayload);

    http.end();

    return httpResponseCode;
}

bool login(String &token){
    HTTPClient http;
    char jsonBody[MESSAGE_MAX_LEN];

    // Your Domain name with URL path or IP address with path
    http.begin(endpointLogin);
    // Content-type header of HTTP request
    http.addHeader("Content-Type", "application/json");

    // Create JSON with ArduinoJson
    createCredentialsJson(portalUsername, portalPassword, jsonBody);

    int httpResponseCode = http.POST(jsonBody);
    token = http.getString();

    http.end();
    
    if( httpResponseCode == 200 ) {
        return true;
    }
    else {
        return false;
    }
}
