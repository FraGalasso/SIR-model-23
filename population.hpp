#ifndef POPULATION_HPP
#define POPULATION_HPP

#include <SFML/Graphics.hpp>
#include <vector>

#include "person.hpp"

class Population {
 private:
  // vector containing all the people
  std::vector<Person> people;

  // probability of infection
  const double beta;

  // probability of death, if infectious
  const double gamma;

  // percentage of deaths before vaccination starts
  // if there is no vaccination it is set to 1 (it never starts)
  const double vaccination_campaign;

  // starting number of people
  const int original_size;

  // (updating) susceptibles counter
  int total_susceptibles;

 public:
  // constructor, defined at line 6 of population.cpp
  Population(std::vector<Person> V, double b, double g, double vax);

  // constructor with no vaccination, useful for tests, defined at line 34 of
  // population.cpp
  Population(std::vector<Person> V, double b, double g);

  // getting i-th person, defined at line 37 of population.cpp
  Person get_person(int i) const;

  // getting beta, defined at line 39 of population.cpp
  double get_beta() const;

  // getting gamma, defined at line 41 of population.cpp
  double get_gamma() const;

  // getting current number of susceptibles, defined at line 43 of
  // population.cpp
  int get_susceptibles() const;

  // getting current number of infectious, defined at line 45 of population.cpp
  int get_infectious() const;

  // getting current number of removed, defined at line 49 of population.cpp
  int get_removed() const;

  // getting current number of alive people, defined at line 53 of
  // population.cpp
  int size();

  // moving randomly people in the grid (one step), processing infections and
  // vaccinations once , defined at line 55 of population.cpp
  void evolve();

  // computing just infections, defined at line 109 of population.cpp
  void infection();

  // computing just vaccinations, defined at line 170 of population.cpp
  void vaccination();

  // removing people, based on a vector of indexes, defined at line 188 of
  // population.cpp
  void death(std::vector<int> d);
};

#endif