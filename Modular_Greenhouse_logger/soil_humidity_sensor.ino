void initSoilHumiditySensor(int pin){
    return;
}

float readSoilHumidity(int sensorId) {
  switch(sensorId) {
    case 1:
      return (float) random(0,50);
    case 2:
      return (float) random(50,100);
    default:
      return (float) -1.0;
  }
}