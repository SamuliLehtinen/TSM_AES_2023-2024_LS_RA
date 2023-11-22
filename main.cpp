/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

/*#include "mbed.h"
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
  bikeSystem.start();
}
#endif*/

#include "mbed.h"
#include "mbed_trace.h"
#include "memory_logger.hpp"
#include "wait_on_button.hpp"
#if MBED_CONF_MBED_TRACE_ENABLE
#undef TRACE_GROUP
#define TRACE_GROUP "main"
#endif // MBED_CONF_MBED_TRACE_ENABLE

int main() {
  // use trace library for console output
  mbed_trace_init();

  tr_debug("EventFlags program started\n");

  // log thread statistics
  advembsof::MemoryLogger memoryLogger;
  memoryLogger.getAndPrintThreadStatistics();

  // create the WaitOnButton instance and start it
  multi_tasking::WaitOnButton waitOnButton("ButtonThread");
  waitOnButton.start();

  // wait that the WaitOnButton thread started
  waitOnButton.wait_started();

  // log thread statistics
  memoryLogger.getAndPrintThreadStatistics();

  // wait for the thread to exit (will not because of infinite loop)
  waitOnButton.wait_exit();
  // or do busy waiting
  // while (true) {
  //}

  return 0;
}
