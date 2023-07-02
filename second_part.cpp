#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>

#include "persona.hpp"

int main() {
  sf::RenderWindow window(sf::VideoMode(1000, 1000), "SIR visualization");
  Persona p(1, -1, 0, Stato::s);
  Persona q(9, 1, 0, Stato::i);
  Popolazione pop{{p, q}, 0.5, 0.5};

  pop.evolve();

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