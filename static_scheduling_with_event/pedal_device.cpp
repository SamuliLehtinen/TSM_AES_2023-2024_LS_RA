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
#endif  // MBED_CONF_MBED_TRACE_ENABLE

namespace static_scheduling_with_event {

// definition of task execution time
static constexpr std::chrono::microseconds kTaskRunTime = 200000us;

PedalDevice::PedalDevice() {
    disco::Joystick::getInstance().setLeftCallback(callback(this, &PedalDevice::onLeft));
    disco::Joystick::getInstance().setRightCallback(callback(this, &PedalDevice::onRight));
}


std::chrono::milliseconds PedalDevice::getCurrentRotationTime() {
    uint32_t currentStep = core_util_atomic_load_u32(&_currentStep);
    return bike_computer::kMinPedalRotationTime +
           currentStep * bike_computer::kDeltaPedalRotationTime;
}

void PedalDevice::increaseRotationSpeed() {
    uint32_t currentStep = core_util_atomic_load_u32(&_currentStep);
    if (currentStep > 0) {
        core_util_atomic_decr_u32(&_currentStep, 1);
    }
}

void PedalDevice::decreaseRotationSpeed() {
    uint32_t currentStep = core_util_atomic_load_u32(&_currentStep);
    if (currentStep < kNbrOfSteps) {
        core_util_atomic_incr_u32(&_currentStep, 1);
    }
}

void PedalDevice::onLeft() { decreaseRotationSpeed(); }

void PedalDevice::onRight() { increaseRotationSpeed(); }

}  // namespace static_scheduling
