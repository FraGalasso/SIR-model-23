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



#endif