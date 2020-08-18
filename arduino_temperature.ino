#include <pt.h>

#include <OneWire.h>
#include <DallasTemperature.h>

// Define OneWire with pin-2(Data)
DallasTemperature sensor1(new OneWire(2));
DallasTemperature sensor2(new OneWire(4));

DeviceAddress deviceAddress1;
DeviceAddress deviceAddress2;

struct pt pt1;
struct pt pt2;

void sendTemperature(float value, int id){
    Serial.println((String)id +  "&" + (String)value);
}

int getTemp(struct pt *pt, DallasTemperature sensors, DeviceAddress deviceAddress, int id){
    PT_BEGIN(pt);

    sensors.requestTemperaturesByAddress(deviceAddress);
    PT_WAIT_UNTIL(pt, sensors.isConversionComplete());
    sendTemperature(sensors.getTempC(deviceAddress), id);

    PT_END(pt);
}

void setup() {
    Serial.begin(9600);

    sensor1.begin();
    sensor1.setWaitForConversion(false);
    sensor1.getAddress(deviceAddress1, (uint8_t)0);
    sensor2.begin();
    sensor2.setWaitForConversion(false);
    sensor2.getAddress(deviceAddress2, (uint8_t)0);
    delay(1000);
}

void loop() {
    getTemp(&pt1, sensor1, deviceAddress1, 0);
    delay(350);
    getTemp(&pt2, sensor2, deviceAddress2, 1);
}