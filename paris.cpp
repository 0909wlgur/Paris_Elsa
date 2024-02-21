#include "paris.hpp"

// distribution is a Batch size PDF of queries followed by possion distribution.
// distribution.first = batchSize, distribution.second = query frequency of the batchsize 
// utilization is a GPU partition's computation utilization data at a particular batch size.
// utilization.first = batchSize, utilization.second = utilization of the batchsize
// throughputs is a throughput 2D matrix which is composed of GPU partition size k and batch size b.
void paris(std::vector<std::pair<int, int>> distribution, std::vector<std::pair<int, float>>* utilization, int** throughputs, int* result) {
    // Step A : Find MaxBatch under each GPU partition

    // maxBatchSize is a array for saving the maxBatchSize of the each partition
    // maxBatchSize.first = batchSize, maxBatchSize.second = utilization
    // maxBatchSizeInfo start with (1, x.xx), 5 element, (BATCHSIZE_END, xx.x) will be saved here
    std::vector<std::pair<int, float>> maxBatchSizeInfo = find_max_batch(utilization);   
    
    // Check the maxBatchSizeInfo
    for(int i = 0; i < maxBatchSizeInfo.size(); i++) {
        // std::cout << i << std::endl;
        std::cout << "The MaxBatch for GPU partition size " << GPU_Partition[i] << " is ";
        std::cout << maxBatchSizeInfo[i].first << " and the utilization is " << maxBatchSizeInfo[i].second << std::endl;
    }
    std::cout << std::endl;

    // Step B : Derive the relative ratio of GPU partition instance numbers

    float* partitionRatio = (float*)malloc(PARTITION_SIZE * sizeof(float));

    // partitionRatio[k] is in charge of the batchsize from GPU_Partition[k - 1] + 1 to the GPU_Partition[k]
    find_partition_ratio(partitionRatio, distribution, maxBatchSizeInfo, throughputs);

    // Check the partitionRatio
    std::cout << "The Partition Ratio Information..." << std::endl;
    for(int i = 0; i < PARTITION_SIZE; i++) {
        std::cout << "The Partition Ratio for GPU partition size " << GPU_Partition[i] << " is ";
        std::cout << partitionRatio[i] << std::endl;
    }
    std::cout << std::endl;

    // Step C : Determine the absolute number of GPU partition instances
    determine_gpu_partition(partitionRatio, result);
    
    free(partitionRatio);

    std::cout << "The Paris session is done." << std::endl << std::endl;
}