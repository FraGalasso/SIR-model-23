#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "persona.hpp"

TEST_CASE("Testing collisions") {
  Persona p(1, -1, 0, Stato::s);
  Persona q(9, 1, 0, Stato::s);
  Persona d(27, -1, 1, Stato::s);
  std::vector<Persona> V;
  V = {p, d, q};
  Popolazione pop{V};
  pop.evolve();
  pop.evolve();

  Persona p1 = pop.GetPerson(0);
  Persona d1 = pop.GetPerson(1);
  Persona q1 = pop.GetPerson(2);
  CHECK(p1.GetX() == 1);
  CHECK(p1.GetPx() == 1);
  CHECK(p1.GetPy() == 0);
  CHECK(d1.GetX() == 5);
  CHECK(d1.GetPx() == -1);
  CHECK(d1.GetPy() == 1);
  CHECK(q1.GetX() == 9);
  CHECK(q1.GetPx() == -1);
  CHECK(q1.GetPy() == 0);
};

// horrible fail
TEST_CASE("Testing triple collisions") {
  Persona p(1, -1, 0, Stato::s);
  Persona q(9, 1, 0, Stato::s);
  Persona d(11, -1, 1, Stato::s);
  Popolazione pop{{p, d, q}};
  pop.evolve();
  pop.evolve();

  Persona p1 = pop.GetPerson(0);
  Persona d1 = pop.GetPerson(1);
  Persona q1 = pop.GetPerson(2);
  CHECK(p1.GetX() == 1);
  CHECK(p1.GetPx() == 1);
  CHECK(p1.GetPy() == 0);
  CHECK(d1.GetX() == 11);
  CHECK(d1.GetPx() == 1);
  CHECK(d1.GetPy() == -1);
  CHECK(q1.GetX() == 9);
  CHECK(q1.GetPx() == -1);
  CHECK(q1.GetPy() == 0);
};

TEST_CASE("Testing quadruple collisions") {
  Persona p(1, -1, 0, Stato::s);
  Persona q(9, 1, 0, Stato::s);
  Persona d(11, -1, 1, Stato::s);
  Persona c(90, 0, -1, Stato::s);
  Popolazione pop{{p, d, q, c}};
  pop.evolve();
  pop.evolve();

  Persona p1 = pop.GetPerson(0);
  Persona d1 = pop.GetPerson(1);
  Persona q1 = pop.GetPerson(2);
  Persona c1 = pop.GetPerson(3);
  CHECK(p1.GetX() == 1);
  CHECK(p1.GetPx() == 1);
  CHECK(p1.GetPy() == 0);
  CHECK(d1.GetX() == 11);
  CHECK(d1.GetPx() == 1);
  CHECK(d1.GetPy() == -1);
  CHECK(q1.GetX() == 9);
  CHECK(q1.GetPx() == -1);
  CHECK(q1.GetPy() == 0);
  CHECK(c1.GetX() == 90);
  CHECK(c1.GetPx() == 0);
  CHECK(c1.GetPy() == 1);
};