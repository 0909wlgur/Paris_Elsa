#include "elsa_util.hpp"

double** lookup_table;

// Implementation of Query class
Query::Query(unsigned int batchsize_, std::chrono::system_clock::duration SLA)
: batchsize(batchsize_) {
    sla = std::chrono::system_clock::now() + SLA;
    auto sla_ms = std::chrono::duration_cast<std::chrono::milliseconds>(SLA).count();
    name = "batchsize_" + std::to_string(sla_ms);
    std::cout << "Query " << name << " has been created!" << std::endl; 
}

std::chrono::system_clock::duration Query::enqueuedToGPU(int partition_size_) {
    setEstimatedTime(partition_size_);
    std::cout << "Query has been inserted to the GPU Queue!" << std::endl;
    return this->estimated_time;
}

void Query::setEstimatedTime(int partition_size_) { 
    estimated_time = std::chrono::duration_cast<std::chrono::system_clock::duration>(
        std::chrono::duration<double>(lookup_table[partition_size_][batchsize]));
}

int Query::getBatchSize() {
    return batchsize;
} 

double Query::getSLA(std::chrono::system_clock::time_point now) {
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(sla - now);
    return duration.count();
}

// Implementation of GPU class
GPU::GPU(int partition_size)
: partition_size(partition_size) {
    std::cout << "GPU Partition size" << partition_size << " has been created!" << std::endl;
    end_time = std::chrono::system_clock::now();
}

void GPU::enqueueQuery(Query* query) {
    wait_q.push(query);
    std::chrono::system_clock::duration added_time = query->enqueuedToGPU(partition_size);
    if(added_time.count() == 0)
        std::cout << "enqueueQuery function has some error!" << std::endl;
    end_time += added_time;
}

double GPU::getWaitTime(std::chrono::system_clock::time_point now) {
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - now);
    return duration.count();
}

int GPU::getPartitionSize() {
    return partition_size;
}

float GPU::getAlpha() {
    return alpha;
}

float GPU::getBeta() {
    return beta;
}
