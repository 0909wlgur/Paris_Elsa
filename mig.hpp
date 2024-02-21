#ifndef __MIG_HPP__
#define __MIG_HPP__

#include <iostream>
#include <vector>

#include "globals.hpp"

const int MEM_Partition[PARTITION_SIZE] = {10, 20, 40, 40, 80};

class MIG {
private:
    static int count;
    int instance[PARTITION_SIZE];
    int GPC;
    int Mem;
    int GPU;
public:
    MIG(int gpc_ = 7, int mem_ = 80);

    // partition case is 0 ~ 4
    // each means GPC 1, GPC 2, GPC 3, GPC 4, GPC 7
    void addConfig(int partitionCase, std::vector<MIG>& handler);
    // Set counter
    void setCounter();
    // Set remaining GPC
    
    void addInstance(int k);

    void subInstance(int k);

    int getInstance(int k);

    void printInstance();

    // return remaining GPC
    void subGPC(int gpc);
    // Set remaining Mem
    void subMem(int mem);
    // Set remaining GPU
    int getGPC();
    // return remaining memory
    int getMem();
    // Get GPU number
    int getGPU();
};

#endif