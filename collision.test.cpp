#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "persona.hpp"

TEST_CASE("Testing Evolution with one element") {
  Stato S{};
  
  Persona p(1, -1, 0, S, 0);
  Persona q(9, 1, 0, S, 0);
  Persona d(10, 0, 1, S, 0);
  Persona c(90,0,-1,S,0);
  std::vector<Persona> V;
  V = {p, d, q, c};
  Popolazione pop{V};
  pop.evolve();
 // pop.collision();
  pop.evolve();

 
  Persona p1 = pop.GetPerson(0);
  Persona d1 = pop.GetPerson(1);
  Persona q1 = pop.GetPerson(2);
  Persona c1 = pop.GetPerson(3);
  CHECK(p1.GetX() == 1);
  CHECK(p1.GetPx()==1);
  CHECK(d1.GetX() == 10);
  CHECK(d1.GetPx()==0);
  CHECK(d1.GetPy()== -1);
  CHECK(q1.GetX() == 9);
  CHECK(q1.GetPx()==-1);
  CHECK(c1.GetX()==90);
  CHECK(c1.GetPy()==1);
  CHECK(q1.GetCollision()==0);
};
