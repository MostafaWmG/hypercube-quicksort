#include <boost/test/unit_test.hpp>
#include "hypercube_utils.cpp"

BOOST_AUTO_TEST_SUITE(HypercubeUtilsSuite);

BOOST_AUTO_TEST_CASE(getCommLinkTest) {
  HypercubeUtils utils(3);

  // first iteration
  BOOST_CHECK(utils.getCommLink(1, 0) == 4);
  BOOST_CHECK(utils.getCommLink(1, 1) == 5);
  BOOST_CHECK(utils.getCommLink(1, 5) == 1);
  BOOST_CHECK(utils.getCommLink(1, 2) == 6);
  BOOST_CHECK(utils.getCommLink(1, 3) == 7);
  BOOST_CHECK(utils.getCommLink(1, 7) == 3);

  // second iteration
  BOOST_CHECK(utils.getCommLink(2, 0) == 2);
  BOOST_CHECK(utils.getCommLink(2, 1) == 3);
  BOOST_CHECK(utils.getCommLink(2, 3) == 1);
  BOOST_CHECK(utils.getCommLink(2, 4) == 6);
  BOOST_CHECK(utils.getCommLink(2, 5) == 7);
  BOOST_CHECK(utils.getCommLink(2, 7) == 5);

  // third iteration
  BOOST_CHECK(utils.getCommLink(3, 0) == 1);
  BOOST_CHECK(utils.getCommLink(3, 4) == 5);
  BOOST_CHECK(utils.getCommLink(3, 2) == 3);
  BOOST_CHECK(utils.getCommLink(3, 1) == 0);
  BOOST_CHECK(utils.getCommLink(3, 3) == 2);
  BOOST_CHECK(utils.getCommLink(3, 6) == 7);
}

BOOST_AUTO_TEST_CASE(shouldPassLargerListTest) {
  HypercubeUtils utils(3);

  // first iteration
  BOOST_CHECK(utils.shouldPassLargerList(1, 0) == true);
  BOOST_CHECK(utils.shouldPassLargerList(1, 1) == true);
  BOOST_CHECK(utils.shouldPassLargerList(1, 2) == true);
  BOOST_CHECK(utils.shouldPassLargerList(1, 3) == true);
  BOOST_CHECK(utils.shouldPassLargerList(1, 4) == false);
  BOOST_CHECK(utils.shouldPassLargerList(1, 5) == false);
  BOOST_CHECK(utils.shouldPassLargerList(1, 6) == false);
  BOOST_CHECK(utils.shouldPassLargerList(1, 7) == false);

  // second iteration
  BOOST_CHECK(utils.shouldPassLargerList(2, 0) == true);
  BOOST_CHECK(utils.shouldPassLargerList(2, 1) == true);
  BOOST_CHECK(utils.shouldPassLargerList(2, 2) == false);
  BOOST_CHECK(utils.shouldPassLargerList(2, 3) == false);
  BOOST_CHECK(utils.shouldPassLargerList(2, 4) == true);
  BOOST_CHECK(utils.shouldPassLargerList(2, 5) == true);
  BOOST_CHECK(utils.shouldPassLargerList(2, 6) == false);
  BOOST_CHECK(utils.shouldPassLargerList(2, 7) == false);

  // third iteration
  BOOST_CHECK(utils.shouldPassLargerList(3, 0) == true);
  BOOST_CHECK(utils.shouldPassLargerList(3, 1) == false);
  BOOST_CHECK(utils.shouldPassLargerList(3, 2) == true);
  BOOST_CHECK(utils.shouldPassLargerList(3, 3) == false);
  BOOST_CHECK(utils.shouldPassLargerList(3, 4) == true);
  BOOST_CHECK(utils.shouldPassLargerList(3, 5) == false);
  BOOST_CHECK(utils.shouldPassLargerList(3, 6) == true);
  BOOST_CHECK(utils.shouldPassLargerList(3, 7) == false);
}

BOOST_AUTO_TEST_CASE(getNextGroupTest) {
  HypercubeUtils utils(3);

  // first iteration
  BOOST_CHECK(utils.getNextGroup(1, 0) == 0);
  BOOST_CHECK(utils.getNextGroup(1, 1) == 0);
  BOOST_CHECK(utils.getNextGroup(1, 2) == 0);
  BOOST_CHECK(utils.getNextGroup(1, 3) == 0);
  BOOST_CHECK(utils.getNextGroup(1, 4) == 1);
  BOOST_CHECK(utils.getNextGroup(1, 5) == 1);
  BOOST_CHECK(utils.getNextGroup(1, 6) == 1);
  BOOST_CHECK(utils.getNextGroup(1, 7) == 1);

  // second iteration);
  BOOST_CHECK(utils.getNextGroup(2, 0) == 0);
  BOOST_CHECK(utils.getNextGroup(2, 1) == 0);
  BOOST_CHECK(utils.getNextGroup(2, 2) == 1);
  BOOST_CHECK(utils.getNextGroup(2, 3) == 1);
  BOOST_CHECK(utils.getNextGroup(2, 4) == 0);
  BOOST_CHECK(utils.getNextGroup(2, 5) == 0);
  BOOST_CHECK(utils.getNextGroup(2, 6) == 1);
  BOOST_CHECK(utils.getNextGroup(2, 7) == 1);

  
}

BOOST_AUTO_TEST_SUITE_END();