#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "person.hpp"
#include "population.hpp"

TEST_CASE("Testing only gamma") {
  double counter = 0;
  // given the probabilistic nature of death the same test is run multiple times
  for (int i = 0; i < 100000; ++i) {
    Person p(1, -1, 0, Status::i);
    Population pop{{p}, 1, 0.25, 1};
    pop.evolve();

    if (pop.size() == 0) {
      ++counter;
    }
  }

  CHECK((counter / 100000) == doctest::Approx(0.25).epsilon(0.005));
};

TEST_CASE("Testing only beta") {
  double counter = 0;
  // given the probabilistic nature of infection the same test is run multiple
  // times
  for (int i = 0; i < 100000; ++i) {
    Person p(1, 0, 0, Status::s);
    Person q(1, 0, 0, Status::i);
    Population pop{{p, q}, 0.3, 0, 1};
    pop.infection();

    if (pop.get_person(0).get_status() == Status::i) {
      ++counter;
    }
  }

  CHECK((counter / 100000) == doctest::Approx(0.3).epsilon(0.005));
};