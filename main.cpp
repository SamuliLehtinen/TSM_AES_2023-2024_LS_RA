/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "mbed_trace.h"
#include "static_scheduling_with_event/bike_system.hpp"

#if defined(MBED_CONF_MBED_TRACE_ENABLE)
#define TRACE_GROUP "MAIN"
#endif // MBED_CONF_MBED_TRACE_ENAB

#if !MBED_TEST_MODE
int main() {
#if defined(MBED_CONF_MBED_TRACE_ENABLE)
  mbed_trace_init();
#endif
  static_scheduling_with_event::BikeSystem bikeSystem;
  bikeSystem.startWithEventQueue();
}
#endif
