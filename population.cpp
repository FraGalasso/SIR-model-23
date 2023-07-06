#include "population.hpp"

#include <random>
#include <stdexcept>

Population::Population(std::vector<Person> V, double b, double g, double vax)
    : people{V},
      beta{b},
      gamma{g},
      vaccination_campaign{vax},
      original_size{static_cast<int>(V.size())} {
  // throwing with invalid parameters
  if (b < 0 || b > 1) {
    throw std::runtime_error{"Not a valid beta."};
  }
  if (g < 0 || g > 1) {
    throw std::runtime_error{"Not a valid gamma."};
  }
  if (vax < 0 || vax > 1) {
    throw std::runtime_error{
        "Not a valid percentage for vaccination campaign."};
  }

  // counting susceptibles in initial population
  int counter = 0;
  for (int j = 0; j < static_cast<int>(V.size()); ++j) {
    if (people[j].get_status() == Status::s) {
      ++counter;
    }
  }
  total_susceptibles = counter;
};

Population::Population(std::vector<Person> V, double b, double g)
    : Population(V, b, g, 1.){};

Person Population::get_person(int i) const { return people[i]; }

double Population::get_beta() const { return beta; }

double Population::get_gamma() const { return gamma; }

int Population::get_susceptibles() const { return total_susceptibles; }

int Population::get_infectious() const {
  return static_cast<int>(people.size()) - total_susceptibles;
}

int Population::get_removed() const {
  return original_size - static_cast<int>(people.size());
}

int Population::size() { return static_cast<int>(people.size()); }

void Population::evolve() {
  std::random_device rd;
  std::default_random_engine engine(rd());
  std::uniform_int_distribution<> jump(-1, 1);

  for (int i = 0; i < static_cast<int>(people.size()); ++i) {
    int r = people[i].get_x();

    // deciding randomly movement direction
    int px = jump(engine);
    int py = jump(engine);

    // computing new positions, in 'edge' cases people are moved on the other
    // side of the board instead of bouncing
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
    people[i].set_x(r);
    people[i].set_px(px);
    people[i].set_py(py);
    people[i].update_dot_position();
  }

  // processing infections
  infection();
  // processing vaccinations
  vaccination();
}

void Population::infection() {
  std::random_device r;
  std::default_random_engine eng(r());
  std::uniform_real_distribution<> prob(0, 1);

  // vector to store indexes of dead people
  std::vector<int> dead_people;

  for (int i = 0; i < size(); ++i) {
    if (people[i].get_status() == Status::s) {
      continue;
    }

    double p = prob(eng);

    // filling dead_people with indexes
    if (p < gamma) {
      dead_people.push_back(i);
    }
  }

  // erasing dead people from people
  death(dead_people);

  for (int i = 0; i < static_cast<int>(people.size()) - 1; ++i) {
    bool vax1 = people[i].get_vaccination();

    for (int j = i + 1; j < static_cast<int>(people.size()); ++j) {
      // condidering only people in the same cell in the grid
      if (people[i].get_x() == people[j].get_x()) {
        double p = prob(eng);

        // vaccinated people have more chances to avoid infection
        if (vax1 || people[j].get_vaccination()) {
          p *= 1.3;
        }

        if (p < beta) {
          // setting infections (if people are in different states) and lowering
          // total susceptibles number
          if (people[i].get_status() == Status::i &&
              people[j].get_status() == Status::s) {
            people[j].set_status(Status::i);

            people[j].set_dot_color(sf::Color::Red);

            --total_susceptibles;
          } else if (people[i].get_status() == Status::s &&
                     people[j].get_status() == Status::i) {
            people[i].set_status(Status::i);

            people[i].set_dot_color(sf::Color::Red);

            --total_susceptibles;
          }
        }
      }
    }
  }
}

void Population::vaccination() {
  int actual_size = static_cast<int>(people.size());

  // if number of removed people is lower than a certain threshold, vaccination
  // campaign doesn't start
  if ((1 - vaccination_campaign) * original_size >= actual_size) {
    double count = 0;

    // vaccinating only 1% of the population at a time
    for (int i = 0; (i < actual_size) && (count < (0.01) * actual_size); ++i) {
      if (!(people[i].get_vaccination())) {
        people[i].vaccine();
        ++count;
      }
    }
  }
}

void Population::death(std::vector<int> d) {
  // looping in reverse order to avoid skipping people or removing wrong people
  for (int i = static_cast<int>(d.size()) - 1; i >= 0; --i) {
    auto it = people.begin() + d[i];
    people.erase(it);
  }
}
