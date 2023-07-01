#include "persona.hpp"

#include <random>

void Popolazione::evolve(Parameter const& par) {
  
  for (int i = 0; i < size(); ++i) {
    if (v[i].GetStatus() == Stato::r) {
      continue;
    }

    int r = v[i].GetX();
    int px = v[i].GetPx();
    int py = v[i].GetPy();

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
 
  infection(par);
  collision();
}

void Popolazione::random_distribution() {
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

void Popolazione::status_distribution(int n) {
  std::mt19937 gen(time(0));
  // random bit generator (mersenne twister)
  for (int i = 0; i < n; ++i) {
    v[i].SetStatus(Stato::i);
  }
  for (int i = n; i < size(); ++i) {
    v[i].SetStatus(Stato::s);
  }
}

void Popolazione::collision() {
  for (int i = 0; i < size() - 1; ++i) {
    for (int j = i + 1; j < size(); ++j) {
      if (v[i].GetX() == v[j].GetX()) {
        if (v[i].GetCollision()) {
          v[i].SetPx(-(v[i].GetPx()));
          v[i].SetPy(-(v[i].GetPy()));
          v[i].SetCollision(false);
        }
        if (v[j].GetCollision()) {
          v[j].SetPx(-(v[j].GetPx()));
          v[j].SetPy(-(v[j].GetPy()));
          v[j].SetCollision(false);
        }
      }
    }
  }
  for (int i = 0; i < size(); ++i) {
    v[i].SetCollision(true);
  }
}

void Popolazione::infection(Parameter const& par) {
  for (int i = 0; i < size() - 1; ++i) {
    for (int j = i + 1; j < size(); ++j) {
      if (v[i].GetX() == v[j].GetX()) {
        Stato st1 = v[i].GetStatus();
        Stato st2 = v[j].GetStatus();
        if (st1 == Stato::i && st2 == Stato::s) {
          std::mt19937 gen(time(0));
          std::uniform_int_distribution<> prob(0, 100);
          int p = prob(gen);

          if ((par.b * 100) >= p) {
            st2 = Stato::i;
            v[j].SetStatus(st2);
            continue;
          }
        }
        if (st1 == Stato::s && st2 == Stato::i) {
          std::mt19937 gen(time(0));
          std::uniform_int_distribution<> prob(0, 100);
          int p = prob(gen);
          if ((par.b * 100) >= p) {
            st1 = Stato::i;
            v[i].SetStatus(st1);
          }
        }
      }
    }
    if (v[i].GetStatus() == Stato::i) {
      std::mt19937 gen(time(0));
      std::uniform_int_distribution<> prob(0, 100);
      int p = prob(gen);
      if ((par.g * 100) >= p) {
        v[i].SetStatus(Stato::r);
      }
    }
  }
}
