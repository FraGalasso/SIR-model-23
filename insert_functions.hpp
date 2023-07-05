#ifndef INSERT_FUNCTIONS_HPP
#define INSERT_FUNCTIONS_HPP

#include <iostream>
#include <limits>
#include <stdexcept>

// used to get beta and gamma from user
double insert_parameter() {
  double par;
  while (!(std::cin >> par) || par < 0 || par > 1) {
    // used to throw with empty input
    if (std::cin.eof()) {
      throw std::runtime_error{"Unexpected input termination."};
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cerr << "Invalid input. Remember that it must be between 0 and 1.\n";
  }
  return par;
}

// used to get susceptibles, infectious, removed and time duration from user,
// differences from the previous function are the absence of upper bounds to
// number inserted and 'int' as returned type instead of 'double'
int insert_people() {
  int people;
  while (!(std::cin >> people) || people < 0) {
    // used to throw with empty input
    if (std::cin.eof()) {
      throw std::runtime_error{"Unexpected input termination."};
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cerr << "Invalid input. Remember that it must be at least 0.\n";
  }
  return people;
}

// used to get yes/no answers from user
bool insert_y_n() {
  char answer;
  while (!(std::cin >> answer) || (answer != 'y' && answer != 'n')) {
    // used to throw with empty input
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