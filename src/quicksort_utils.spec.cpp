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