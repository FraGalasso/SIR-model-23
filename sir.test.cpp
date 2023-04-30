#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "sir.hpp"

#include "doctest.h"

TEST_CASE("Testing getters and setters") {
  SIR m(60, 5, 0);
  CHECK(m.get_s() == 60);
  CHECK(m.get_i() == 5);
  CHECK(m.get_r() == 0);
  m.set_s(51);
  CHECK(m.get_s() == 51);
}