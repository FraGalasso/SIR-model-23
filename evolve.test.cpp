#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "parameters.hpp"
#include "sir.hpp"

// returns steps needed to get to result
int evolve(Parameters const& p, SIR& model, int const& steps) {
  SIR previous{};

  const int N{model.get_s() + model.get_i() + model.get_r()};

  if (N == 0) {
    return 1;
  }

  for (int j = 0; j < steps; ++j) {
    // computing floating-point values for s, i, r
    double s1{model.get_s() - p.beta * model.get_s() * model.get_i() / N};
    double i1{model.get_i() + p.beta * model.get_s() * model.get_i() / N -
              p.gamma * model.get_i()};
    double r1{model.get_r() + p.gamma * model.get_i()};

    // computing integer part
    int s{static_cast<int>(s1)};
    int i{static_cast<int>(i1)};
    int r{static_cast<int>(r1)};

    // separating decimal part
    s1 -= s;
    i1 -= i;
    r1 -= r;

    // equivalent to sum of decimal parts
    int diff{N - (s + i + r)};

    // distributing remainder from decimal parts, one step at a time
    while (diff > 0) {
      if (s1 >= i1 && s1 >= r1) {
        ++s;
        s1 = 0;
        --diff;
      } else if (i1 >= s1 && i1 >= r1) {
        ++i;
        i1 = 0;
        --diff;
      } else {
        ++r;
        r1 = 0;
        --diff;
      }
    }
    // at this point diff should be equal to 0

    previous.set_s(model.get_s());
    previous.set_i(model.get_i());
    previous.set_r(model.get_r());

    model.set_s(s);
    model.set_i(i);
    model.set_r(r);

    // no point in going on if I'm always starting from the same integers
    if (model == previous) {
      return j + 1;
    }
  }
  return steps;
}

// results of these test have been independently checked by authors

TEST_CASE("Testing no evolution") {
  SIR m(60, 5, 0);
  Parameters p{0.3, 0.7};
  CHECK(evolve(p, m, 0) == 0);
  CHECK(m.get_s() == 60);
  CHECK(m.get_i() == 5);
  CHECK(m.get_r() == 0);
}

TEST_CASE("Testing little evolution") {
  SIR m(60, 5, 0);
  Parameters p{0.3, 0.7};
  CHECK(evolve(p, m, 3) == 3);
  CHECK(m.get_s() == 58);
  CHECK(m.get_i() == 1);
  CHECK(m.get_r() == 6);
}

TEST_CASE("Testing early exit") {
  SIR m(60, 5, 0);
  Parameters p{0.3, 0.7};
  CHECK(evolve(p, m, 10) == 5);
  CHECK(m.get_s() == 58);
  CHECK(m.get_i() == 0);
  CHECK(m.get_r() == 7);
}

TEST_CASE("Testing no infection") {
  SIR m(60, 5, 0);
  Parameters p{0, 0};
  CHECK(evolve(p, m, 10) == 1);
  CHECK(m.get_s() == 60);
  CHECK(m.get_i() == 5);
  CHECK(m.get_r() == 0);
}

TEST_CASE("Testing no people") {
  SIR m(0, 0, 0);
  Parameters p{0.3, 0.7};
  CHECK(evolve(p, m, 10) == 1);
  CHECK(m.get_s() == 0);
  CHECK(m.get_i() == 0);
  CHECK(m.get_r() == 0);
}