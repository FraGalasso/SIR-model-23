#ifndef PERSONA_HPP
#define PERSONA_HPP

#include <vector>

enum class Stato { s, i, r };

class Persona {
 private:
  int x;
  int px, py;
  Stato s;
  int e;

 public:
  Persona(int X, int Px, int Py, Stato S, int E) : x{X}, px{Px}, py{Py}, s{S} , e{E} {};
  int GetX() const { return x; }
  int GetPx() const { return px; }
  int GetPy() const { return py; }
  Stato GetStatus() const { return s; }
  int GetCollision() const {return e; }
  void SetX(int y) { x = y; }
  void SetPx(int p) { px = p; }
  void SetPy(int p) { py = p; }
  void SetStatus(Stato z) { s = z; }
  void SetCollision(int c) {e = c;}
};

class Popolazione {
 private:
  std::vector<Persona> v;

 public:
  Popolazione(std::vector<Persona> V) : v{V} {};

  Persona GetPerson(int i) const { return v[i]; }

  int size() { return v.size(); }

  void evolve();

  void random_distribution();

  void status_distribution(int n);

  void collision();

  void infection();
};

#endif

// fare in modo che ci sia una probabilità di contagio

// visualizzazione con una griglia 10x10
