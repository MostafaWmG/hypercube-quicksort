#define BOOST_TEST_MODULE Unit
#include <boost/test/included/unit_test.hpp>
#include "hypercube_utils.cpp"

BOOST_AUTO_TEST_CASE(getCommLinkTest) {
  HyperCubeUtils utils(3);

  // first iteration
  BOOST_CHECK(utils.getCommLink(1, 0) == 1);
  BOOST_CHECK(utils.getCommLink(1, 2) == 3);
  BOOST_CHECK(utils.getCommLink(1, 1) == 0);
  BOOST_CHECK(utils.getCommLink(1, 3) == 2);
  BOOST_CHECK(utils.getCommLink(1, 6) == 7);

  // second iteration
  BOOST_CHECK(utils.getCommLink(2, 0) == 2);
  BOOST_CHECK(utils.getCommLink(2, 1) == 3);
  BOOST_CHECK(utils.getCommLink(2, 3) == 1);
  BOOST_CHECK(utils.getCommLink(2, 4) == 6);
  BOOST_CHECK(utils.getCommLink(2, 5) == 7);
  BOOST_CHECK(utils.getCommLink(2, 7) == 5);

  // third iteration
  BOOST_CHECK(utils.getCommLink(3, 0) == 4);
  BOOST_CHECK(utils.getCommLink(3, 1) == 5);
  BOOST_CHECK(utils.getCommLink(3, 5) == 1);
  BOOST_CHECK(utils.getCommLink(3, 2) == 6);
  BOOST_CHECK(utils.getCommLink(3, 3) == 7);
  BOOST_CHECK(utils.getCommLink(3, 7) == 3);
}