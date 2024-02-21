#ifndef __GLOBAL_HPP__
#define __GLOBAL_HPP__

#define BATCHSIZE_END 64
#define NUMBER_OF_GPU 2
#define PARTITION_SIZE 5
#define POSSIBLE_MIG_CONFIGURATION 19
#define POSSIBLE_MAX_MIG_INSTANCE 7 
#define POSSIBLE_MIG_PARTITION_SIZE_CASE 14

const int GPU_Partition[PARTITION_SIZE] = {1, 2, 3, 4, 7};

extern int possible_mig_configuration[POSSIBLE_MIG_PARTITION_SIZE_CASE][POSSIBLE_MAX_MIG_INSTANCE];
extern int possible_mig_configuration_count[POSSIBLE_MIG_PARTITION_SIZE_CASE][PARTITION_SIZE];


#endif