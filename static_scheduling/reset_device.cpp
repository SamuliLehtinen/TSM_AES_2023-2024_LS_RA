// includes come here
#include "reset_device.hpp"
<<<<<<< Updated upstream

=======
>>>>>>> Stashed changes

#if defined(TARGET_DISCO_H747I)
#define PUSH_BUTTON BUTTON1
static constexpr uint8_t kPolarityPressed = 1;
#endif

namespace static_scheduling{

ResetDevice::ResetDevice(Timer& timer) : _timer(timer), _resetButton(BUTTON1) {}

// definition of task execution time
static constexpr std::chrono::microseconds kTaskRunTime = 100000us;

bool ResetDevice::checkReset() {
    std::chrono::microseconds initialTime = _timer.elapsed_time();
    std::chrono::microseconds elapsedTime = std::chrono::microseconds::zero();
    int buttonState = 0;
    while(elapsedTime < kTaskRunTime){
            buttonState = _resetButton.read();  // Read the actual button state
    }
    return (buttonState == kPolarityPressed); 

}

void static_scheduling::ResetDevice::onRise() {

    _pressTime = _timer.elapsed_time();

}

std::chrono::microseconds static_scheduling::ResetDevice::getPressTime() {
    return _pressTime;
}
}