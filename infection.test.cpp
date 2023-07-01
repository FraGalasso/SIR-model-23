#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "persona.hpp"

TEST_CASE("Testing Evolution with three elements") {
  Stato S{Stato::s};
  Stato I{Stato::i};
  Stato R{Stato::r};
  Persona p(1, -1, 0, S);
  Persona q(9, 1, 0, S);
  Persona d(10, 0, 1, I);
  std::vector<Persona> V;
  V = {p, d, q};
  Popolazione pop{V};
  Parameter par{0.6,0.1};
  pop.evolve(par);
 // pop.collision();
 //pop.infection();
  pop.evolve(par);
 
  Persona p1 = pop.GetPerson(0);
  Persona d1 = pop.GetPerson(1);
  Persona q1 = pop.GetPerson(2);
  CHECK(p1.GetX() == 1);
  CHECK(p1.GetPx()==1);
  CHECK(d1.GetX() == 10);
  CHECK(d1.GetPx()==0);
  CHECK(q1.GetX() == 9);
  CHECK(q1.GetPx()==-1);
  CHECK(p1.GetStatus()==R);
  CHECK(q1.GetStatus()==I);
  CHECK(d1.GetStatus()==I);
};
