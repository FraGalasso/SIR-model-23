#include <SFML/Graphics.hpp>
#include <chrono>
#include <random>
#include <thread>

#include "persona.hpp"

Popolazione RandomPopulationGenerator(int s, int i, int r, double beta,
                                      double gamma) {
  std::random_device rd;
  std::default_random_engine eng(rd());
  std::uniform_int_distribution<> position(0, 99);
  std::uniform_int_distribution<> momentum(-1, 1);
  std::vector<Persona> people;
  for (int j = 0; j < s; ++j) {
    Persona p(position(eng), momentum(eng), momentum(eng), Stato::s);
    people.push_back(p);
  }
  for (int j = 0; j < i; ++j) {
    Persona p(position(eng), momentum(eng), momentum(eng), Stato::i);
    people.push_back(p);
  }
  for (int j = 0; j < r; ++j) {
    Persona p(100, 0, 0, Stato::r);
    people.push_back(p);
  }
  Popolazione pop(people, beta, gamma);
  return pop;
}

Popolazione RandomPopulationGenerator(int s, int i, double beta, double gamma) {
  return RandomPopulationGenerator(s, i, 0, beta, gamma);
}

int main() {
  sf::RenderWindow window(sf::VideoMode(1000, 1000), "SIR visualization");
  Popolazione pop = RandomPopulationGenerator(16, 4, 0.4, 0.1);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();
    }
    pop.evolve();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    window.clear(sf::Color::Black);

    for (int i = 0; i < pop.size(); ++i) {
      if (pop.GetPerson(i).GetStatus() == Stato::r) {
        continue;
      }
      window.draw(pop.GetPerson(i).GetDot());
    }

    window.display();
  }
}