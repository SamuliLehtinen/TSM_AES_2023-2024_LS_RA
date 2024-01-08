#pragma once

#include "mbed.h"

namespace multi_tasking {

class MemoryLeak {
   public:
    static constexpr uint16_t kArraySize = 1024;

    // create a memory leak in the constructor itself
    MemoryLeak() { _ptr = new int[kArraySize]; }

    void use() {
        for (uint16_t i = 0; i < kArraySize; i++) {
            _ptr[i] = i;
        }
    }

   private:
    int* _ptr;
};

}  // namespace multi_tasking