#include "my_candidate_applications.hpp"
#include "FlashIAPBlockDevice.h"

#include "mbed_trace.h"
#if MBED_CONF_MBED_TRACE_ENABLE
#define TRACE_GROUP "MyCandidateApplications"
#endif  // MBED_CONF_MBED_TRACE_ENABLE

#include "uc_error_code.hpp"

namespace update_client {

uint32_t MyCandidateApplications::getSlotForCandidate() {
    mbed::bd_addr_t _storageAddress = MBED_CONF_UPDATE_CLIENT_STORAGE_ADDRESS;

    FlashIAPBlockDevice flashIAPBlockDevice(MBED_ROM_START, MBED_ROM_SIZE);
    int ret = flashIAPBlockDevice.init();

    if(ret == 0){
        for (int i = 0; i < getNbrOfSlots(); i++) {
            mbed::bd_addr_t headerAddress = HEADER_ADDR - MBED_ROM_START;
            mbed::bd_addr_t applicationAddress = _storageAddress + i * getSlotSize();
            update_client::BlockDeviceApplication activeApplication(flashIAPBlockDevice, headerAddress, applicationAddress);
            update_client::UCErrorCode rc = activeApplication.checkApplication();

            if (update_client::UCErrorCode::UC_ERR_NONE != rc) {
                return _storageAddress + i * getSlotSize();
            }
        }
    }
    return -1;
}
}  // namespace update_client
