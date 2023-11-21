#include "reset_device.hpp"

#if defined(TARGET_DISCO_H747I)
#define PUSH_BUTTON BUTTON1
static constexpr uint8_t kPolarityPressed = 1;
#endif

namespace static_scheduling{

ResetDevice::ResetDevice(Timer& timer) : _timer(timer), _resetButton(PUSH_BUTTON) {}

// definition of task execution time
static constexpr std::chrono::microseconds kTaskRunTime = 100000us;

bool ResetDevice::checkReset() {
    std::chrono::microseconds initialTime = _timer.elapsed_time();
    std::chrono::microseconds elapsedTime = std::chrono::microseconds::zero();
    bool buttonState = false;
    
    while(elapsedTime < kTaskRunTime){
         if (!buttonState) {
            buttonState = _resetButton.read() == kPolarityPressed;
        }
            elapsedTime = _timer.elapsed_time() - initialTime;  
    }
    return buttonState; 

}

void static_scheduling::ResetDevice::onRise() {

    _pressTime = _timer.elapsed_time();

}

std::chrono::microseconds static_scheduling::ResetDevice::getPressTime() {
    return _pressTime;
}
}