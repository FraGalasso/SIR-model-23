#ifndef PERSONA_HPP
#define PERSONA_HPP

#include <SFML/Graphics.hpp>
#include <stdexcept>
#include <vector>

enum class Stato { s, i };

class Persona {
 private:
  int x;
  int px, py;
  Stato s;
  bool is_vaccinated = false;
  sf::RectangleShape dot = sf::RectangleShape(sf::Vector2f(6, 6));

 public:
  Persona(int X, int Px, int Py, Stato S) : x{X}, px{Px}, py{Py}, s{S} {
    if (s == Stato::s) {
      dot.setFillColor(sf::Color::Green);
    } else if (s == Stato::i) {
      dot.setFillColor(sf::Color::Red);
    }
    UpdateDotPosition();
  };
  int GetX() const { return x; }
  int GetPx() const { return px; }
  int GetPy() const { return py; }
  Stato GetStatus() const { return s; }
  bool GetVaccination() const { return is_vaccinated; }
  sf::RectangleShape GetDot() const { return dot; }
  void SetX(int y) { x = y; }
  void SetPx(int p) { px = p; }
  void SetPy(int p) { py = p; }
  void SetStatus(Stato z) { s = z; }
  void Vaccine() {
    is_vaccinated = true;
    if (s == Stato::s) {
      dot.setFillColor(sf::Color::Blue);
    }
  }
  void UpdateDotPosition() {
    int posx = 6 + 18 * (x % 40);
    int posy = 6 + 18 * (x / 40);
    if (px == 1) {
      posx -= 6;
    } else if (px == -1) {
      posx += 6;
    }
    if (py == 1) {
      posy += 6;
    } else if (py == -1) {
      posy -= 6;
    }
    dot.setPosition(sf::Vector2f(posx, posy));
  }
  void SetDotColor(sf::Color color) { dot.setFillColor(color); }
};

class Popolazione {
 private:
  std::vector<Persona> v;
  const double beta;
  const double gamma;
  // percentage of deaths before vaccination starts
  // if there is no vaccination it is set to 1 (it never starts)
  const double vaccination_campaign;
  const int original_size;
  int total_infectious;
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
    for (int j = 0; j < static_cast<int>(v.size()); ++j) {
      if (v[j].GetStatus() == Stato::i) {
        ++counter;
      }
    }
    total_infectious = counter;
    total_susceptibles = static_cast<int>(V.size()) - total_infectious;
  };

  // useful with no vaccination
  Popolazione(std::vector<Persona> V, double b, double g)
      : Popolazione(V, b, g, 1.){};

  Persona GetPerson(int i) const { return v[i]; }

  double GetBeta() const { return beta; }

  double GetGamma() const { return gamma; }

  int GetSusceptibles() const { return total_susceptibles; }

  int GetInfectious() const { return total_infectious; }

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