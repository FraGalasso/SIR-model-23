#ifndef INSERT_FUNCTIONS_HPP
#define INSERT_FUNCTIONS_HPP

#include <iostream>
#include <limits>
#include <stdexcept>

double insert_parameter() {
  double par;
  while (!(std::cin >> par) || par < 0 || par > 1) {
    if (std::cin.eof()) {
      throw std::runtime_error{"Unexpected input termination."};
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cerr << "Invalid input. Remember that it must be between 0 and 1.\n";
  }
  return par;
}

int insert_people() {
  int people;
  while (!(std::cin >> people) || people < 0) {
    if (std::cin.eof()) {
      throw std::runtime_error{"Unexpected input termination."};
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cerr << "Invalid input. Remember that it must be at least 0.\n";
  }
  return people;
}

bool insert_y_n() {
  char answer;
  while (!(std::cin >> answer) || (answer != 'y' && answer != 'n')) {
    if (std::cin.eof()) {
      throw std::runtime_error{"Unexpected input termination."};
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cerr
        << "Invalid input. Remember that it must be between 'y' or 'n'.\n";
  }
  if (answer == 'y') {
    return true;
  }
  return false;
}

#endif