#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "persona.hpp"

TEST_CASE("Testing only gamma") {
  double counter = 0;
  for (int i = 0; i < 100000; ++i) {
    Persona p(1, -1, 0, Stato::i);
    Popolazione pop{{p}, 1, 0.25, 1};
    pop.evolve();

    if (pop.size() == 0) {
      ++counter;
    }
  }

  CHECK((counter / 100000) == doctest::Approx(0.25).epsilon(0.005));
};

TEST_CASE("Testing only beta") {
  double counter = 0;
  for (int i = 0; i < 100000; ++i) {
    Persona p(1, 0, 0, Stato::s);
    Persona q(1, 0, 0, Stato::i);
    Popolazione pop{{p, q}, 0.3, 0, 1};
    pop.infection();

    if (pop.GetPerson(0).GetStatus() == Stato::i) {
      ++counter;
    }
  }

  CHECK((counter / 100000) == doctest::Approx(0.3).epsilon(0.005));
};