#include <math.h>

class HypercubeUtils {

private:

  /**
   * The number of dimensions in the hypercube
   */ 
  int dimensions;

public:

  HypercubeUtils (int dimensions) {
    this->dimensions = dimensions;
  }

  /**
   * Determines which node to communicate with
   * @param {int} comm_rank The rank of the current node
   * @param {int} iteration Which iteration of the algorithm we are on
   * @return {int} The rank of the node to communicate with
   */
  int getCommLink (int iteration, int comm_rank) {
    int mask = (int) pow(2, iteration - 1);
    return comm_rank ^ mask;
  }

  /**
   * Determines which list to pass
   * @param {int} comm_rank The rank of the current node
   * @param {int} iteration Which iteration of the algorithm we are on
   * @return {boolean} True if the larger set should be passed; false if the smaller set should be passed.
   */
  bool shouldPassLargerList (int iteration, int comm_rank) {
    return (comm_rank & (1 << (iteration - 1))) == 0 ? false : true;
  }

};