class HyperCubeUtils {

public:

  HyperCubeUtils () {}

  /**
   * Determines which node to communicate with
   * @param {int} comm_rank The rank of the current node
   * @param {int} iteration Which iteration of the algorithm we are on
   * @return The rank of the node to communicate with
   */
  int getCommLink (int comm_rank, int iteration) {
    return 0;
  }
};