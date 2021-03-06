#include <boost/test/unit_test.hpp>
#include "quicksort_utils.cpp"

BOOST_AUTO_TEST_CASE(choosePivotTest) {
  srand(time(NULL));
  QuicksortUtils utils;
  int testArray[8] = {0,1,2,3,4,5,6,7};
  utils.choosePivot(testArray, 8);
}

BOOST_AUTO_TEST_CASE(splitTTTest) {
  srand(time(NULL));
  QuicksortUtils utils;
  int testArray[8] = {1, 5, 3, 5, 6, 2, 3, 6};
  for (int j = 0; j < 100; j++) {
    int pivot = rand() % 6;
    int midIndex, highLen, lowLen;
    utils.split(testArray, 8, pivot, midIndex, highLen, lowLen);
    for (int i = 0; i < midIndex; i++) {
      BOOST_ASSERT(testArray[i] <= pivot);
    }
    for (int i = midIndex; i < 8; i++) {
      BOOST_ASSERT(testArray[i] > pivot);
    }
  }
}

BOOST_AUTO_TEST_CASE(splitTest) {
  srand(time(NULL));
  QuicksortUtils utils;
  for (int i = 0; i < 100; i++) {
    int testArray[100];
    int pivot = rand() % 100;
    int midIndex, highLen, lowLen;
    for (int j = 0; j < 100; j++) {
      testArray[j] = rand() % 100;
    }
    utils.split(testArray, 100, pivot, midIndex, highLen, lowLen);
    for (int j = 0; j < midIndex; j++) {
      BOOST_ASSERT(testArray[j] <= pivot);
    }
    for (int j = midIndex; j < 100; j++) {
      BOOST_ASSERT(testArray[j] > pivot);
    }
  }
}

BOOST_AUTO_TEST_CASE(splitteyTester) {
  QuicksortUtils utils;
  int testArray[4] = {3, 5, 5, 3};
  int midIndex, highLen, lowLen;
  utils.split(testArray, 4, 3, midIndex, highLen, lowLen);
  BOOST_ASSERT(testArray[0] == 3);
  BOOST_ASSERT(testArray[1] == 3);
  BOOST_ASSERT(testArray[2] == 5);
  BOOST_ASSERT(testArray[3] == 5);
}

BOOST_AUTO_TEST_CASE(sorterz) {
  QuicksortUtils utils;
  srand(time(NULL));
  int testArray[4] = {3, 5, 5, 3};
  utils.sort(testArray, 4);
  BOOST_ASSERT(testArray[0] == 3);
  BOOST_ASSERT(testArray[1] == 3);
  BOOST_ASSERT(testArray[2] == 5);
  BOOST_ASSERT(testArray[3] == 5);
}

BOOST_AUTO_TEST_CASE(splittz) {
  QuicksortUtils utils;
  int testArray[6] = {3, 5, 6, 5, 3, 6};
  int midIndex, highLen, lowLen;
  utils.split(testArray, 6, 5, midIndex, highLen, lowLen);
  for (int i = 0; i < midIndex; i++) {
    BOOST_ASSERT(testArray[i] <= 5);
  }
  for (int i = midIndex; i < 6; i++) {
    BOOST_ASSERT(testArray[i] > 5);
  }
  BOOST_ASSERT(midIndex == 4);
}

BOOST_AUTO_TEST_CASE(sortTest) {
  srand(time(NULL));
  QuicksortUtils utils;
  for (int j = 0; j < 100; j++) {
    int testArray[8] = {1, 5, 3, 5, 6, 2, 3, 6};
    int sortedArray[8] = {1, 2, 3, 3, 5, 5, 6, 6};
    utils.sort(testArray, 8);
    for (int i = 0; i < 8; i++) {
      BOOST_ASSERT(testArray[i] == sortedArray[i]);
    }
  }
}

// BOOST_AUTO_TEST_CASE(choosePivotTest) {
//   srand(time(NULL));
//   QuicksortUtils utils;
//   int trials = 100;
//   int length, min = 100, max = 0, random, pivot;
//   for (int j = 0; j < trials; j++) {
//     do {
//       length = rand() % 100;
//     } while (length == 0);
//     int testArray [length];
//     for (int i = 0; i < length; i++) {
//       testArray[i] = rand() % 100;
//     }
//     pivot = utils.choosePivot(testArray, length);
//     BOOST_ASSERT(pivot >= 0);
//     BOOST_ASSERT(pivot <= 99);
//   }
// }

// BOOST_AUTO_TEST_CASE(choosePivotWorksWithDoubleTest) {
//   QuicksortUtils utils;
//   double testArray[4] = {2.2, 3.3, 4.4, 5.5};

//   for (int i = 0; i < 10; i++) {
//     double pivot = utils.choosePivot(testArray, 4);
//     BOOST_ASSERT(pivot >= 0);
//     BOOST_ASSERT(pivot <= 3);
//   }
// }

// BOOST_AUTO_TEST_CASE(concreteSplitTest) {
//   QuicksortUtils utils;
//   int testList[4] = {0, 1, 2, 3};
//   int lowLen, highLen, midIndex;
//   utils.split(testList, 4, 2, midIndex, lowLen, highLen);
//   BOOST_ASSERT(testList[midIndex] == 2);
//   BOOST_ASSERT(testList[0] == 0);
// }

// BOOST_AUTO_TEST_CASE(concreteSplitTestTwo) {
//   QuicksortUtils utils;
//   int testList[10] = {0, 4, 6, 2, 1, 7, 9, 8, 3, 5};
//   int midIndex, lowLen, highLen, pivot = 9;
//   utils.split(testList, 10, pivot, midIndex, lowLen, highLen);
//   BOOST_ASSERT(testList[midIndex] == 5);
//   BOOST_ASSERT(highLen == 5);
//   BOOST_ASSERT(lowLen == 5);
//   for (int i = 0; i < midIndex; i++) {
//     BOOST_ASSERT(testList[i] < testList[midIndex]);
//   }
//   for (int i = midIndex; i < 10; i++) {
//     BOOST_ASSERT(testList[i] >= testList[midIndex]);
//   }
// }

// BOOST_AUTO_TEST_CASE(concreteSplitTestThree) {
//   QuicksortUtils utils;
//   int testList[10] = {0, 4, 6, 2, 1, 7, 9, 8, 3, 5};
//   int midIndex, lowLen, highLen, pivot = 8;
//   utils.split(testList, 10, pivot, midIndex, lowLen, highLen);
//   BOOST_ASSERT(testList[midIndex] == 3);
//   BOOST_ASSERT(highLen == 7);
//   BOOST_ASSERT(lowLen == 3);
// }

// BOOST_AUTO_TEST_CASE(concreteSplitTestFour) {
//   QuicksortUtils utils;
//   int testList[3] = {3, 3, 3};
//   int midIndex, lowLen, highLen, pivot = 1;
//   utils.split(testList, 3, pivot, midIndex, lowLen, highLen);
//   BOOST_ASSERT(midIndex == 1);
//   BOOST_ASSERT(highLen == 2);
//   BOOST_ASSERT(lowLen == 1);
// }

// BOOST_AUTO_TEST_CASE(concreteSortTest) {
//   QuicksortUtils utils;
//   int length = 10;
//   int testList[10] = {0, 4, 6, 2, 1, 7, 9, 8, 3, 5};
//   utils.sort(testList, length);
//   for (int i = 0; i < length; i++) {
//     BOOST_ASSERT(testList[i] == i);
//   }
// }

// BOOST_AUTO_TEST_CASE(concreteSortTestTwo) {
//   QuicksortUtils utils;
//   int length = 5, testList[5] = {2, 0, 2, 4, 2};
//   utils.sort(testList, 5);
//   BOOST_ASSERT(testList[0] == 0);
//   BOOST_ASSERT(testList[1] == 2);
//   BOOST_ASSERT(testList[2] == 2);
//   BOOST_ASSERT(testList[3] == 2);
//   BOOST_ASSERT(testList[4] == 4);
// }

// BOOST_AUTO_TEST_CASE(randomSortTest) {
//   srand(time(NULL));
//   QuicksortUtils utils;
//   int length = 100, current;
//   int testList[length];
//   for (int i = 0; i < length; i++) {
//     for (int j = 0; j < length; j++) {
//       testList[j] = rand() % 100;
//     }
//     utils.sort(testList, length);
//     current = 0;
//     for (int j = 0; j < length; j++) {
//       BOOST_ASSERT(testList[j] >= current);
//       current = testList[j];
//     }
//   }
// }
