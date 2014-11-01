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
    int bit = dimensions - iteration;
    int mask = (int) pow(2, bit);
    return comm_rank ^ mask;
  }

  /**
   * Determines which list to pass
   * @param {int} comm_rank The rank of the current node
   * @param {int} iteration Which iteration of the algorithm we are on
   * @return {boolean} True if the larger set should be passed; false if the smaller set should be passed.
   */
  bool shouldPassLargerList (int iteration, int comm_rank) {
    int bit = dimensions - iteration;
    return (comm_rank & (1 << bit)) == 0 ? true : false;
  }

  /**
   * Gets the group that the process should be in for the next iteration
   * @param {int} comm_rank The rank of the current node
   * @param {int} iteration Which iteration of the algorithm we are on
   * @return {int} The group number for the next iteration
   */
  int getNextGroup (int iteration, int comm_rank) {
    int bit = dimensions - iteration;
    return (comm_rank & (1 << bit)) == 0 ? 0 : 1;
  }

};