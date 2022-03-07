//https://www.youtube.com/watch?v=t5yUIDkWM0E

#include <SoftwareSerial.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_MPU6050.h>
#include "UltraSonic.hpp"
#include<Servo.h>
Servo Myservo1, Myservo2;
int pos;

// Sensor ports
const uint8_t kBluetoothPorts[] = { 2, 3 };
const uint8_t kUltraSonicPin = 4;
const uint8_t kNeoPixelPin = A1;

// Other sensor data
const uint16_t kNeoPixelLedsCount = 24;

// Sensor classes
SoftwareSerial bt(kBluetoothPorts[0], kBluetoothPorts[1]);
UltraSonic us(kUltraSonicPin);
Adafruit_NeoPixel np(kNeoPixelLedsCount, kNeoPixelPin, NEO_GRB + NEO_KHZ800);
Adafruit_MPU6050 mpu;

/**
 * @brief Function changes NeoPixel ring color according to the distance from UltraSonic sensor.
 * @param distance Distance from UltraSonic sensor.
 */
void handleDistanceColors(const word distance);

// Arduino EntryPoint
void setup() {
  Serial.begin(9600);
  bt.begin(9600);

  np.begin();
  np.clear();

  mpu.begin();
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  Myservo1.attach(5);
  Myservo2.attach(7);
  Myservo1.write(0);
  Myservo2.write(0);
  delay(2000);
}

// Arduino MainLoop
void loop() {
  auto distance = us.getDistance();
  auto distance_string = "Distance = " + String(distance) + "\n";
  Serial.print(distance_string);
  //Serial.print(distance_string);
  if (bt.available()) {
    auto input = bt.readString();
    switch (input.toInt()) {
      case 10: {
        for(pos=0;pos<=90;pos++){
          Myservo1.write(pos);
          delay(15);
        }
        delay(1000);
        for(pos=90;pos>=0;pos--){
          Myservo1.write(pos);
          delay(15);
        }
        break;
      }
      case 20: {
        for(pos=0;pos<=90;pos++){
        Myservo2.write(pos);
        delay(15);
        }
        delay(1000);
        for(pos=90;pos>=0;pos--){
          Myservo2.write(pos);
          delay(15);
        }
        break;
      }
    }
  }
  else{
    if(distance >= 200 && distance < 300){
      for(pos=0;pos<=90;pos++){
        Myservo1.write(pos);
        delay(15);
      }
      delay(1000);
      for(pos=90;pos>=0;pos--){
        Myservo1.write(pos);
        delay(15);
      }
     }
     if(distance >= 300){
        for(pos=0;pos<=90;pos++){
        Myservo2.write(pos);
        delay(15);
      }
      delay(1000);
      for(pos=90;pos>=0;pos--){
        Myservo2.write(pos);
        delay(15);
      }
  }
 }
}
