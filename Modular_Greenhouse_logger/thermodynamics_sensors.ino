#include <Wire.h> // Library for I2C communication
#include "config.h"
bool temperatureMeter, humidityMeter, pressureMeter, altitudeMeter;

#if USE_DHT_SENSOR == true

#include <DHT.h>
#define DHT_TYPE DHT22
static DHT termodynamicSensor(DHT_PIN, DHT_TYPE);

void initThermodynamicSensor()
{
    termodynamicSensor.begin();

    temperatureMeter = true;
    humidityMeter = true;
    pressureMeter = false;
    altitudeMeter = false;
}

float readTemperature()
{
    return termodynamicSensor.readTemperature();
}

float readHumidity()
{
    return termodynamicSensor.readHumidity();
}

float readPressure()
{
    return 0.0;
}

float readAltitude()
{
  return 0.0;
}

#else

#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

Adafruit_BME280 termodynamicSensor;

void initThermodynamicSensor()
{
    if (!termodynamicSensor.begin(0x76)) {
        Serial.println("Could not find a valid sensor, check wiring, address, sensor ID!");
        while(1){
          //blinkAlert();
        }
    }

  temperatureMeter = true;
  humidityMeter = true;
  pressureMeter = true;
  altitudeMeter = true;

  termodynamicSensor.setSampling(Adafruit_BME280::MODE_NORMAL,
                    Adafruit_BME280::SAMPLING_X2,  // temperature
                    Adafruit_BME280::SAMPLING_X1, // pressure
                    Adafruit_BME280::SAMPLING_X2,  // humidity
                    Adafruit_BME280::FILTER_X16,
                    Adafruit_BME280::STANDBY_MS_0_5 );
}

float readTemperature()
{
    return termodynamicSensor.readTemperature();
}

float readHumidity()
{
    return termodynamicSensor.readHumidity();
}

float readPressure()
{
    return termodynamicSensor.readPressure()/ 100.0F;
}

#endif

void updateThermodynamicReadings(){
  if(temperatureMeter) temperature = readTemperature();
  if(pressureMeter) pressure = readPressure();
  if(humidityMeter) humidity = readHumidity();
}
//#include <Adafruit_BME280.h>
// #define SEALEVELPRESSURE_HPA (1013.25) //for BMx sensors

//Adafruit_BMP280 termodynamicSensor;
