#include <string>
#include <sstream>

#include "allocate_mig.hpp"
#include "mig.hpp"

void allocate_mig(int* result) {
    std::vector<MIG> handler;
    MIG mig;
    mig.setCounter();

    for(int k = PARTITION_SIZE - 1; k >= 0; k--) {
        for(int iter = 0; iter < result[k]; iter++) {
            mig.addConfig(k, handler);
        }
    }

    std::cout << "The space allocation status will be as followed..." << std::endl;
    for(auto iter = handler.begin(); iter < handler.end(); iter++) {
        iter->printInstance();
    }

    std::string baseCommand = {"sudo nvidia-smi mig -i"};

    // Order of  1, 2, 3, 4, 7 
    std::vector<std::string> MIG_Config;
    MIG_Config.push_back("1g.10gb");
    MIG_Config.push_back("2g.20gb");
    MIG_Config.push_back("3g.40gb");
    MIG_Config.push_back("4g.40gb");
    MIG_Config.push_back("7g.80gb");
    
    std::string command1 = "sudo nvidia-smi mig -dci; sudo nvidia-smi mig -dgi;";
    system(command1.c_str());

    for(auto iter = handler.begin(); iter < handler.end(); iter++) {
        std::cout << "GPU" << iter->getGPU() << "..." << std::endl;
        for(int k = PARTITION_SIZE - 1; k >= 0; k--) {
            for(int i = 0; i < iter->getInstance(k); i++) {
                std::stringstream ss;
                std::string arg = MIG_Config[k];
                // std::cout << arg << std::endl;
                ss << baseCommand << " " << iter->getGPU() << " -cgi " << arg << " -C";
                std::string command = ss.str();
                std::cout << command << std::endl;
                system(command.c_str());
            }
        }
        std::cout << std::endl;
    }
    
}