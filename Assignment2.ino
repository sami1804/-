#include <SoftwareSerial.h>
#include "ultra_sonic.h"
#include <Adafruit_NeoPixel.h>
//video:https://www.youtube.com/watch?v=8tXYO6tbtto
SoftwareSerial bt(2, 3);

auto ultra_sonic_pin = 4; 
ultra_sonic us(ultra_sonic_pin);

auto strip = Adafruit_NeoPixel(24, A1, NEO_GRB + NEO_KHZ800);

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
  strip.show();
}

void setup() {
  Serial.begin(9600);
  bt.begin(9600);

  strip.begin();
  strip.clear();
  
}

void loop() {
  auto distance = us.get_distance();
  auto distance_string = "Distance = " + String(distance) + "\n";
  bt.print(distance_string);  

  handle_distance_colors(distance);

  delay(50);
}
