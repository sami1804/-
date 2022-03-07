//https://www.youtube.com/watch?v=ut9D0N5jDJE

#include <SoftwareSerial.h>
#include "ultra_sonic.h"

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_NeoPixel.h>

SoftwareSerial bt(2, 3);

auto ultra_sonic_pin = 4; 
ultra_sonic us(ultra_sonic_pin);

auto strip = Adafruit_NeoPixel(24, A1, NEO_GRB + NEO_KHZ800);

auto mpu = Adafruit_MPU6050();

void set_pixels_color(unsigned int start, unsigned int finish, int r, int g, int b) {
  for (auto i = start; i < finish; ++i) {
    strip.setPixelColor(i, r, g, b);
  }
}

void handle_distance_colors(word distance) {
  if (distance < 100) {
    set_pixels_color(0, 24, 0, 0, 0);
  } else {
    if (distance >= 100) {
      set_pixels_color(0, 8, 255, 0, 0);
    }
    if (distance >= 200) {
      set_pixels_color(8, 16, 0, 255, 0);
    }
    if (distance >= 300) {
      set_pixels_color(16, 24, 0, 0, 255);
    }
    if (distance >= 300) {
      set_pixels_color(16, 24, 0, 0, 255);
    }
    if (distance >= 400) {
      static bool on = true;
      if (on)
        set_pixels_color(0, 24, 255, 255, 255);
      else
        set_pixels_color(0, 24, 0, 0, 0);
      on = !on;
    }
  }
}

void setup() {
  Serial.begin(9600);
  bt.begin(9600);

  strip.begin();
  strip.clear();

  mpu.begin();
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
}

void loop() {
  auto distance = us.get_distance();
  auto distance_string = "Distance = " + String(distance) + "\n";
  // bt.print(distance_string);  

  static bool start = false;
  static auto i = 0u;

  if (bt.available()) {
    bt.read(); // clear buffer;
    start = !start;
  }

  if (start) {
    strip.setPixelColor(i, strip.Color(0, 0, 0));
    if (i == 23) {
      strip.setPixelColor(i = 0, strip.Color(255, 255, 255));
  
      sensors_event_t a, g, temp;
      mpu.getEvent(&a, &g, &temp);
    
      auto temperature = temp.temperature;
      auto temperature_string = "Temperature = " + String(temperature) + " degC\n";
      bt.print(temperature_string);
    }
    else
      strip.setPixelColor(++i, strip.Color(255, 255, 255));
  }
  
  strip.show();

  
  
  delay(500);
}
