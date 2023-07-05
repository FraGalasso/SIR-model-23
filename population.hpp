#ifndef POPULATION_HPP
#define POPULATION_HPP

#include <SFML/Graphics.hpp>
#include <stdexcept>
#include <vector>

#include "persona.hpp"

class Popolazione {
 private:
  std::vector<Persona> v;
  const double beta;
  const double gamma;
  // percentage of deaths before vaccination starts
  // if there is no vaccination it is set to 1 (it never starts)
  const double vaccination_campaign;
  const int original_size;
  int total_susceptibles;

 public:
  Popolazione(std::vector<Persona> V, double b, double g, double vax)
      : v{V},
        beta{b},
        gamma{g},
        vaccination_campaign{vax},
        original_size{static_cast<int>(V.size())} {
    if (b < 0 || b > 1) {
      throw std::runtime_error{"Not a valid beta."};
    }
    if (g < 0 || g > 1) {
      throw std::runtime_error{"Not a valid gamma."};
    }
    if (vax < 0 || vax > 1) {
      throw std::runtime_error{
          "Not a valid percentage for vaccination campaign."};
    }
    int counter = 0;
    for (int j = 0; j < static_cast<int>(V.size()); ++j) {
      if (v[j].GetStatus() == Stato::s) {
        ++counter;
      }
    }
    total_susceptibles = counter;
  };

  // useful with no vaccination
  Popolazione(std::vector<Persona> V, double b, double g)
      : Popolazione(V, b, g, 1.){};

  Persona GetPerson(int i) const { return v[i]; }

  double GetBeta() const { return beta; }

  double GetGamma() const { return gamma; }

  int GetSusceptibles() const { return total_susceptibles; }

  int GetInfectious() const {
    return static_cast<int>(v.size()) - total_susceptibles;
  }

  int GetRemoved() const { return original_size - static_cast<int>(v.size()); }

  int size() { return v.size(); }

  void evolve();

  void infection();

  void vaccination();

  void death(std::vector<int> d) {
    for (int i = static_cast<int>(d.size()) - 1; i >= 0; --i) {
      auto it = v.begin() + d[i];
      v.erase(it);
    }
  }
};

#endif