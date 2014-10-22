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
      testArray[i] = rand() % 100;
    }
    pivot = utils.choosePivot(testArray, length);
    BOOST_ASSERT(pivot >= 0);
    BOOST_ASSERT(pivot <= 99);
  }
}

BOOST_AUTO_TEST_CASE(choosePivotWorksWithDoubleTest) {
  QuicksortUtils utils;
  double testArray[4] = {2.2, 3.3, 4.4, 5.5};

  for (int i = 0; i < 10; i++) {
    double pivot = utils.choosePivot(testArray, 4);
    BOOST_ASSERT(pivot >= 0);
    BOOST_ASSERT(pivot <= 3);
  }
}

BOOST_AUTO_TEST_CASE(concreteSplitTest) {
  QuicksortUtils utils;
  int testList[4] = {0, 1, 2, 3};
  int lowLen, highLen, midIndex;
  utils.split(testList, 4, 2, midIndex, lowLen, highLen);
  BOOST_ASSERT(testList[midIndex] == 2);
  BOOST_ASSERT(testList[0] == 0);
}

BOOST_AUTO_TEST_CASE(concreteSplitTestTwo) {
  QuicksortUtils utils;
  int testList[10] = {0, 4, 6, 2, 1, 7, 9, 8, 3, 5};
  int midIndex, lowLen, highLen, pivot = 9;
  utils.split(testList, 10, pivot, midIndex, lowLen, highLen);
  BOOST_ASSERT(testList[midIndex] == 5);
  BOOST_ASSERT(highLen == 5);
  BOOST_ASSERT(lowLen == 5);
  for (int i = 0; i < midIndex; i++) {
    BOOST_ASSERT(testList[i] < testList[midIndex]);
  }
  for (int i = midIndex; i < 10; i++) {
    BOOST_ASSERT(testList[i] >= testList[midIndex]);
  }
}

BOOST_AUTO_TEST_CASE(concreteSplitTestThree) {
  QuicksortUtils utils;
  int testList[10] = {0, 4, 6, 2, 1, 7, 9, 8, 3, 5};
  int midIndex, lowLen, highLen, pivot = 8;
  utils.split(testList, 10, pivot, midIndex, lowLen, highLen);
  BOOST_ASSERT(testList[midIndex] == 3);
  BOOST_ASSERT(highLen == 7);
  BOOST_ASSERT(lowLen == 3);
}

BOOST_AUTO_TEST_CASE(concreteSplitTestFour) {
  QuicksortUtils utils;
  int testList[3] = {3, 3, 3};
  int midIndex, lowLen, highLen, pivot = 1;
  utils.split(testList, 3, pivot, midIndex, lowLen, highLen);
  BOOST_ASSERT(midIndex == 1);
  BOOST_ASSERT(highLen == 2);
  BOOST_ASSERT(lowLen == 1);
}

BOOST_AUTO_TEST_CASE(randomSplitTest) {
  QuicksortUtils utils;
  int midIndex, lowLen, highLen, length = 100, pivot = 0, midVal;
  int testList[length];
  int *lowList, *highList;
  for (int i = 0; i < 100; i++) {
    for (int j = 0; j < length; j++) {
      testList[j] = rand() % 100;
    }
    utils.split(testList, length, pivot, midIndex, lowLen, highLen);
    lowList = &testList[0];
    highList = &testList[midIndex];
    midVal = testList[midIndex];
    for (int j = 0; j < lowLen; j++) {
      BOOST_ASSERT(lowList[j] < midVal);
    }
    for (int j = 0; j < highLen; j++) {
      BOOST_ASSERT(highList[j] >= midVal);
    }
  }
}
