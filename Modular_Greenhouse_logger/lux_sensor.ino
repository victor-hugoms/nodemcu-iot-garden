#ifndef LUX_PIN
    #define LUX_PIN = A0
#endif
bool luminosityMeter = false;

void initLuxSensor(){
    pinMode(LUX_PIN, INPUT);
    luminosityMeter = true;
}

float readLuminosity(){
    float r;
    int reading;

    reading = analogRead(LUX_PIN);
    //reading = constrain( map(reading, lowerBoundary, upperBoundary, 0, 100), 0, 100);
    r = (float) reading;
    return r;
}
