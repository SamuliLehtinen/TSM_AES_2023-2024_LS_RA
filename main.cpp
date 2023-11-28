/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "mbed_trace.h"
#include "multi_tasking/bike_system.hpp"

#if defined(MBED_CONF_MBED_TRACE_ENABLE)
#define TRACE_GROUP "MAIN"
#endif // MBED_CONF_MBED_TRACE_ENAB

#if !MBED_TEST_MODE

int main() {
#if defined(MBED_CONF_MBED_TRACE_ENABLE)
  mbed_trace_init();
#endif
  multi_tasking::BikeSystem bikeSystem;
  bikeSystem.start();
}
#endif
