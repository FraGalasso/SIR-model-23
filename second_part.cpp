#include <SFML/Graphics.hpp>
#include <chrono>
#include <iostream>
#include <random>
#include <string>
#include <thread>

#include "insert_functions.hpp"
#include "person.hpp"
#include "population.hpp"

// generating random people and putting them in a population
Population RandomPopulationGenerator(int s, int i, double beta, double gamma,
                                     double vax_pct) {
  std::random_device rd;
  std::default_random_engine eng(rd());
  std::uniform_int_distribution<> position(0, 1599);
  std::uniform_int_distribution<> momentum(-1, 1);
  std::vector<Person> people;
  for (int j = 0; j < s; ++j) {
    Person p(position(eng), momentum(eng), momentum(eng), Status::s);
    people.push_back(p);
  }
  for (int j = 0; j < i; ++j) {
    Person p(position(eng), momentum(eng), momentum(eng), Status::i);
    people.push_back(p);
  }
  Population pop(people, beta, gamma, vax_pct);
  return pop;
}

int main() {
  try {
    std::cout << "Input beta.\n";
    double beta{insert_parameter()};
    std::cout << "Input gamma.\n";
    double gamma{insert_parameter()};
    int sus = 1601;
    int inf = 1601;
    while (sus + inf > 1600) {
      std::cout << "Input susceptibles (don't exceed 1600 total people).\n";
      sus = insert_people();
      std::cout << "Input infectious (don't exceed 1600 total people).\n";
      inf = insert_people();
    }
    std::cout << "Do you want to show the grid? [y/n].\n";
    bool show_grid{insert_y_n()};
    std::cout << "Do you want to have vaccinations? [y/n].\n";
    bool vaccine{insert_y_n()};
    double vax_pct = 1;
    if (vaccine) {
      std::cout << "Input what percentage of deaths triggers "
                   "vaccinations.\n(Number from 0 to 1.)\n";
      vax_pct = insert_parameter();
    }

    // intializing sfml render window
    sf::RenderWindow window(sf::VideoMode(720, 775), "SIR visualization");

    // generating population
    Population pop =
        RandomPopulationGenerator(sus, inf, beta, gamma, vax_pct);

    // used to store grid lines (if necessary)
    std::vector<sf::VertexArray> grid_lines;

    if (show_grid) {
      // initializing grid lines
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

    // lower banner to show real time statistics
    sf::RectangleShape banner(sf::Vector2f(720, 55));
    banner.setFillColor(sf::Color::White);
    banner.setPosition(sf::Vector2f(0, 720));

    // loading 'Helvetica' font
    sf::Font font;
    if (!font.loadFromFile("helvetica.otf")) {
      throw std::runtime_error{"Error loading fonts.\n"};
    }

    // Title and fixed elements to write in lower banner
    sf::Text title;
    title.setFont(font);
    title.setString("SIR model");
    title.setCharacterSize(20);
    title.setFillColor(sf::Color::Black);
    title.setPosition(sf::Vector2f(340, 725));
    sf::Text s_num;
    s_num.setFont(font);
    s_num.setCharacterSize(18);
    s_num.setFillColor(sf::Color::Black);
    s_num.setPosition(sf::Vector2f(50, 745));
    std::string susceptibles{"Susceptibles: "};
    sf::Text i_num;
    i_num.setFont(font);
    i_num.setCharacterSize(18);
    i_num.setFillColor(sf::Color::Black);
    i_num.setPosition(sf::Vector2f(325, 745));
    std::string infectious{"Infectious: "};
    sf::Text r_num;
    r_num.setFont(font);
    r_num.setCharacterSize(18);
    r_num.setFillColor(sf::Color::Black);
    r_num.setPosition(sf::Vector2f(585, 745));
    std::string removed{"Removed: "};

    while (window.isOpen()) {
      // checking if the window is still open
      sf::Event event;
      while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
          window.close();
        }
      }

      // evolving once per iteration
      pop.evolve();

      // early exit in case of empty population
      if (pop.size() == 0) {
        window.close();
        break;
      }

      // clearing window from previous pictures
      window.clear(sf::Color::Black);

      // drawing people
      for (int i = 0; i < pop.size(); ++i) {
        window.draw(pop.get_person(i).get_dot());
      }

      if (show_grid) {
        // drawing grid
        for (int i = 0; i < static_cast<int>(grid_lines.size()); ++i) {
          window.draw(grid_lines[i]);
        }
      }

      // drawing lower banner
      window.draw(banner);

      // generating strings with current statistics

      std::string sus_append = std::to_string(pop.get_susceptibles());
      std::string inf_append = std::to_string(pop.get_infectious());
      std::string rem_append = std::to_string(pop.get_removed());
      s_num.setString(susceptibles + sus_append);
      i_num.setString(infectious + inf_append);
      r_num.setString(removed + rem_append);

      // drawing texts
      window.draw(title);
      window.draw(s_num);
      window.draw(i_num);
      window.draw(r_num);

      // displaying the window
      window.display();

      // waiting a bit to avoid messy evolution
      std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }
  } catch (std::exception const& e) {
    std::cerr << "Caught exception: '" << e.what() << "'\n";
    return EXIT_FAILURE;
  }
}