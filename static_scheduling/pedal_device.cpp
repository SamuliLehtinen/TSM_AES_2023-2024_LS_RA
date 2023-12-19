// Copyright 2023 Adrien Rey

/****************************************************************************
 * @file gear_device.cpp
 * @author Adrien Rey <adrien.rey@hevs.ch>
 *
 * @brief Pedal Device implementation (static scheduling)
 *
 * @date 2023-08-20
 * @version 1.0.0
 ***************************************************************************/

#include "pedal_device.hpp"

// from disco_h747i/wrappers
#include <chrono>

#include "joystick.hpp"
#include "mbed_trace.h"

#if MBED_CONF_MBED_TRACE_ENABLE
#define TRACE_GROUP "PedalDevice"
#endif // MBED_CONF_MBED_TRACE_ENABLE

namespace static_scheduling {

// definition of task execution time
static constexpr std::chrono::microseconds kTaskRunTime = 200000us;

PedalDevice::PedalDevice(Timer &timer) : _timer(timer) {}

std::chrono::milliseconds PedalDevice::getCurrentRotationTime() {
  std::chrono::microseconds initialTime = _timer.elapsed_time();
  std::chrono::microseconds elapsedTime = std::chrono::microseconds::zero();
  bool hasChanged = false;
  while (elapsedTime < kTaskRunTime) {
    if (!hasChanged) {
      disco::Joystick::State joystickState =
          disco::Joystick::getInstance().getState();

      switch (joystickState) {
      case disco::Joystick::State::LeftPressed:
        if (_pedalRotationTime < bike_computer::kMaxPedalRotationTime) {
          decreaseRotationSpeed();
          hasChanged = true;
        }
        break;

      case disco::Joystick::State::RightPressed:
        if (_pedalRotationTime > bike_computer::kMinPedalRotationTime) {
          increaseRotationSpeed();
          hasChanged = true;
        }
        break;

      default:
        break;
      }
    }
    elapsedTime = _timer.elapsed_time() - initialTime;
  }

  return _pedalRotationTime;
}

void PedalDevice::increaseRotationSpeed() {
  _pedalRotationTime -= bike_computer::kDeltaPedalRotationTime;
}

void PedalDevice::decreaseRotationSpeed() {
  _pedalRotationTime += bike_computer::kDeltaPedalRotationTime;
}

} // namespace static_scheduling
