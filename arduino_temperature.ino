#include <pt.h>

#include <OneWire.h>
#include <DallasTemperature.h>

// Define OneWire with pin-2(Data)
DallasTemperature sensor(new OneWire(2));

DeviceAddress deviceAddress1;

struct pt pt1;

void sendTemperature(float value){
    Serial.println(value);
}

int getTemp(struct pt *pt, DallasTemperature sensors, DeviceAddress deviceAddress){
    PT_BEGIN(pt);

    sensors.requestTemperaturesByAddress(deviceAddress);
    PT_WAIT_UNTIL(pt, sensors.isConversionComplete());
    sendTemperature(sensors.getTempC(deviceAddress));

    PT_END(pt);
}

void setup() {
    Serial.begin(9600);

    sensor.begin();
    sensor.setWaitForConversion(false);
    sensor.getAddress(deviceAddress1, (uint8_t)0);
    delay(1000);
}

void loop() {
    getTemp(&pt1, sensor, deviceAddress1);
}