#include <ArduinoJson.h>

void createTemperatureJson(char *payload)
{
    /**
     * sessionName, device, location, unit, elapsedTime, value    
    */
    DynamicJsonDocument root(MESSAGE_MAX_LEN);

    root["sessionName"] = "Test session";
    root["device"] = "Test device";
    root["location"] = "greenhouse";
    root["unit"] = "deg C";
    root["elapsedTime"] = 0;
    
    // NAN is not the valid json, change it to NULL
    if (std::isnan(temperature))
    {
        root["value"] = NULL;
    }
    else
    {
        root["value"] = temperature;
    }

    //serializeJson(root, Serial);
    serializeJson(root, payload, MESSAGE_MAX_LEN);
    return;
}

void createCredentialsJson(String user, String pwd, char *payload) {
    DynamicJsonDocument root(MESSAGE_MAX_LEN);

    root["email"] = user;
    root["password"] = pwd;

    serializeJson(root, payload, MESSAGE_MAX_LEN);
    return;
}

void createRenderJson(char *payload) {
    DynamicJsonDocument root(MESSAGE_MAX_LEN);
    JsonArray array = root.to<JsonArray>();

    JsonObject item1 = array.createNestedObject();
    item1["measure"] = "temperature";
    item1["label"] = "Temperature";
    item1["unit"] = "deg C";

    JsonObject item2 = array.createNestedObject();
    item2["measure"] = "humidity";
    item2["label"] = "Rel. humidity";
    item2["unit"] = "%";

    JsonObject item3 = array.createNestedObject();
    item3["measure"] = "luminosity";
    item3["label"] = "Luminosity";
    item3["unit"] = "abs";

    JsonObject item4 = array.createNestedObject();
    item4["measure"] = "soilHumidity1";
    item4["label"] = "Soil humidity rhizomes";
    item4["unit"] = "% wt";

    JsonObject item5 = array.createNestedObject();
    item5["measure"] = "soilHumidity2";
    item5["label"] = "Soil humidity tomatoes";
    item5["unit"] = "% wt";

    serializeJson(root, payload, MESSAGE_MAX_LEN);
    return;
}

void createMeasurementsJson(char *payload) {
    DynamicJsonDocument root(MESSAGE_MAX_LEN);
    JsonArray array = root.to<JsonArray>();

    JsonObject item1 = array.createNestedObject();
    item1["measure"] = "temperature";
    item1["value"] = temperature;

    JsonObject item2 = array.createNestedObject();
    item2["measure"] = "humidity";
    item2["value"] = humidity;

    JsonObject item3 = array.createNestedObject();
    item3["measure"] = "luminosity";
    item3["value"] = luminosity;

    JsonObject item4 = array.createNestedObject();
    item4["measure"] = "soilHumidity1";
    item4["value"] = soilHumidity1;

    JsonObject item5 = array.createNestedObject();
    item5["measure"] = "soilHumidity2";
    item5["value"] = soilHumidity2;

    if(Serial) {
        Serial.print("\nJSON created: ");
        serializeJson(root, Serial);
        Serial.println("");
    }

    serializeJson(root, payload, MESSAGE_MAX_LEN);
    return;
}