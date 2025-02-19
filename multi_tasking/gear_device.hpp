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
 * @file gear_device.hpp
 * @author Serge Ayer <serge.ayer@hefr.ch>
 *
 * @brief Gear Device header file (static scheduling)
 *
 * @date 2023-08-20
 * @version 1.0.0
 ***************************************************************************/

#pragma once

#include "constants.hpp"
#include "mbed.h"

namespace multi_tasking {

class GearDevice {
   public:
    GearDevice(EventQueue& eventQueue,  // NOLINT(runtime/references)
               mbed::Callback<void(uint8_t, uint8_t)> cb);
    // make the class non copyable
    GearDevice(GearDevice&)            = delete;
    GearDevice& operator=(GearDevice&) = delete;

    // method called for updating the bike system
    uint8_t getCurrentGear();
    uint8_t getCurrentGearSize() const;

    void onUp();
    void onDown();


   private:
    // data members
    volatile uint8_t _currentGear = bike_computer::kMinGear;

    EventQueue& _eventQueue;
    mbed::Callback<void(uint8_t, uint8_t)> _cb;

    void postEvent();

};

}  // namespace multi_tasking
