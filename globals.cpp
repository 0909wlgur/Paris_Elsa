#include "globals.hpp"

extern int possible_mig_configuration[POSSIBLE_MIG_PARTITION_SIZE_CASE][POSSIBLE_MAX_MIG_INSTANCE] = {
    {7},
    {4, 3}, 
    {4, 2, 1},  
    {4, 1, 1, 1},
    {3, 3},
    {3, 2, 1},
    {3, 1, 1, 1},
    {2, 2, 3},
    {2, 1, 1, 3},
    {1, 1, 1, 1, 3},
    {2, 2, 2, 1},
    {2, 1, 1, 2, 1},
    {2, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1}
};

/* extern int possible_mig_configuration[POSSIBLE_MIG_CONFIGURATION][POSSIBLE_MAX_MIG_INSTANCE] = {
    {7},
    {4, 3}, 
    {4, 2, 1},  
    {4, 1, 1, 1},
    {3, 3},
    {3, 2, 1},
    {3, 1, 1, 1},
    {2, 2, 3},
    {2, 1, 1, 3},
    {1, 1, 2, 3},
    {1, 1, 1, 1, 3},
    {2, 2, 2, 1},
    {2, 1, 1, 2, 1},
    {1, 1, 2, 2, 1},
    {2, 1, 1, 1, 1, 1},
    {1, 1, 2, 1, 1, 1},
    {1, 1, 1, 1, 2, 1},
    {1, 1, 1, 1, 1, 2},
    {1, 1, 1, 1, 1, 1, 1}
}; */

extern int possible_mig_configuration_count[POSSIBLE_MIG_PARTITION_SIZE_CASE][PARTITION_SIZE] = {
    {0, 0, 0, 0, 1},
    {0, 0, 1, 1, 0},
    {1, 1, 0, 1, 0},
    {3, 0, 0, 1, 0},
    {0, 0, 2, 0, 0},
    {1, 1, 1, 0, 0},
    {3, 0, 1, 0, 0},
    {0, 2, 1, 0, 0},
    {2, 1, 1, 0, 0},
    {4, 0, 1, 0, 0},
    {1, 3, 0, 0, 0},
    {3, 2, 0, 0, 0},
    {5, 1, 0, 0, 0},
    {7, 0, 0, 0, 0}
};
