#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <iostream>
#include <limits>
#include "quicksort_utils.cpp"
#include "hypercube_utils.cpp"

int main (int argc, const char *argv[]) {

  /**
   * Options
   */
  int length = 9999999; // number of items to sort
  QuicksortUtils q_utils;

  /**
   * Generate a large random array
   */
  srand(time(NULL));
  int *sortMe = new int[length];
  int *sortMeDupe = new int[length];
  int randomNum;
  int intMax = std::numeric_limits<int>::max();
  for (int i = 0; i < length; i++) {
    randomNum = rand();
    sortMe[i] = randomNum;
    sortMeDupe[i] = randomNum;
  }

  std::cout << "Generated two identical arrays of " << length << " integers between 0 and " << intMax << "\n";

  /**
   * Run sequential sort
   */
  struct timeval startTime, endTime;
  suseconds_t timeElapsed;
  std::cout << "Starting sequential quicksort \n";
  gettimeofday(&startTime, NULL);
  q_utils.sort(sortMe, length);
  gettimeofday(&endTime, NULL);
  timeElapsed = ((endTime.tv_sec - startTime.tv_sec) * 1000) + ((endTime.tv_usec - startTime.tv_usec) / 1000);
  std::cout << "Finished sequential quicksort in " << timeElapsed << " milliseconds\n";

}