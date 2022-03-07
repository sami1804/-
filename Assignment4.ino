//https://www.youtube.com/watch?v=FrlKfZE6W00

#include <SoftwareSerial.h>
#include <Temperature_LM75_Derived.h>
#include "UltraSonic.hpp"

// Sensor ports
const uint8_t kBluetoothPorts[] = {2, 3};
const uint8_t kUltraSonicPin = 4;

// Sensor objects
SoftwareSerial bt(kBluetoothPorts[0], kBluetoothPorts[1]);
Generic_LM75 lm75;
UltraSonic us(kUltraSonicPin);

void setup() {
  Serial.begin(9600);
  bt.begin(9600);
  
  Wire.begin();
}

void loop() {  
  if (bt.available()) {
    auto input = bt.readString().toInt();
    switch (input) {
      case 10: {
        // Get temperature
        auto temperature = lm75.readTemperatureC();
        auto temperatureString = "Temparature = " + String(lm75.readTemperatureC()) + " C\n";
        
        bt.print(temperatureString);
        break;
      }
      case 20: {
        // Get distance
        auto distance = us.getDistance();
        auto distanceString = "Distance = " + String(distance) + " cm\n";

        bt.print(distanceString);
        break;
      }
    }
  }

  delay(300);
}
