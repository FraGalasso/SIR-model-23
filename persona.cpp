#include "persona.hpp"

#include <random>

void Popolazione::evolve() {
  std::random_device rd;
  std::default_random_engine engine(rd());
  std::uniform_int_distribution<> jump(-1, 1);

  for (int i = 0; i < size(); ++i) {
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

void Popolazione::infection() {
  std::random_device r;
  std::default_random_engine eng(r());
  std::uniform_real_distribution<> prob(0, 1);
  for (int i = 0; i < size(); ++i) {
    double p = prob(eng);
    p = v[i].GetVaccination() ? 2 * p : p;
    if (v[i].GetStatus() == Stato::i && p < gamma) {
      death(i);
    }
  }
  for (int i = 0; i < size(); ++i) {
    Stato st1 = v[i].GetStatus();
    for (int j = i + 1; j < size(); ++j) {
      if (v[i].GetX() == v[j].GetX()) {
        Stato st2 = v[j].GetStatus();
        double p = prob(eng);
        p = (v[i].GetVaccination() || v[j].GetVaccination()) ? 1.5 * p : p;
        if ((st1 == st2) || (p > beta)) {
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

void Popolazione::vaccination() {
  double count{0};
  int actual_size = size();

  if ((original_size - actual_size) >= vaccination_campaign * actual_size) {
    for (int i = 0; i < actual_size; ++i) {
      if ((count < (0.05) * actual_size) &&
          (v[i].GetVaccination() == false)) {
        v[i].Vaccine();
        ++count;
      }
    }
  }
}
