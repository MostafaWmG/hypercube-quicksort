#include <math.h>

class HyperCubeUtils {

private:

  /**
   * The number of dimensions in the hypercube
   */ 
  int dimensions;

public:

  HyperCubeUtils (int dimensions) {
    this->dimensions = dimensions;
  }

  /**
   * Determines which node to communicate with
   * @param {int} comm_rank The rank of the current node
   * @param {int} iteration Which iteration of the algorithm we are on
   * @return The rank of the node to communicate with
   */
  int getCommLink (int iteration, int comm_rank) {
    int mask = (int) pow(2, iteration - 1);
    return comm_rank ^ mask;
  }
};