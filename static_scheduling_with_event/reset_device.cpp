// Copyright 2023 Adrien Rey

/****************************************************************************
 * @file reset_device.cpp
 * @author Adrien Rey <adrien.rey@hevs.ch>
 *
 * @brief Reset Device implementation (static scheduling)
 *
 * @date 2023-08-20
 * @version 1.0.0
 ***************************************************************************/
#include "reset_device.hpp"

#if defined(TARGET_DISCO_H747I)
#define PUSH_BUTTON BUTTON1
static constexpr uint8_t kPolarityPressed = 1;
#endif

namespace static_scheduling_with_event {

ResetDevice::ResetDevice(Callback<void()> cb) : _resetButton(PUSH_BUTTON) {
  // register a callback for computing the response time
  _resetButton.fall(cb);
}

} // namespace static_scheduling_with_event
