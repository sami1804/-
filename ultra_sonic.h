#ifndef ULTRA_SONIC_H
#define ULTRA_SONIC_H

#include <Arduino.h>

class ultra_sonic {
  static const auto time_per_cm = 58u; /// Time that sound need to complete 1 cm.

  int pin_; /// Sensor's pin.

public:
  /**
   * @brief Constructor, sets the US pin.
   */    
  ultra_sonic(const int pin) : pin_(pin) {}

  /**
   * @brief Calculates the distance from the US sensor.
   * @return The distance of object from the US sensor.
   */
  inline word get_distance() {
    return pulseIn(pin_, HIGH) / time_per_cm;
  }
};

#endif // ULTRA_SONIC_H
