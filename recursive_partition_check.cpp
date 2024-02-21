#include "paris.hpp"

bool recursive_partition_check(int* preresult) {
    for(int iter = 0; iter < POSSIBLE_MIG_PARTITION_SIZE_CASE; iter ++) {
            for(int k = 0; k < PARTITION_SIZE; k++) {
                if(preresult[k] - possible_mig_configuration_count[iter][k] < 0)
                    break;
                // call recursive function again
            }
    }
}