#ifndef __ELSA_UTIL_H__
#define __ELSA_UTIL_H__

#include <iostream>
#include <string>
#include <queue>
#include <chrono>

// It contains the definition of class Query and GPU
extern double** lookup_table;

class Query {
private:
    // name is a name of query
    std::string name;
    // batchsize is a charicteristic of query
    int batchsize;
    // sla in query is a time point of execution time limit
    // The parameter SLA is a time duration, but the member variable sla is a time point
    std::chrono::system_clock::time_point sla;
    // estimated_time is a time duration of executing this query
    // this variable is determined after the query's partition has been determined
    std::chrono::system_clock::duration estimated_time;
public:
    // initializer of query
    Query(unsigned int batchsize_, std::chrono::system_clock::duration SLA);
    // Make this query enequeued to the GPU partition
    // And returns the added time of this GPU partition's end time
    std::chrono::system_clock::duration enqueuedToGPU(int partition_size_);
    // return this query's estimated time
    void setEstimatedTime(int partition_size_);
    // return batch size
    int getBatchSize();
    // return SLA time slack(time duration not a time point)   
    double getSLA(std::chrono::system_clock::time_point now);
};

class GPU {
private:
    // wait_q is a waiting queue for the gpu partition
    std::queue<Query*> wait_q;
    //end_time is the time that this gpu partition would be ended
    std::chrono::system_clock::time_point end_time;
    // partition_size is the size of the partition of gpu
    int partition_size;
    // alpha is a constant ratio for SLA computation
    float alpha;
    // beta is a constant ratio for T_(estimated,new)
    float beta;
public:
    // initializer of GPU
    GPU(int partition_size);
    // This function make query to be enqueued
    // and it raise its end time
    void enqueueQuery(Query* query);
    // Return wait time of this gpu partition job ending from now
    double getWaitTime(std::chrono::system_clock::time_point now);
    // Return partition size of this gpu
    int getPartitionSize();
    // Return alpha(constant proportional ratio for SLA computation)
    float getAlpha();
    // Return beta(constant proportional ratio for T_(estimated,new))
    float getBeta();
};

#endif