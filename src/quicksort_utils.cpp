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
   * @param {Type} list The list that we are sorting.  Type must implement addition and division.
   * @param {int} length The length of the list we are sorting
   * @return {int} The chosen pivot
   */
  template <typename Type>
  Type choosePivot (Type list[], int length) {
    Type firstSample = list[rand() % length];
    Type secondSample = list[rand() % length];
    Type thirdSample = list[rand() % length];
    Type pivot = (firstSample + secondSample + thirdSample) / 3;
    return pivot;
  }


  /**
   * Splits a list on a pivot
   *
   * @param {Type} list The list to split.
   * @param {int} length The length of the list
   * @param {Type} pivot The pivot to split on
   * @param {Type[]} lowArray The resulting lower array
   * @param {Type[]} highArray The resulting higher array
   * @param {int} lowArrayLength The resulting lower array length
   * @param {int} highArrayLength The resulting higher array length
   */
  template <typename Type>
  void splitList (Type list[], int length, Type pivot, Type lowArray[], Type highArray[], int &lowArrayLength, int &highArrayLength) {
    lowArrayLength = 0;
    highArrayLength = 0;
    for (int i = 0; i < length; i++) {
      if (list[i] < pivot) {
        lowArray[lowArrayLength] = list[i];
        lowArrayLength += 1;
      } else {
        highArray[highArrayLength] = list[i];
        highArrayLength += 1;
      }
    }
  }



};