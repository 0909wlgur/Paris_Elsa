#include "elsa.hpp"

bool schedule_new_query(std::vector<GPU> gpu_partitions, Query* query) {
    for(auto gpu = gpu_partitions.begin(); gpu < gpu_partitions.end(); gpu++) {
        auto now = std::chrono::system_clock::now();
        double wait_time = gpu->getWaitTime(now);
        double estimated_time = lookup_table[gpu->getPartitionSize()][query->getBatchSize()];
        
        if(query->getSLA(now) > gpu->getAlpha() * (wait_time + gpu->getBeta() * estimated_time)){
            gpu->enqueueQuery(query);
            return true;
        }
    }

    return false;
}