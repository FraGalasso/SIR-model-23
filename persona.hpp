#ifndef PERSONA_HPP
#define PERSONA_HPP

#include <iostream>
#include <random>
#include <vector>

enum class Stato { s, i, r };

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
  Stato GetStatus() const { return s; }
  void SetX(int y) { x = y; };
  void SetPx(int p) { px = p; }
  void SetPy(int p) { py = p; }
  void SetStatus(Stato z) { s = z; }
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
      v[i] = GetPerson(i);
      int r = v[i].GetX();
      int px = v[i].GetPx();
      int py = v[i].GetPy();

      if (v[i].GetStatus() != Stato::r) {
        if (px == 1) {
          if ((r % 10) == 9) {
            // dx = -9;
            r -= 9;
          } else {
            // dx = 1;
            ++r;
          }
        }
        if (px == -1) {
          if (r % 10 == 0) {
            // dx = 9;
            r += 9;
          } else {
            --r;
          }
        }
        if (py == 1) {
          if (r >= 0 && r <= 9) {
            // dy = 90;
            r += 90;
          } else {
            // dy = -10;
            r -= 10;
          }
        }
        if (py == -1) {
          if (r >= 90 && r <= 99) {
            // dy = -90;
            r -= 90;
          } else {
            // dy = 10;
            r += 10;
          }
        }
        if ((px * px) != 1 && (py * py) != 1) {
          // dx = 0;
          // dy = 0;
          r = 0;
        }
        v[i].SetX(r);
      }
      if (v[i].GetStatus() == Stato::r) {
        v[i].SetX(100);
      }
      infection();
      collision();
    }
  };
  void random_distribution() {
    std::mt19937 gen(time(0));
    // random bit generator (mersenne twister)
    for (int i = 0; i < size(); ++i) {
      std::uniform_int_distribution<> x_distribution(0, 99);
      int x = x_distribution(gen);
      std::uniform_int_distribution<> px_distribution(-1, 1);
      int px = px_distribution(gen);
      std::uniform_int_distribution<> py_distribution(-1, 1);
      int py = py_distribution(gen);
      v[i].SetX(x);
      v[i].SetPx(px);
      v[i].SetPy(py);
    }
  }
  void status_distribution(int n) {
    std::mt19937 gen(time(0));
    // random bit generator (mersenne twister)
    for (int i = 0; i < n; ++i) {
      v[i].SetStatus(Stato::i);
    }
    for (int i = n; i < size(); ++i) {
      v[i].SetStatus(Stato::s);
    }
  }

  void collision() {
    for (int i = 0; i < size(); ++i) {
      int j = 1;
      while (j + i < size()) {
        v[i] = GetPerson(i);
        v[i + j] = GetPerson(i + j);
        int r = v[i].GetX();
        int px = v[i].GetPx();
        int py = v[i].GetPy();
        int r_ = v[i + j].GetX();
        int px_ = v[i + j].GetPx();
        int py_ = v[i + j].GetPy();
        if (r == r_) {
          px = -px;
          px_ = -px_;
          py = -py;
          py_ = -py;
          v[i].SetPx(px);
          v[i].SetPy(py);
          v[i + j].SetPx(px_);
          v[i + j].SetPy(py_);
        }
        ++j;
      }
    }
  };
  void infection() {
    for (int i = 0; i < size(); ++i) {
      int j = 1;
      while (j + i < size()) {
        v[i] = GetPerson(i);
        v[i + j] = GetPerson(i + j);
        int r = v[i].GetX();
        int r_ = v[i + j].GetX();
        Stato st1 = v[i].GetStatus();
        Stato st2 = v[i + j].GetStatus();
        if (r == r_) {
          if (st1 == Stato::i && st2 == Stato::s) {
            st2 = Stato::i;
            v[i + j].SetStatus(st2);
          }
          if (st1 == Stato::s && st2 == Stato::i) {
            st1 = Stato::i;
            v[i].SetStatus(st1);
          }
        }
        ++j;
      }
    }
  };
};

#endif

// fare in modo che ci sia una probabilità di contagio

// visualizzazione con una griglia 10x10
