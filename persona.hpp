#ifndef PERSONA_HPP
#define PERSONA_HPP

#include <vector>

enum class Stato { Susceptible, Infectious, Removed };

class Persona {
 private:
  int x;
  int px, py;
  Stato s;

 public:
  Persona(int X, int Px, int Py, Stato S) : x{X}, px{Px}, py{Py}, s{S} {};
  int GetX() const { return x; }
  int GetPx() const { return px; }
  int GetPy() const { return py; }
  void SetX(int y) { x = y; };
};

class Popolazione {
 private:
  std::vector<Persona> v;

 public:
  Popolazione(std::vector<Persona> V) : v{V} {};

  Persona GetPerson(int i) const { return v[i]; }

  int size() { return v.size(); }

  void evolve() {
    for (int i = 0; i < size(); ++i) {
      int r = v[i].GetX();
      int px = v[i].GetPx();
      int py = v[i].GetPy();
      if (px == 1) {
        if ((r % 10) == 9) {
          r -= 9;
        } else {
          ++r;
        }
      }
      if (px == -1) {
        if (r % 10 == 0) {
          r += 9;
        } else {
          --r;
        }
      }
      if (py == 1) {
        if (r >= 0 && r <= 9) {
          r += 90;
        } else {
          r -= 10;
        }
      }
      if (py == -1) {
        if (r >= 90 && r <= 99) {
          r -= 90;
        } else {
          r += 10;
        }
      }
      if ((px * px) != 1 && (py * py) != 1) {
        r = 0;
      }
      v[i].SetX(r);
    }
  }
};

#endif
