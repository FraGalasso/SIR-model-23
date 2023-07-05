#include "persona.hpp"

Person::Person(int X, int Px, int Py, Status S) : x{X}, px{Px}, py{Py}, s{S} {
  if (s == Status::s) {
    dot.setFillColor(sf::Color::Green);
  } else if (s == Status::i) {
    dot.setFillColor(sf::Color::Red);
  }
  update_dot_position();
};

int Person::get_x() const { return x; }

int Person::get_px() const { return px; }

int Person::get_py() const { return py; }

Status Person::get_status() const { return s; }

bool Person::get_vaccination() const { return is_vaccinated; }

void Person::set_x(int y) { x = y; }

void Person::set_px(int p) { px = p; }

void Person::set_py(int p) { py = p; }

void Person::set_status(Status z) { s = z; }

void Person::vaccine() {
  is_vaccinated = true;
  if (s == Status::s) {
    dot.setFillColor(sf::Color::Blue);
  }
}

void Person::update_dot_position() {
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

void Person::set_dot_color(sf::Color color) { dot.setFillColor(color); }
