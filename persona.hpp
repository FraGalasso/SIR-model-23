#ifndef PERSONA_HPP
#define PERSONA_HPP

#include <stdexcept>
#include <vector>

enum class Stato { s, i, r };

class Persona {
 private:
  int x;
  int px, py;
  Stato s;
  bool e = true;

 public:
  Persona(int X, int Px, int Py, Stato S) : x{X}, px{Px}, py{Py}, s{S} {};
  int GetX() const { return x; }
  int GetPx() const { return px; }
  int GetPy() const { return py; }
  Stato GetStatus() const { return s; }
  bool GetCollision() const { return e; }
  void SetX(int y) { x = y; }
  void SetPx(int p) { px = p; }
  void SetPy(int p) { py = p; }
  void SetStatus(Stato z) { s = z; }
  void SetCollision(bool c) { e = c; }
};

class Popolazione {
 private:
  std::vector<Persona> v;
  const double beta;
  const double gamma;

 public:
  Popolazione(std::vector<Persona> V, double b, double g)
      : v{V}, beta{b}, gamma{g} {
    if (b < 0 || b > 1) {
      throw std::runtime_error{"Not a valid beta."};
    }
    if (g < 0 || g > 1) {
      throw std::runtime_error{"Not a valid gamma."};
    }
  };

  // useful for collision tests
  Popolazione(std::vector<Persona> V) : v{V}, beta{0}, gamma{0} {};

  Persona GetPerson(int i) const { return v[i]; }

  double GetBeta() const { return beta; }

  double GetGamma() const { return gamma; }

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
