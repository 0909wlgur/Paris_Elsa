#ifndef __ELSA_HPP__
#define __ELSA_HPP__

#include <algorithm>
#include "elsa_util.hpp"

bool schedule_new_query(std::vector<GPU> gpu_partitions, Query* query);
void schedule_when_emergency(std::vector<GPU> gpu_partitions, Query* query);

bool compare(GPU g1, GPU g2);

#endif