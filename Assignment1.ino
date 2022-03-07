#include <SoftwareSerial.h>
#include "ultra_sonic.h"

SoftwareSerial bt(2, 3);

auto ultra_sonic_pin = 4; 
ultra_sonic us(ultra_sonic_pin);

void setup() {
  Serial.begin(9600);
  bt.begin(9600);
}

void loop() {
  auto distance = us.get_distance();
  auto distance_string = "Distance = " + String(distance) + "\n";
  bt.print(distance_string);

  delay(50);
}
