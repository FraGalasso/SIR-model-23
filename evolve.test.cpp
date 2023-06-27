#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "persona.hpp"

TEST_CASE("Testing Evolution with one element") {
  Stato S{};
  Persona p(0, 1, 0, S);
  std::vector<Persona> V;
  V.push_back(p);
  Popolazione pop{V};
  pop.evolve();
  Persona p1 = pop.GetPerson(0);
  CHECK(p1.GetX() == 1);
  CHECK(p.GetX() == 0);
};

TEST_CASE("Testing Evolution with three elements") {
  Stato S{};
  Persona p(29, 0, 1, S);
  Persona q(99, 1, -1, S);
  Persona b(98, 1, 1, S);
  std::vector<Persona> V;
  V = {p, q, b};
  Popolazione pop{V};
  pop.evolve();
  Persona p1 = pop.GetPerson(0);
  Persona q1 = pop.GetPerson(1);
  Persona b1 = pop.GetPerson(2);
  CHECK(p1.GetX() == 19);
  CHECK(q1.GetX() == 0);
  CHECK(b1.GetX() == 89);
};

 TEST_CASE("Testing Evolution twice") {
  Stato S{};
  Persona p(29, 0, 1, S);
  Persona q(99, 1, -1, S);
  Persona b(98, 1, 1, S);
  std::vector<Persona> V;
  V = {p, q, b};
  Popolazione pop{V};
  pop.evolve();
  pop.evolve();
  Persona p1 = pop.GetPerson(0);
  Persona q1 = pop.GetPerson(1);
  Persona b1 = pop.GetPerson(2);
  CHECK(p1.GetX() == 9);
  CHECK(q1.GetX() == 11);
  CHECK(b1.GetX() == 70);
};
