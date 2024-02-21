#include "elsa.hpp"

bool compare(GPU g1, GPU g2) {
    return g1.getPartitionSize() < g2.getPartitionSize();
}

void elsa(std::vector<GPU> gpu_partitions, Query* query) {
    std::cout << "Elsa Session started" << std::endl;
    std::sort(gpu_partitions.begin(), gpu_partitions.end(), compare);

    bool result = false;

    // Step A: schedule new query if the GPU partition can satisfy SLA
    result = schedule_new_query(gpu_partitions, query);
    if(result == true) {
        std::cout << "New query has been scheduled successfully!" << std::endl;
    } else {
        // Step B : If step A failed, schedule query to the GPU partition that can service the new query the fastest
        std::cout << "It will be some SLA violation!" << std::endl;
        schedule_when_emergency(gpu_partitions, query);
    }

    std::cout << "Elsa Session Ended..." << std::endl;
}