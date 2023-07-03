#include "persona.hpp"

#include <random>

void Popolazione::evolve() {
  std::random_device rd;
  std::default_random_engine engine(rd());
  std::uniform_int_distribution<> jump(-1, 1);

  for (int i = 0; i < size(); ++i) {
    if (v[i].GetStatus() == Stato::r) {
      continue;
    }

    int r = v[i].GetX();
    int px = jump(engine);
    int py = jump(engine);

    if (px == 1) {
      if (r % 40 == 39) {
        r -= 39;
      } else {
        ++r;
      }
    }
    if (px == -1) {
      if (r % 40 == 0) {
        r += 39;
      } else {
        --r;
      }
    }
    if (py == 1) {
      if (r >= 0 && r <= 39) {
        // dy = 90;
        r += 1560;
      } else {
        // dy = -10;
        r -= 40;
      }
    }
    if (py == -1) {
      if (r >= 90 && r <= 99) {
        // dy = -90;
        r -= 1560;
      } else {
        // dy = 10;
        r += 40;
      }
    }
    v[i].SetX(r);
    v[i].SetPx(px);
    v[i].SetPy(py);
    v[i].UpdateDotPosition();
  }

  infection();
}

/*void Popolazione::collision() {
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
}*/

void Popolazione::infection() {
  std::random_device r;
  std::default_random_engine eng(r());
  std::uniform_real_distribution<> prob(0, 1);
  for (int i = 0; i < size(); ++i) {
    if (v[i].GetStatus() == Stato::i && prob(eng) < gamma) {
      v[i].SetStatus(Stato::r);
      v[i].SetX(1600);
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
          v[j].SetDotColor(sf::Color::Red);
          continue;
        }
        if (st1 == Stato::s) {
          v[i].SetStatus(Stato::i);
          v[i].SetDotColor(sf::Color::Red);
        }
      }
    }
  }
}
