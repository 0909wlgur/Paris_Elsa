#include "mig.hpp"

int MIG::count = 0;

MIG::MIG(int gpc_, int mem_) :GPC(gpc_), Mem(mem_) {
    this->GPU = count;
    count++;

    for(int k = 0; k < PARTITION_SIZE; k++) {
        this->instance[k] = 0;
    }
}

void MIG::addConfig(int partitionCase, std::vector<MIG>& handler) {
    bool configAdded = false;
    for (auto& GPU : handler) { // 참조 사용
        // std::cout << "The GPU's remaining GPC is " << GPU.GPC << " and ";
        // std::cout << "the GPU's remaining Mem is " << GPU.Mem << std::endl;
        if (GPU.getGPC() >= GPU_Partition[partitionCase] && GPU.getMem() >= MEM_Partition[partitionCase]) {
            // MIG가 가능한 경우
            GPU.subGPC(GPU_Partition[partitionCase]);
            GPU.subMem(MEM_Partition[partitionCase]);
            GPU.addInstance(partitionCase);
            // std::cout << "GPC is inserted at GPU index " << GPU.GPU << std::endl;
            configAdded = true;
            break;
        }
    }

    if (!configAdded) {
        // 마지막 MIG가 가능하지 않은 경우
        MIG new_mig;
        new_mig.subGPC(GPU_Partition[partitionCase]); 
        new_mig.subMem(MEM_Partition[partitionCase]);
        new_mig.addInstance(partitionCase);
        handler.push_back(new_mig);
        // std::cout << "New MIG instance added and configured." << std::endl;
    }
}

void MIG::addInstance(int k) {
    instance[k] += 1;
}

void MIG::subInstance(int k) {
    instance[k] -= 1;
}

int MIG::getInstance(int k) {
    return instance[k];
}

void MIG::printInstance() {
    std::cout << "GPU " << this->GPU << " : ";
    for(int k = 0; k < PARTITION_SIZE; k++) {
        std::cout << this->instance[k] << " ";
    }
    std::cout << std::endl;
}

void MIG::subGPC(int gpc) {
    this->GPC -= gpc;
}

void MIG::subMem(int mem) {
    this->Mem -= mem;
}

void MIG::setCounter() {
    count = 0;
}

int MIG::getGPC() {
    return this->GPC;
}

int MIG::getMem() {
    return this->Mem;
}

int MIG::getGPU() {
    return this->GPU;
}