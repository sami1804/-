#ifndef ULTRASONIC_HPP
#define ULTRASONIC_HPP

#include <Arduino.h>

class UltraSonic {
public:
  /**
   * @brief Constructor, sets the US pin.
   */    
  UltraSonic(const uint8_t pin) : pin_(pin) {}

  /**
   * @brief Calculates the distance from the US sensor.
   * @return The distance of object from the US sensor.
   */
  inline word getDistance() {
    return pulseIn(pin_, HIGH) / kTimePerCm;
  }

private:
  static const word kTimePerCm = 58; /// Time that sound need to complete 1 cm.

  uint8_t pin_; /// Sensor's pin.
};

#endif // ULTRASONIC_HPP
