#include "persona.hpp"

#include <random>

void Popolazione::evolve() {
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
    v[i].SetX(r);
    v[i].UpdateDotPosition();
  }

  infection();
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

void Popolazione::infection() {
  std::random_device r;
  std::default_random_engine eng(r());
  std::uniform_real_distribution<> prob(0, 1);
  for (int i = 0; i < size(); ++i) {
    if (v[i].GetStatus() == Stato::i && prob(eng) < gamma) {
      v[i].SetStatus(Stato::r);
      v[i].GetDot().setFillColor(sf::Color::Yellow);
      v[i].SetX(100);
    }
  }
  for (int i = 0; i < size(); ++i) {
    Stato st1 = v[i].GetStatus();
    if (st1 == Stato::r) {
      continue;
    }
    for (int j = i + 1; j < size(); ++j) {
      if (v[i].GetX() == v[j].GetX()) {
        Stato st2 = v[j].GetStatus();
        if ((st1 == st2) || (st2 == Stato::r) || (prob(eng) > beta)) {
          continue;
        }
        if (st1 == Stato::i) {
          v[j].SetStatus(Stato::i);
          v[j].GetDot().setFillColor(sf::Color::Red);
          continue;
        }
        if (st1 == Stato::s) {
          v[i].SetStatus(Stato::i);
          v[j].GetDot().setFillColor(sf::Color::Red);
        }
      }
    }
  }
}