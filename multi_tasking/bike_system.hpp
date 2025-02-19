// Copyright 2022 Haute école d'ingénierie et d'architecture de Fribourg
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/****************************************************************************
 * @file bike_system.hpp
 * @author Serge Ayer <serge.ayer@hefr.ch>
 *
 * @brief Bike System header file (static scheduling)
 *
 * @date 2023-08-20
 * @version 1.0.0
 ***************************************************************************/

#pragma once

// from advembsof
#include "display_device.hpp"
#include "task_logger.hpp"
#include "cpu_logger.hpp"
#include "memory_logger.hpp"

// from common
#include "sensor_device.hpp"
#include "speedometer.hpp"

// local
#include "gear_device.hpp"
#include "pedal_device.hpp"
#include "reset_device.hpp"

#include "memory_leak.hpp"

namespace multi_tasking {

class BikeSystem {
   public:
    // constructor
    BikeSystem();

    // make the class non copyable
    BikeSystem(BikeSystem&)            = delete;
    BikeSystem& operator=(BikeSystem&) = delete;

    // method called in main() for starting the system
    void start();

    // method called in main() for starting the system with the event
    void startWithEventQueue();

    // method called for stopping the system
    void stop();

#if defined(MBED_TEST_MODE)
    const advembsof::TaskLogger& getTaskLogger();
    bike_computer::Speedometer& getSpeedometer();
    GearDevice& getGearDevice();
    uint8_t getCurrentGear() const;
#endif  // defined(MBED_TEST_MODE)

    // these methods must be made public for test purposes only
#if defined(MBED_TEST_MODE)

   public:
#else

   private:
#endif
   void onReset();
   
   private:
    // private methods
    void init();
    void onGearChanged(uint8_t currentGear, uint8_t currentGearSize);
    void onRotationSpeedChanged(const std::chrono::milliseconds& pedalRotationTime);
    void gearTask();  
    void speedDistanceTask(); 
    void temperatureTask();
    void resetTask();
    void displayTask();
    //void cpuTask();

    EventQueue _eventQueue;
    EventQueue _eventQueueForISRs;

    Thread _eventThread;

    // stop flag, used for stopping the super-loop (set in stop())
    bool _stopFlag = false;
     // used for computing the reset response time
    std::chrono::microseconds _resetTime = std::chrono::microseconds::zero();
    // reset flag (set in onReset)
    volatile bool _resetFlag = false;
    // timer instance used for loggint task time and used by ResetDevice
    Timer _timer;
    // data member that represents the device for manipulating the gear
    GearDevice _gearDevice;
    uint8_t _currentGear = bike_computer::kMinGear;
    uint8_t _currentGearSize = bike_computer::kMinGearSize;
    // data member that represents the device for manipulating the pedal rotation
    // speed/time
    PedalDevice _pedalDevice;
    float _currentSpeed = 0.0f;
    float _traveledDistance = 0.0f;
    // data member that represents the device used for resetting
    ResetDevice _resetDevice;
    // data member that represents the device display
    advembsof::DisplayDevice _displayDevice;
    // data member that represents the device for counting wheel rotations
    bike_computer::Speedometer _speedometer;
    // data member that represents the sensor device
    bike_computer::SensorDevice _sensorDevice;
    float _currentTemperature = 0.0f;

    // used for logging task info
    advembsof::TaskLogger _taskLogger;

    
    
    // needed in mem code lab
    advembsof::MemoryLogger _memoryLogger;


    MemoryLeak memoryLeak;

};

}  // namespace multi_tasking
