#include "paris.hpp"

void determine_gpu_partition(float* partitionRatio, int* result) {
    float sum = 0;
    for(int k = 0; k < PARTITION_SIZE; k++) { 
        sum += partitionRatio[k] * GPU_Partition[k];
    }

    std::cout << "The sum of needed partion ratio is " << sum << std::endl;

    float MIG_Partition_Allocate_Ratio = Total_MIG / sum;

    std::cout << "The proportional variable of partion ratio is " << MIG_Partition_Allocate_Ratio << std::endl;

    // original paris partition
    for(int k = 0; k < PARTITION_SIZE; k++) 
        result[k] = MIG_Partition_Allocate_Ratio * partitionRatio[k];

    // Not an paris implementation but supplementation of paris
    /* int preresult[PARTITION_SIZE];
    int partitionSum = 0;
    bool raw_partition_clear = true;

    // Compare with possible data mad by hard coding
    for(int k = 0; k < PARTITION_SIZE; k++) {
        preresult[k] = round(MIG_Partition_Allocate_Ratio * partitionRatio[k]);
    }

    for(int k = 0; k < PARTITION_SIZE; k++) {
        sum += (k + 1) * preresult[k];
    }

    
    int* temp = nullptr;

    if(sum > NUMBER_OF_GPU * POSSIBLE_MAX_MIG_INSTANCE) {
        raw_partition_clear = false;
    } else {
        temp = new int[PARTITION_SIZE];
        for(int k = 0; k < PARTITION_SIZE; k++) {
            temp[k] = preresult[k];
        }

        raw_partition_clear = recursive_partition_check(temp);
    }

    if(raw_partition_clear){
        for(int k = 0; k < PARTITION_SIZE; k++)
            result[k] = preresult[k];
    } else {
        for(int k = 0; k < PARTITION_SIZE; k++) 
            result[k] = MIG_Partition_Allocate_Ratio * partitionRatio[k];
    }

    if(temp != nullptr)
        delete[] temp; */
}