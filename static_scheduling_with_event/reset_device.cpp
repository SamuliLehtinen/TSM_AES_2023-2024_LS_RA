#include "reset_device.hpp"

#if defined(TARGET_DISCO_H747I)
#define PUSH_BUTTON BUTTON1
static constexpr uint8_t kPolarityPressed = 1;
#endif

namespace static_scheduling_with_event{

ResetDevice::ResetDevice(Callback<void()> cb) : _resetButton(PUSH_BUTTON) {
    // register a callback for computing the response time
    _resetButton.fall(cb);
}


}