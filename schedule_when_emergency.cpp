#include "elsa.hpp"

void schedule_when_emergency(std::vector<GPU> gpu_partitions, Query* query) { 
    int t_min = INT32_MAX;
    auto G_min = gpu_partitions.begin();
    
    for (auto gpu = gpu_partitions.begin(); gpu<gpu_partitions.end(); gpu++) {
        auto now = std::chrono::system_clock::now();
        double wait_time = gpu->getWaitTime(now);
        double estimated_time = lookup_table[gpu->getPartitionSize()][query->getBatchSize()];
        
        if(t_min > wait_time + estimated_time) {
            t_min = wait_time + estimated_time;
            G_min = gpu;
        }
    }

    G_min->enqueueQuery(query);
}