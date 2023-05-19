#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "sir.hpp"

#include "doctest.h"

TEST_CASE("Testing correct construction") {
  SIR m(60, 5, 0);
  CHECK_THROWS_AS(SIR m(60, -5, 0), std::runtime_error);
}

TEST_CASE("Testing getters and setters") {
  SIR m(60, 5, 0);
  CHECK(m.get_s() == 60);
  CHECK(m.get_i() == 5);
  CHECK(m.get_r() == 0);
  m.set_s(51);
  CHECK(m.get_s() == 51);
}

TEST_CASE("Testing == operator") {
  SIR m(60, 5, 0);
  SIR m1(60, 5, 0);
  SIR m2(60, 5);
  SIR m3(60, 1);
  CHECK((m == m1) == true);
  CHECK((m == m2) == true);
  CHECK((m == m3) == false);
}