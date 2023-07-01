#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "persona.hpp"

TEST_CASE("Testing Evolution with one element") {
  Persona p(0, 1, 0, Stato::s);
  Popolazione pop{{p}};
  pop.evolve();
  Persona p1 = pop.GetPerson(0);
  CHECK(p1.GetX() == 1);
  CHECK(p1.GetPx() == 1);
  CHECK(p1.GetPy() == 0);
};

TEST_CASE("Testing Evolution with three elements") {
  Persona p(29, 0, 1, Stato::s);
  Persona q(99, 1, -1, Stato::s);
  Persona b(98, 1, 1, Stato::s);
  Popolazione pop{{p, q, b}};
  pop.evolve();
  Persona p1 = pop.GetPerson(0);
  Persona q1 = pop.GetPerson(1);
  Persona b1 = pop.GetPerson(2);
  CHECK(p1.GetX() == 19);
  CHECK(p1.GetPx() == 0);
  CHECK(p1.GetPy() == 1);
  CHECK(q1.GetX() == 0);
  CHECK(q1.GetPx() == 1);
  CHECK(q1.GetPy() == -1);
  CHECK(b1.GetX() == 89);
  CHECK(b1.GetPx() == 1);
  CHECK(b1.GetPy() == 1);
};

TEST_CASE("Testing Evolution twice") {
  Persona p(29, 0, 1, Stato::s);
  Persona q(99, 1, -1, Stato::s);
  Persona b(98, 1, 1, Stato::s);
  Popolazione pop{{p, q, b}};
  pop.evolve();
  pop.evolve();
  Persona p1 = pop.GetPerson(0);
  Persona q1 = pop.GetPerson(1);
  Persona b1 = pop.GetPerson(2);
  CHECK(p1.GetX() == 9);
  CHECK(p1.GetPx() == 0);
  CHECK(p1.GetPy() == 1);
  CHECK(q1.GetX() == 11);
  CHECK(q1.GetPx() == 1);
  CHECK(q1.GetPy() == -1);
  CHECK(b1.GetX() == 70);
  CHECK(b1.GetPx() == 1);
  CHECK(b1.GetPy() == 1);
};