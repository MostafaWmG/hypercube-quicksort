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
  int rank, size, hypercubeDimensions, *sortMe = new int[length], MASTER = 0;
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
  int e = 1;
  int sizee;
  sizee = pow(2, e);
  while (sizee < size) {
    e += 1;
    sizee = pow(2, e);
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
  hypercubeDimensions = e;
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
  int receiveBuffer[scatter_sizes[rank]];
  MPI_Scatterv(sortMe, scatter_sizes, scatter_offsets, MPI_INT, &receiveBuffer, scatter_sizes[rank], MPI_INT, MASTER, MPI_COMM_WORLD);
  cout << rank << ": Received array ";
  printBuffer(receiveBuffer, scatter_sizes[rank]);
  cout << endl;


  /**
   * Initialize compare & exchange loop
   */
  hypercubeDimensions = 1;
  MPI_Comm currentComm = MPI_COMM_WORLD;
  int currRank = rank;
  for (int iteration = 1; iteration <= hypercubeDimensions; iteration++) {

    /**
     * Broadcast pivot
     */
    int pivot;
    if (currRank == MASTER) {
      pivot = q_utils.choosePivot(receiveBuffer, scatter_sizes[currRank]);
      cout << "0: chose pivot as " << pivot << endl;
    }
    MPI_Bcast(&pivot, 1, MPI_INT, MASTER, currentComm);

    /**
     * Split list
     */
    int midIndex;
    int lowLen;
    int highLen;
    q_utils.split(receiveBuffer, scatter_sizes[currRank], pivot, midIndex, lowLen, highLen);
    cout << rank << ": lowlist ";
    printBuffer(receiveBuffer, lowLen);
    cout << ", highlist ";
    printBuffer(&receiveBuffer[midIndex], highLen);
    cout << ", highlen " << highLen << ", lowlen " << lowLen;
    cout << endl;

    /**
     * Compare & exchange
     */
    int rankToExchangeWith = h_utils.getCommLink(iteration, rank);
    bool shouldPassLargeList = h_utils.shouldPassLargerList(iteration, rank);
    int sendLen = shouldPassLargeList ? highLen : lowLen;
    int keepLen = shouldPassLargeList ? lowLen : highLen;
    int *keepStart = shouldPassLargeList ? receiveBuffer : &receiveBuffer[midIndex];
    int *sendStart = shouldPassLargeList ? &receiveBuffer[midIndex] : receiveBuffer;
    int recvLen;
    int tag1 = 1;
    int tag2 = 2;
    MPI_Sendrecv(&sendLen, 1, MPI_INT, rankToExchangeWith, tag1, &recvLen, 1, MPI_INT, rankToExchangeWith, tag1, currentComm, NULL);
    int receiveArray[recvLen + keepLen];
    MPI_Sendrecv(sendStart, sendLen, MPI_INT, rankToExchangeWith, tag2, receiveArray, recvLen, MPI_INT, rankToExchangeWith, tag2, currentComm, NULL);
    for (int i = 0; i < keepLen; i++) {
      receiveArray[recvLen + i] = keepStart[i];
    }
    cout << rank << ": received array ";
    printBuffer(receiveArray, recvLen + keepLen);
    cout << " from " << rankToExchangeWith << endl;

    /**
     * Divide communicator
     */
     
  }


  /**
   * Close up MPI
   */
  MPI_Finalize();
}