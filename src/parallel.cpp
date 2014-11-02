#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <iostream>
#include <limits>
#include <math.h>
#include "quicksort_utils.cpp"
#include "hypercube_utils.cpp"
#include "mpi.h"

using namespace std;

void printBuffer (int list[], int length) {
  std::cout << "[";
  for (int i = 0; i < length; i++) {
    std::cout << list[i];
    if (i < length - 1) {
      std::cout << ", ";
    }
  }
  std::cout << "]";
}

int main (int argc, const char *argv[]) {

  /**
   * Initialize
   */
  int length = atoi(argv[1]);
  int rank, size, sortMe[length], MASTER = 0;
  bool IS_MASTER, IS_SLAVE;
  QuicksortUtils q_utils;

  MPI_Init(NULL, NULL);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  IS_MASTER = rank == 0;
  IS_SLAVE = ! IS_MASTER;

  /**
   * Check that the user initialized a hypercube
   */
  int hypercubeDimensions = 1;
  int sizee;
  sizee = pow(2, hypercubeDimensions);
  while (sizee < size) {
    hypercubeDimensions += 1;
    sizee = pow(2, hypercubeDimensions);
  }

  if (sizee != size) {
    if (IS_MASTER) {
      std::cout << "Invalid number of processes..." << endl;
      std::cout << "We're running a hypercube here..." << endl;
    }
    MPI_Finalize();
    exit(0);
  }

  /** 
   * Calculate how the list will be scattered
   */
  int list_size = length / size;
  int scatter_sizes[size];
  int scatter_offsets[size];
  int remainz = length % size;
  for (int i = 0; i < size; i++) {
    scatter_sizes[i] = list_size;
    if (remainz > 0) {
      scatter_sizes[i] += 1;
      remainz -= 1;
    }
    if (i == 0) {
      scatter_offsets[i] = 0;
    } else {
      scatter_offsets[i] = scatter_offsets[i-1] + scatter_sizes[i-1];
    }
  }
  if (IS_MASTER) {
    for (int i = 0; i < size; i++) {
      cout << "0: Sending " << scatter_sizes[i] << " elements to " << i << " starting at element " << scatter_offsets[i] << endl;
    }
  }

  /**
   * Initialize hypercube utils
   */
  HypercubeUtils h_utils(hypercubeDimensions);


  /**
   * Generate a large random array
   */
  if (IS_MASTER) {
    // srand(time(NULL));
    srand(0);
    int intMax = std::numeric_limits<int>::max();
    for (int i = 0; i < length + 1; i++) {
      sortMe[i] = rand() % 10;
    }

    std::cout << rank << ": Generated an array of " << length << " random integers between 0 and " << intMax << endl;
  }

  /**
   * Scatter array
   */
  if(IS_MASTER) {
    cout << "Initial array: ";
    printBuffer(sortMe, length);
    cout << endl;
  }
  int *currBuffer;
  int currBufferSize = scatter_sizes[rank];
  currBuffer = new int [currBufferSize];
  MPI_Scatterv(sortMe, scatter_sizes, scatter_offsets, MPI_INT, currBuffer, currBufferSize, MPI_INT, MASTER, MPI_COMM_WORLD);
  cout << rank << ": Received array ";
  printBuffer(currBuffer, currBufferSize);
  cout << endl;


  
  /**
   * Iterate compare & exchange
   */
  MPI_Comm currComm = MPI_COMM_WORLD;
  for (int iteration = 1; iteration <= hypercubeDimensions; iteration++) {

    // choose & broadcast pivot
    int currentRank;
    int pivot;
    MPI_Comm_rank(currComm, &currentRank);
    if (currentRank == 0) {
      pivot = q_utils.choosePivot(currBuffer, currBufferSize);
      cout << rank << ", " << iteration << ": chose current pivot as " << pivot << endl;
    }
    MPI_Bcast(&pivot, 1, MPI_INT, 0, currComm);

    // split array
    int midIndex, lowLen, highLen;
    q_utils.split(currBuffer, currBufferSize, pivot, midIndex, lowLen, highLen);

    // determine details for this communication
    bool shouldPassLargerList = h_utils.shouldPassLargerList(iteration, rank);
    int commLink = h_utils.getCommLink(iteration, rank);
    int recvLen;

    // send size
    if (shouldPassLargerList) {
      MPI_Sendrecv(&highLen, 1, MPI_INT, commLink, 0, &recvLen, 1, MPI_INT, commLink, 0, MPI_COMM_WORLD, NULL);
    } else {
      MPI_Sendrecv(&lowLen, 1, MPI_INT, commLink, 0, &recvLen, 1, MPI_INT, commLink, 0, MPI_COMM_WORLD, NULL);
    }

    // initialize new array
    int keepLen = shouldPassLargerList ? lowLen : highLen;
    int *recvBuffer;
    recvBuffer = new int [recvLen + keepLen];

    // send array
    if (shouldPassLargerList) {
      MPI_Sendrecv(&currBuffer[midIndex], highLen, MPI_INT, commLink, 1, recvBuffer, recvLen, MPI_INT, commLink, 1, MPI_COMM_WORLD, NULL);
    } else {
      MPI_Sendrecv(currBuffer, lowLen, MPI_INT, commLink, 1, recvBuffer, recvLen, MPI_INT, commLink, 1, MPI_COMM_WORLD, NULL);
    }

    // copy array
    if (shouldPassLargerList) {
      memcpy(&recvBuffer[recvLen], currBuffer, lowLen * sizeof(int));
    } else {
      memcpy(&recvBuffer[recvLen], &currBuffer[midIndex], highLen * sizeof(int));
    }

    delete[] currBuffer;
    currBuffer = recvBuffer;
    currBufferSize = recvLen + keepLen;

    // split communicator
    MPI_Comm nextComm;
    int nextGroup = h_utils.getNextGroup(iteration, rank);
    MPI_Comm_split(currComm, nextGroup, rank, &nextComm);
    currComm = nextComm;
  }



  /**
   * Close up MPI
   */
  MPI_Finalize();
}