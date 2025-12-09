#include "l1_rd_miss.h"

int main(int argc, char* argv[]) {

  float lat = l1_rd_miss(argc,argv);

  // The following dump is misleading
  // "(unsigned)lat" indicates the evaluated L1 cache latency in cycles
  // but "-gpgpu_l1_rd_missency" is supposed to indicate the L1 cache latency
  // used in the GPU simulator configuration file.

    // std::cout << "\n//Accel_Sim config: \n";
    // std::cout << "-gpgpu_l1_rd_missency " << (unsigned)lat << std::endl;
  

  return 1;
}
