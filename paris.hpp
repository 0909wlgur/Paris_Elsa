#ifndef __PARIS_HPP__
#define __PARIS_HPP__

#include <vector>
#include <utility>
#include <iostream>
#include <math.h>

#include "globals.hpp"

// Get Information about GPU and inferences
const int Total_MIG = 7 * NUMBER_OF_GPU;

void paris(std::vector<std::pair<int, int>> distribution, std::vector<std::pair<int, float>>* utilization, int** throughputs, int* result);
std::vector<std::pair<int, float>> find_max_batch(std::vector<std::pair<int, float>>* utilization);
void find_partition_ratio(float* partitionRatio, std::vector<std::pair<int, int>> distribution, std::vector<std::pair<int, float>> maxBatchSizeInfo, int** throughputs);
void determine_gpu_partition(float* partitionRatio, int* result);
// bool recursive_partition_check(int* preresult);

#endif