#include <iostream>
#include <vector>
#include <utility>
#include <math.h>

#include "paris.hpp"
#include "elsa.hpp"
#include "allocate_mig.hpp"

int main() {
    std::vector<std::pair<int, int>> distribution;

    // make psuedo data
    // distribution = (batchsize, query frequency)
    // Made by Hard Coding.
    distribution.push_back(std::pair<int, int> (1, 1));
    distribution.push_back(std::pair<int, int> (2, 4));
    distribution.push_back(std::pair<int, int> (4, 16));
    distribution.push_back(std::pair<int, int> (8, 16));
    distribution.push_back(std::pair<int, int> (16, 16));
    distribution.push_back(std::pair<int, int> (32, 16));
    distribution.push_back(std::pair<int, int> (64, 4));
    distribution.push_back(std::pair<int, int> (128, 4));

    // utilization = (batchsize, utilization)
    std::vector<std::pair<int, float>>* utilization = new std::vector<std::pair<int, float>>[PARTITION_SIZE];
    // 1 GPC
    utilization[0].push_back(std::pair<int, float>(1, 0.36));
    utilization[0].push_back(std::pair<int, float>(2, 0.5));
    utilization[0].push_back(std::pair<int, float>(4, 0.8));
    utilization[0].push_back(std::pair<int, float>(8, 0.87));
    utilization[0].push_back(std::pair<int, float>(16, 0.9));
    utilization[0].push_back(std::pair<int, float>(32, 0.95));
    utilization[0].push_back(std::pair<int, float>(64, 0.97));
    utilization[0].push_back(std::pair<int, float>(128, 0.97));

    // 2 GPC
    utilization[1].push_back(std::pair<int, float>(1, 0.36));
    utilization[1].push_back(std::pair<int, float>(2, 0.5));
    utilization[1].push_back(std::pair<int, float>(4, 0.55));
    utilization[1].push_back(std::pair<int, float>(8, 0.7));
    utilization[1].push_back(std::pair<int, float>(16, 0.82));
    utilization[1].push_back(std::pair<int, float>(32, 0.9));
    utilization[1].push_back(std::pair<int, float>(64, 0.93));
    utilization[1].push_back(std::pair<int, float>(128, 0.93));

    // 3 GPC
    utilization[2].push_back(std::pair<int, float>(1, 0.36));
    utilization[2].push_back(std::pair<int, float>(2, 0.5));
    utilization[2].push_back(std::pair<int, float>(4, 0.55));
    utilization[2].push_back(std::pair<int, float>(8, 0.7));
    utilization[2].push_back(std::pair<int, float>(16, 0.75));
    utilization[2].push_back(std::pair<int, float>(32, 0.8));
    utilization[2].push_back(std::pair<int, float>(64, 0.84));
    utilization[2].push_back(std::pair<int, float>(128, 0.84));

    // 4 GPC
    utilization[3].push_back(std::pair<int, float>(1, 0.36));
    utilization[3].push_back(std::pair<int, float>(2, 0.5));
    utilization[3].push_back(std::pair<int, float>(4, 0.55));
    utilization[3].push_back(std::pair<int, float>(8, 0.7));
    utilization[3].push_back(std::pair<int, float>(16, 0.75));
    utilization[3].push_back(std::pair<int, float>(32, 0.78));
    utilization[3].push_back(std::pair<int, float>(64, 0.8));
    utilization[3].push_back(std::pair<int, float>(128, 0.83));

    // 7 GPC
    utilization[4].push_back(std::pair<int, float>(1, 0.36));
    utilization[4].push_back(std::pair<int, float>(2, 0.5));
    utilization[4].push_back(std::pair<int, float>(4, 0.55));
    utilization[4].push_back(std::pair<int, float>(8, 0.6));
    utilization[4].push_back(std::pair<int, float>(16, 0.65));
    utilization[4].push_back(std::pair<int, float>(32, 0.68));
    utilization[4].push_back(std::pair<int, float>(64, 0.7));
    utilization[4].push_back(std::pair<int, float>(128, 0.75));

    int** throughputs = new int*[PARTITION_SIZE];
    for(int i = 0; i < PARTITION_SIZE; i++)
        throughputs[i] = new int[8];
    
    for(int i = 0; i<PARTITION_SIZE;i++) {
        for(int j = 0; j < 8; j++)
            throughputs[i][j] = 100;
    }
    
    int* result = new int[PARTITION_SIZE];

    // Step 1-a. Execute the Paris
    paris(distribution, utilization, throughputs, result);

    std::cout << "The partitioning instance size is..." << std::endl;
    for(int i = 0; i < PARTITION_SIZE; i++){
        std::cout << "For partitioning size " << GPU_Partition[i] << " is ";
        std::cout << result[i] << std::endl;
    }
    std::cout<<std::endl;

    // Step 1-b. Allocate the Paris result into the GPU
    std::cout << "Allocating session is started." << std::endl << std::endl;
    allocate_mig(result);
    std::cout<<std::endl;

    delete[] utilization;
    delete result;

    for(int i = 0; i< PARTITION_SIZE; i++)
        delete throughputs[i];
    delete throughputs;

    return 0;
}