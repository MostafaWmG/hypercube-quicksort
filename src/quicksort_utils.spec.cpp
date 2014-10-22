#include <boost/test/unit_test.hpp>
#include "quicksort_utils.cpp"

BOOST_AUTO_TEST_CASE(choosePivotTest) {
  srand(time(NULL));
  QuicksortUtils utils;
  int trials = 100;
  int length, min = 100, max = 0, random, pivot;
  for (int j = 0; j < trials; j++) {
    do {
      length = rand() % 100;
    } while (length == 0);
    int testArray [length];
    for (int i = 0; i < length; i++) {
      random = rand() % 100;
      testArray[i] = random;
      if (random < min) { min = random; }
      if (random > max) { max = random; }
    }
    pivot = utils.choosePivot(testArray, length);
    BOOST_ASSERT(pivot >= min);
    BOOST_ASSERT(pivot <= max);
  }
}

BOOST_AUTO_TEST_CASE(choosePivotWorksWithDoubleTest) {
  QuicksortUtils utils;
  double testArray[4] = {2.2, 3.3, 4.4, 5.5};

  for (int i = 0; i < 10; i++) {
    double pivot = utils.choosePivot(testArray, 4);
    BOOST_ASSERT(pivot >= 2.2);
    BOOST_ASSERT(pivot <= 5.5);
  }
}

BOOST_AUTO_TEST_CASE(concreteSplitListTest) {
  QuicksortUtils utils;
  int length = 10;
  int testArray[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  int lowArray[length];
  int highArray[length];
  int lowArrayLength = 0;
  int highArrayLength = 0;
  int pivot = 4;
  utils.splitList(testArray, length, pivot, lowArray, highArray, lowArrayLength, highArrayLength);
  BOOST_ASSERT(lowArrayLength == 4);
  BOOST_ASSERT(highArrayLength == 6);
  for (int i = 0; i < 4; i++) {
    BOOST_ASSERT(lowArray[i] < pivot);
  }
  for (int i = 0; i < 6; i++) {
    BOOST_ASSERT(highArray[i] >= pivot);
  }
}

BOOST_AUTO_TEST_CASE(randomSplitListTest) {
  srand(time(NULL));
  QuicksortUtils utils;
  int trials = 100;
  int length, pivot;
  for (int j = 0; j < trials; j++) {
    do {
      length = rand() % 100;
    } while (length == 0);
    pivot = length / 2;
    int testArray [length];
    for (int i = 0; i < length; i++) {
      testArray[i] = rand() % 100;
    }
    pivot = utils.choosePivot(testArray, length);
    int lowArray[length];
    int highArray[length];
    int lowArrayLength = 0;
    int highArrayLength = 0;
    utils.splitList(testArray, length, pivot, lowArray, highArray, lowArrayLength, highArrayLength);
    for (int i = 0; i < lowArrayLength; i++) {
      BOOST_ASSERT(lowArray[i] < pivot);
    }
    for (int i = 0; i < highArrayLength; i++) {
      BOOST_ASSERT(highArray[i] >= pivot);
    }
  }
}
