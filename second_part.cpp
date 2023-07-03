#include <SFML/Graphics.hpp>
#include <chrono>
#include <iostream>
#include <random>
#include <thread>

#include "insert_functions.hpp"
#include "persona.hpp"

Popolazione RandomPopulationGenerator(int s, int i, double beta, double gamma) {
  std::random_device rd;
  std::default_random_engine eng(rd());
  std::uniform_int_distribution<> position(0, 1599);
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
  Popolazione pop(people, beta, gamma);
  return pop;
}

int main() {
  std::cout << "Input beta.\n";
  double beta{insert_parameter()};
  std::cout << "Input gamma.\n";
  double gamma{insert_parameter()};
  std::cout << "Input susceptibles.\n";
  int sus{insert_people()};
  std::cout << "Input infectious.\n";
  int inf{insert_people()};
  std::cout << "Do you want to show the grid?.\n";
  bool show_grid{insert_y_n()};

  sf::RenderWindow window(sf::VideoMode(720, 720), "SIR visualization");
  Popolazione pop = RandomPopulationGenerator(sus, inf, beta, gamma);

  std::vector<sf::VertexArray> grid_lines;

  if (show_grid) {
    for (int i = 1; i < 40; ++i) {
      sf::VertexArray line(sf::Lines, 2);
      line[0].position = sf::Vector2f(i * 18, 0);
      line[1].position = sf::Vector2f(i * 18, 720);
      line[0].color = sf::Color::Yellow;
      line[1].color = sf::Color::Yellow;
      grid_lines.push_back(line);
    }
    for (int i = 1; i < 40; ++i) {
      sf::VertexArray line(sf::Lines, 2);
      line[0].position = sf::Vector2f(0, i * 18);
      line[1].position = sf::Vector2f(720, i * 18);
      line[0].color = sf::Color::Yellow;
      line[1].color = sf::Color::Yellow;
      grid_lines.push_back(line);
    }
  }

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();
    }
    pop.evolve();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    window.clear(sf::Color::Black);

    for (int i = 0; i < pop.size(); ++i) {
      if (pop.GetPerson(i).GetStatus() == Stato::r) {
        continue;
      }
      window.draw(pop.GetPerson(i).GetDot());
    }
    if (show_grid) {
      for (int i = 0; i < static_cast<int>(grid_lines.size()); ++i) {
        window.draw(grid_lines[i]);
      }
    }

    window.display();
  }
}