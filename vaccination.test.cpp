#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "person.hpp"
#include "population.hpp"

TEST_CASE("Testing Vaccination") {
  double counter = 0;

  std::vector<Person> people;
  for (int j = 0; j < 1000; ++j) {
    Person p{j, 0, 0, Status::s};
    people.push_back(p);
  }
  Population pop{people, 0, 0, 0};
  pop.vaccination();

  for (int i = 0; i < 1000; ++i) {
    if (pop.get_person(i).get_vaccination() == true) {
      ++counter;
    }
  }

  CHECK(counter == 10);

  counter = 0;

  pop.vaccination();

  for (int i = 0; i < 1000; ++i) {
    if (pop.get_person(i).get_vaccination() == true) {
      ++counter;
    }
  }

  CHECK(counter == 20);
};