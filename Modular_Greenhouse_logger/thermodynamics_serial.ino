void initSerial(unsigned int baudRate){
    while(!Serial){
        Serial.begin(baudRate);
    }
    delay(100);
    return;
}

void printThermodynamicState(){
  Serial.print("Temperature: ");
  Serial.print(temperature,0);
  Serial.println("");

  Serial.print("Humidity: ");
  Serial.print(humidity,0);
  Serial.println("");
  
  Serial.print("Luminosity: ");
  Serial.print(luminosity,0);
  Serial.println("");

  return;
}

void printPlotThermodynamicState(){
    return;
}