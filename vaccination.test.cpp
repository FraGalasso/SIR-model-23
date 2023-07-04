#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "persona.hpp"

TEST_CASE("Testing Vaccination") {
  double counter = 0;

  std::vector<Persona> people;
  for (int j = 0; j < 100; ++j) {
    Persona p{j, 0, 0, Stato::s};
    people.push_back(p);
  }
  Popolazione pop{people, 0, 0, 0};
  pop.vaccination();

  for (int i = 0; i < pop.size(); ++i) {
    if (pop.GetPerson(i).GetVaccination() == true) {
      ++counter;
    }
  }

  CHECK(counter == 5);
};