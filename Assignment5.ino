//https://www.youtube.com/watch?v=tUcgiwxNgc0

#include <SoftwareSerial.h>
#include <MPU6050_Z.h>
#include <Adafruit_NeoPixel.h>

// Sensor ports
const uint8_t kBluetoothPorts[] = {2, 3};
const uint8_t kNeoPixelPin = A1;

// Other sensor data
const uint16_t kNeoPixelLedsCount = 24;

// Sensor object
SoftwareSerial bt(kBluetoothPorts[0], kBluetoothPorts[1]);
Adafruit_NeoPixel np(kNeoPixelLedsCount, kNeoPixelPin, NEO_GRB + NEO_KHZ800);
MPU6050 mpu(Wire);

namespace MPU {
  /**
   * @brief Calculates led number by angle from mput
   */
  static int CalculateLedNumberByAngle();
}
namespace NeoPixel {
  /**
   * @brief Enables colors according to led number
   * @param ledNumber Number of leds
   */
  static void HandleLedColors(const int ledNumber);
}

void setup() {
  Serial.begin(9600);
  bt.begin(9600);
  
  Wire.begin();

  mpu.begin();
  mpu.calcGyroOffsets(true);
  
  np.begin();
  np.clear();
}

void loop() {
  auto ledNumber = MPU::CalculateLedNumberByAngle();
  NeoPixel::HandleLedColors(ledNumber);
}

int MPU::CalculateLedNumberByAngle() {
  mpu.update();
  auto angle = mpu.getAngleZ();
  return -(angle / 30);
}

void NeoPixel::HandleLedColors(const int ledNumber) {
  if (ledNumber > 0) {
    np.fill(Adafruit_NeoPixel::Color(255, 0, 255), 0, ledNumber);
    if (ledNumber < kNeoPixelLedsCount) {
      np.fill(Adafruit_NeoPixel::Color(0, 0, 0), ledNumber, kNeoPixelLedsCount - 1);
    }
  } else if (ledNumber < 0) {
    auto trueLedNumber = -ledNumber;
    np.fill(Adafruit_NeoPixel::Color(255, 255, 0), kNeoPixelLedsCount - 1 - trueLedNumber, kNeoPixelLedsCount - 1);
    if (trueLedNumber < kNeoPixelLedsCount) {
      np.fill(Adafruit_NeoPixel::Color(0, 0, 0), 0, kNeoPixelLedsCount - 1 - trueLedNumber);
    }
  } else {
    np.clear();
  }
  np.show();
}
