#include <stdlib.h>
#include <time.h>

using namespace std;

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
      return firstSample;
    }
    if (secondSample >= firstSample && secondSample < thirdSample) {
      return secondSample;
    }
    return thirdSample;
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
  void split (Type list[], int length, Type pivot, int &midIndex, int &lowLen, int &highLen) { 
    int i = 0;
    lowLen = 0;
    while(list[i] <= pivot && i < length) {
      i += 1;
      lowLen += 1;
    }
    midIndex = i;
    while(i < length) {
      if(list[i] <= pivot) {
        Type tmp = list[i];
        list[i] = list[midIndex];
        list[midIndex] = tmp;
        midIndex += 1;
        lowLen += 1;
      }
      i += 1;
    }
    highLen = length - lowLen;
  }


  /**
   * Runs quicksort on a list
   *
   * @param {Type[]} list The list to sort
   * @param {int} length The length of the list we are sorting
   */
  template <typename Type>
  void sort (Type list[], int length) {
    if (length > 1) {
      bool same = true;
      for (int i = 0; i < length - 1; i++) {
        if (list[i] != list[i+1]) {
          same = false;
          break;
        }
      }
      if (same) { return; }
      Type pivot = choosePivot(list, length);
      int midIndex, lowLen, highLen;
      split(list, length, pivot, midIndex, lowLen, highLen);
      sort(list, lowLen);
      sort(&list[midIndex], highLen);
    }
  }

};