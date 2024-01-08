#pragma once

#include "mbed.h"
#include "memory_logger.hpp"
#include "mbed_trace.h"

namespace multi_tasking {

class MemoryFragmenter {
   public:
    // create a memory leak in the constructor itself
    MemoryFragmenter() {}

    void fragmentMemory() {
        // create a memory logger
        advembsof::MemoryLogger memorLogger;

        // get heap info
        mbed_stats_heap_t heapInfo = {0};
        mbed_stats_heap_get(&heapInfo);
        uint32_t availableSize =
            heapInfo.reserved_size - heapInfo.current_size - heapInfo.overhead_size;
        tr_debug("Available heap size is %" PRIu32 " (reserved %" PRIu32 ")",
                 availableSize,
                 heapInfo.reserved_size);

        // divide the available size by 8 blocks that we allocate
        uint32_t blockSize = (availableSize - kMarginSpace) / kNbrOfBlocks;
        tr_debug("Allocating blocks of size %" PRIu32 "", blockSize);
        char* pBlockArray[kNbrOfBlocks] = {NULL};
        for (uint32_t blockIndex = 0; blockIndex < kNbrOfBlocks; blockIndex++) {
            pBlockArray[blockIndex] = new char[blockSize];
            if (pBlockArray[blockIndex] == NULL) {
                tr_error("Cannot allocate block memory for index %" PRIu32 "",
                         blockIndex);
            }
            tr_debug("Allocated block index  %" PRIu32 " of size  %" PRIu32
                     " at address 0x%08" PRIx32 "",
                     blockIndex,
                     blockSize,
                     (uint32_t)pBlockArray[blockIndex]);
            // copy to member variable to prevent them from being optimized away
            for (uint32_t index = 0; index < kArraySize; index++) {
                _doubleArray[index] += (double)pBlockArray[blockIndex][index];
            }
        }
        // the full heap (or almost) should be allocated
        tr_debug("Heap statistics after full allocation:");
        memorLogger.getAndPrintHeapStatistics();
        // delete only the even blocks
        for (uint32_t blockIndex = 0; blockIndex < kNbrOfBlocks; blockIndex += 2) {
            delete[] pBlockArray[blockIndex];
            pBlockArray[blockIndex] = NULL;
        }
        // we should have half of the heap space free
        tr_debug("Heap statistics after half deallocation:");
        memorLogger.getAndPrintHeapStatistics();

        // trying to allocated one block that is slightly bigger
        // without fragmentation, this allocation should succeed
        heapInfo = {0};
        mbed_stats_heap_get(&heapInfo);
        availableSize =
            heapInfo.reserved_size - heapInfo.current_size - heapInfo.overhead_size;
        tr_debug("Available heap size is  %" PRIu32 " (reserved  %" PRIu32 ")",
                 availableSize,
                 heapInfo.reserved_size);
        blockSize += 8;
        // this allocation will fail
        tr_debug("Allocating 1 block of size %" PRIu32 " should succeed !", blockSize);
        pBlockArray[0] = new char[blockSize];
        // copy to member variable to prevent them from being optimized away
        for (uint32_t index = 0; index < kArraySize; index++) {
            _doubleArray[index] += (double)pBlockArray[0][index];
        }
    }

   private:
    static constexpr uint8_t kNbrOfBlocks  = 8;
    static constexpr uint16_t kMarginSpace = 1024;
    static constexpr uint8_t kArraySize    = 100;
    double _doubleArray[kArraySize]        = {0};
};

}  // namespace multi_tasking
