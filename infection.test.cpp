#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "persona.hpp"

TEST_CASE("Testing simple infection") {
  Stato S{Stato::s};
  Stato I{Stato::i};
  Persona p(1, -1, 0, I);
  Persona q(9, 1, 0, S);
  Persona d(27, -1, 1, S);
  Popolazione pop{{p, d, q}};
  pop.evolve();
  pop.evolve();
 
  Persona p1 = pop.GetPerson(0);
  Persona d1 = pop.GetPerson(1);
  Persona q1 = pop.GetPerson(2);
  CHECK(p1.GetX() == 1);
  CHECK(p1.GetPx()==1);
  CHECK(d1.GetX() == 5);
  CHECK(d1.GetPx()==-1);
  CHECK(q1.GetX() == 9);
  CHECK(q1.GetPx()==-1);
  CHECK(p1.GetStatus()==I);
  CHECK(q1.GetStatus()==I);
  
};