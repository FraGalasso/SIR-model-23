#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "persona.hpp"

TEST_CASE("Testing collisions") {
  Persona p(1, -1, 0, Stato::s, 0);
  Persona q(9, 1, 0, Stato::s, 0);
  Persona d(27, -1, 1, Stato::s, 0);
  Popolazione pop{{p, d, q}};
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
  Persona a(1, -1, 0, Stato::s, 0);
  Persona b(9, 1, 0, Stato::s, 0);
  Persona c(11, -1, 1, Stato::s, 0);
  Popolazione pop{{a, b, c}};
  pop.evolve();

  CHECK(pop.GetPerson(0).GetX() == 0);
  CHECK(pop.GetPerson(1).GetX() == 0);
  CHECK(pop.GetPerson(2).GetX() == 0);

  pop.evolve();

  Persona p0 = pop.GetPerson(0);
  Persona p1 = pop.GetPerson(1);
  Persona p2 = pop.GetPerson(2);
  CHECK(p0.GetX() == 1);
  CHECK(p0.GetPx() == 1);
  CHECK(p0.GetPy() == 0);
  CHECK(p1.GetX() == 9);
  CHECK(p1.GetPx() == -1);
  CHECK(p1.GetPy() == 0);
  CHECK(p2.GetX() == 11);
  CHECK(p2.GetPx() == 1);
  CHECK(p2.GetPy() == -1);
};

TEST_CASE("Testing quadruple collisions") {
  Persona a(1, -1, 0, Stato::s, 0);
  Persona b(9, 1, 0, Stato::s, 0);
  Persona c(11, -1, 1, Stato::s, 0);
  Persona d(90, 0, -1, Stato::s, 0);
  Popolazione pop{{a, b, c, d}};
  pop.evolve();

  CHECK(pop.GetPerson(0).GetX() == 0);
  CHECK(pop.GetPerson(1).GetX() == 0);
  CHECK(pop.GetPerson(2).GetX() == 0);
  CHECK(pop.GetPerson(3).GetX() == 0);

  pop.evolve();

  Persona p0 = pop.GetPerson(0);
  Persona p1 = pop.GetPerson(1);
  Persona p2 = pop.GetPerson(2);
  Persona p3 = pop.GetPerson(3);
  CHECK(p0.GetX() == 1);
  CHECK(p0.GetPx() == 1);
  CHECK(p0.GetPy() == 0);
  CHECK(p1.GetX() == 9);
  CHECK(p1.GetPx() == -1);
  CHECK(p1.GetPy() == 0);
  CHECK(p2.GetX() == 11);
  CHECK(p2.GetPx() == 1);
  CHECK(p2.GetPy() == -1);
  CHECK(p3.GetX() == 90);
  CHECK(p3.GetPx() == 0);
  CHECK(p3.GetPy() == 1);
};