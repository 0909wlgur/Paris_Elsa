#include <math.h>
#include "paris.hpp"

void find_partition_ratio(float* partitionRatio, std::vector<std::pair<int, int>> distribution, std::vector<std::pair<int, float>> maxBatchSizeInfo, int** throughputs) {
    // For smooth computation of ratio for partition[k], emplace the (1, 0.0) to the maxBatchSizeInfo
    maxBatchSizeInfo.emplace(maxBatchSizeInfo.begin(), std::pair<int, float>(1, 0.0));
    int start = 0;

    for(int k = 0; k < PARTITION_SIZE; k++) {
        float ratio = 0;
        int end = log2(maxBatchSizeInfo[k + 1].first) + 1;

        for(int b = start; b < end; b++) {
            ratio += (float) distribution[b].second / throughputs[k][b];
            if(throughputs[k][b] == 0)
                std::cout << "The k is " << k << " and the " << b << std::endl;
            std::cout<< "The batchsize is " << pow(2, b) << " and the ratio is ";
            std::cout << (float) distribution[b].second / throughputs[k][b] << std::endl;
        }
        partitionRatio[k] = ratio;
        start = log2(maxBatchSizeInfo[k + 1].first) + 1;
    }

    // For smooth computation of ratio for partition[k], erase the (1, 0.0) from the maxBatchSizeInfo
    maxBatchSizeInfo.erase(maxBatchSizeInfo.begin());
    std::cout << std::endl;
}