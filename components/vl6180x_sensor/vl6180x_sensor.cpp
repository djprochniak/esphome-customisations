#include "vl6180x_sensor.h"
#include "esphome/core/log.h"

namespace esphome {
namespace vl6180x_sensor {

static const char *TAG = "vl6180x";

void VL6180XSensor::setup() {
  ESP_LOGCONFIG(TAG, "Setting up VL6180X sensor...");
  if (!this->vl_.begin()) {
    ESP_LOGE(TAG, "VL6180X not found at I2C address 0x29");
    this->mark_failed();
  }
}

void VL6180XSensor::update() {
  if (this->is_failed()) return;
  uint8_t range = this->vl_.readRange();
  ESP_LOGD(TAG, "Got distance: %d mm", range);
  this->publish_state(range);
}

void VL6180XSensor::dump_config() {
  ESP_LOGCONFIG(TAG, "VL6180X Sensor:");
  LOG_SENSOR("  ", "Distance", this);
}

}  // namespace vl6180x_sensor
}  // namespace esphome
