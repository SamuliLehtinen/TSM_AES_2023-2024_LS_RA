// Copyright 2023 Adrien Rey

/****************************************************************************
 * @file sensor_device.cpp
 * @author Adrien Rey <adrien.rey@hevs.ch>
 *
 * @brief SensorDevice implementation
 *
 * @date 2023-10.22
 * @version 1.0.0
 ***************************************************************************/

#include "sensor_device.hpp"
#include "constants.hpp"
#include "mbed_trace.h"

#if MBED_CONF_MBED_TRACE_ENABLE
#define TRACE_GROUP "SensorDevice"
#endif // MBED_CONF_MBED_TRACE_ENABLE

namespace bike_computer {

SensorDevice::SensorDevice() : _hdc1000(PD_13, PD_12, PC_6) {}

bool SensorDevice::init() {
  bool isDevice = _hdc1000.probe();
  if (!isDevice) {
    tr_error("HDC1000 not present !");
  }
  return isDevice;
}

float SensorDevice::readTemperature() { return _hdc1000.getTemperature(); }

float SensorDevice::readHumidity() { return _hdc1000.getHumidity(); }

} // namespace bike_computer
