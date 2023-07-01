#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "persona.hpp"

TEST_CASE("Testing only gamma") {
  double counter = 0;
  for (int i = 0; i < 100000; ++i) {
    Persona p(1, -1, 0, Stato::i);
    Popolazione pop{{p}};
    Parameter par{1, 0.25};
    pop.evolve(par);

    if (pop.GetPerson(0).GetStatus() == Stato::r) {
      ++counter;
    }
  }

  CHECK((counter / 100000) == doctest::Approx(0.25).epsilon(0.005));
};

TEST_CASE("Testing only beta") {
  double counter = 0;
  for (int i = 0; i < 100000; ++i) {
    Persona p(1, -1, 0, Stato::s);
    Persona q(9, 1, 0, Stato::i);
    Popolazione pop{{p, q}};
    Parameter par{0.3, 0};
    pop.evolve(par);
    pop.evolve(par);

    if (pop.GetPerson(0).GetStatus() == Stato::i) {
      ++counter;
    }
  }

  CHECK((counter / 100000) == doctest::Approx(0.3).epsilon(0.005));
};

TEST_CASE("Testing beta and gamma") {
  double counter1p = 0;
  double counter2p = 0;
  double counterq = 0;
  for (int i = 0; i < 100000; ++i) {
    Persona p(1, -1, 0, Stato::s);
    Persona q(9, 1, 0, Stato::i);
    Popolazione pop{{p, q}};
    Parameter par{0.5, 0.5};
    pop.evolve(par);
    pop.evolve(par);

    if (pop.GetPerson(0).GetStatus() == Stato::s) {
      ++counter1p;
    }
    if (pop.GetPerson(0).GetStatus() == Stato::r) {
      ++counter2p;
    }
    if (pop.GetPerson(1).GetStatus() == Stato::r) {
      ++counterq;
    }
  }

  CHECK((counter1p / 100000) == doctest::Approx(0.75).epsilon(0.005));
  CHECK((counter2p / 100000) == doctest::Approx(0.125).epsilon(0.005));
  CHECK((counterq / 100000) == doctest::Approx(0.75).epsilon(0.005));
};
