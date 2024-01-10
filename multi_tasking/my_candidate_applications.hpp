#include "mbed.h"
#include "update-client/candidate_applications.hpp"

namespace update_client {

class MyCandidateApplications : public update_client::CandidateApplications {
    uint32_t getSlotForCandidate();
};

}  // namespace update_client

update_client::CandidateApplications* createCandidateApplications(
    BlockDevice& blockDevice,
    mbed::bd_addr_t storageAddress,
    mbed::bd_size_t storageSize,
    uint32_t headerSize,
    uint32_t nbrOfSlots);