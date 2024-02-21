#include "paris.hpp"

std::vector<std::pair<int, float>> find_max_batch(std::vector<std::pair<int, float>>* utilization) {
    std::vector<std::pair<int, float>> maxBatchSizeInfo;
    
    // initialize the maxBatchSizeInfo for batchsize 1
    for(int k = 0; k < PARTITION_SIZE; k++) {
        std::vector<std::pair<int, float>> temp = *(utilization + k);

        bool found = false;
        for(auto iter : temp) {
            if(iter.second >= 0.8 ) {
                maxBatchSizeInfo.push_back(iter);
                found = true;
                break;
            }
        }

        // Suppose the only 7 GPC can't reach the utility of 80%
        if(!found) {
            // std::cout << "There isn't a maxBatchSize for partition size " << GPU_Partition[k] << std::endl;
            auto temp = utilization[PARTITION_SIZE - 1].back();
            maxBatchSizeInfo.push_back(temp);
            // std::cout << "So the batch size limit has become the last element of the maxBatchSizeInfo" << std::endl;
        }
        // std::cout<<"maxBatchSizeInfo is "<<maxBatchSizeInfo.size()<<std::endl;
    }
    
    std::cout << std::endl;
    return maxBatchSizeInfo;
}