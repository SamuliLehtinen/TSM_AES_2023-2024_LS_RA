/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "mbed_trace.h"
#include "multi_tasking/bike_system.hpp"
#include "FlashIAPBlockDevice.h"
#include "update-client/block_device_application.hpp"
#include "update-client/candidate_applications.hpp"
#include "update-client/usb_serial_uc.hpp"
#include "update-client/uc_error_code.hpp"

#if defined(MBED_CONF_MBED_TRACE_ENABLE)
#define TRACE_GROUP "MAIN"
#endif // MBED_CONF_MBED_TRACE_ENAB

#if !MBED_TEST_MODE

int main() {
#if defined(MBED_CONF_MBED_TRACE_ENABLE)
  mbed_trace_init();
#endif
    FlashIAPBlockDevice flashIAPBlockDevice(MBED_ROM_START, MBED_ROM_SIZE);
    update_client::USBSerialUC usbSerialUpdateClient(flashIAPBlockDevice);
    update_client::UCErrorCode rc = usbSerialUpdateClient.start();
    if (rc != update_client::UCErrorCode::UC_ERR_NONE) {
        tr_error("Cannot initialize update client: %d", rc);
    } else {
        tr_info("Update client started");
    }
  multi_tasking::BikeSystem bikeSystem;
  bikeSystem.start();
}
#endif
