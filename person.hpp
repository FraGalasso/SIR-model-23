#ifndef PERSON_HPP
#define PERSON_HPP

#include <SFML/Graphics.hpp>

// health condition, s = susceptible, i = infectious
enum class Status { s, i };

class Person {
 private:
  // position in 40*40 grid, each square is labeled by a number between 0 and
  // 1599
  int x;

  // movement along the x axis
  int px;

  // movement along the y axis
  int py;

  // health condition of this person
  Status s;

  // vaccination status: default = false
  bool is_vaccinated = false;

  // square in the grid
  sf::RectangleShape dot = sf::RectangleShape(sf::Vector2f(6, 6));

 public:
  // constructor, defined at line 3 of person.cpp
  Person(int X, int Px, int Py, Status S);

  // getting position in 40*40 grid, each square is labeled by a number between
  // 0 and 1599, defined at line 12 of person.cpp
  int get_x() const;

  // getting movement along the x axis, defined at line 14 of person.cpp
  int get_px() const;

  // getting movement along the y axis, defined at line 16 of person.cpp
  int get_py() const;

  // getting health condition, defined at line 18 of person.cpp
  Status get_status() const;

  // getting dot, defined at line 20 of person.cpp
  sf::RectangleShape get_dot() const;

  // getting vaccination status, defined at line 22 of person.cpp
  bool get_vaccination() const;

  // setting position in 40*40 grid, defined at line 24 of person.cpp
  void set_x(int y);

  // setting movement along the x axis, defined at line 26 of person.cpp
  void set_px(int p);

  // setting movement along the y axis, defined at line 28 of person.cpp
  void set_py(int p);

  // setting health condition, defined at line 30 of person.cpp
  void set_status(Status z);

  // vaccination, sets dot color to blue if the person is still susceptible,
  // defined at line 32 of person.cpp
  void vaccine();

  // updates dot position on the grid according to its position x and its
  // movement direction: if the person comes from right, the dot will be on the
  // right edge, etc, defined at line 39 of person.cpp
  void update_dot_position();

  // setting dot color, defined at line 55 of person.cpp
  void set_dot_color(sf::Color color);
};

#endif
