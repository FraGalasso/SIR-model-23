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
        r += 1560;
      } else {
        r -= 40;
      }
    }
    if (py == -1) {
      if (r >= 1560 && r <= 1599) {
        r -= 1560;
      } else {
        r += 40;
      }
    }
    v[i].SetX(r);
    v[i].SetPx(px);
    v[i].SetPy(py);
    v[i].UpdateDotPosition();
  }

  infection();
  vaccination();
}

void Popolazione::infection() {
  std::random_device r;
  std::default_random_engine eng(r());
  std::uniform_real_distribution<> prob(0, 1);
  std::vector<int> dead_people;
  for (int i = 0; i < size(); ++i) {
    double p = prob(eng);
    if (v[i].GetVaccination()) {
      p *= 1.3;
    }
    if (v[i].GetStatus() == Stato::i && p < gamma) {
      dead_people.push_back(i);
    }
  }
  death(dead_people);

  for (int i = 0; i < size(); ++i) {
    bool vax1 = v[i].GetVaccination();
    for (int j = i + 1; j < size(); ++j) {
      if (v[i].GetX() == v[j].GetX()) {
        double p = prob(eng);
        if (vax1 || v[j].GetVaccination()) {
          p *= 1.3;
        }
        if (p < beta) {
          if (v[i].GetStatus() == Stato::i && v[j].GetStatus() == Stato::s) {
            v[j].SetStatus(Stato::i);
            v[j].SetDotColor(sf::Color::Red);
            --total_susceptibles;
          }
          if (v[i].GetStatus() == Stato::s && v[j].GetStatus() == Stato::i) {
            v[i].SetStatus(Stato::i);
            v[i].SetDotColor(sf::Color::Red);
            --total_susceptibles;
          }
        }
      }
    }
  }
}

void Popolazione::vaccination() {
  int actual_size = size();

  // if number of removed people is lower than a certain threshold, vaccination
  // campaign doesn't start
  if ((1 - vaccination_campaign) * original_size >= actual_size) {
    double count = 0;
    for (int i = 0; (i < actual_size) && (count < (0.01) * actual_size); ++i) {
      if (!(v[i].GetVaccination())) {
        v[i].Vaccine();
        ++count;
      }
    }
  }
}
