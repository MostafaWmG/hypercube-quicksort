#include <stdlib.h>
#include <time.h>

class QuicksortUtils {
  
public:

  QuicksortUtils () {
    srand(time(NULL));
  }

  /**
   * Chooses a pivot using the median-of-three
   * method
   *
   * @param {generic} list The list that we are sorting.  Type must implement addition and division.
   * @param {int} length The length of the list we are sorting
   */
  template <typename Type>
  Type choosePivot (Type list[], int length) {
    Type firstSample = list[rand() % length];
    Type secondSample = list[rand() % length];
    Type thirdSample = list[rand() % length];
    Type pivot = (firstSample + secondSample + thirdSample) / 3;
    return pivot;
  }

};