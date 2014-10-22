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
  int choosePivot (Type list[], int length) {
    int firstIndex = rand() % length;
    int secondIndex = rand() % length;
    int thirdIndex = rand() % length;
    Type firstSample = list[firstIndex];
    Type secondSample = list[secondIndex];
    Type thirdSample = list[thirdIndex];
    if (firstSample >= secondSample && firstSample < thirdSample) {
      return firstIndex;
    }
    if (secondSample >= firstSample && secondSample < thirdSample) {
      return secondIndex;
    }
    return thirdIndex;
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
  void split (Type list[], int length, int pivot, int &midIndex, int &lowLen, int &highLen) { 
    Type tmp;
    Type pivotValue = list[pivot];
    int currentIndex = 0;
    lowLen = 0;
    highLen = 0;
    tmp = list[pivot];
    list[pivot] = list[length-1];
    list[length-1] = tmp;
    for (int i = 0; i < length; i++) {
      if(list[i] < pivotValue) {
        tmp = list[currentIndex];
        list[currentIndex] = list[i];
        list[i] = tmp;
        currentIndex += 1;
      }
    }
    tmp = list[length-1];
    list[length-1] = list[currentIndex];
    list[currentIndex] = tmp;
    midIndex = currentIndex;
    highLen = length - currentIndex;
    lowLen = length - highLen;
    if (midIndex == 0) {
      midIndex = 1;
      lowLen += 1;
      highLen -= 1;
    }
  }



};