#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <vector>

#include "parameters.hpp"
#include "sir.hpp"

void print_SIR(SIR const& m) {
  std::cout << "Susceptibles: " << m.get_s() << "\nInfectious: " << m.get_i()
            << "\nRemoved: " << m.get_r() << '\n';
}

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

int main() {
  try {
    std::cout << "Input beta.\n";
    double beta{insert_parameter()};
    std::cout << "Input gamma.\n";
    double gamma{insert_parameter()};
    Parameters p{beta, gamma};
    SIR model{};
    std::cout << "Input susceptibles.\n";
    model.set_s(insert_people());
    std::cout << "Input infectious.\n";
    model.set_i(insert_people());
    std::cout << "Input removed.\n";
    model.set_r(insert_people());
    std::cout << "Input duration (in days).\n";
    int steps{insert_people()};
    SIR previous{};

    const int N{model.get_s() + model.get_i() + model.get_r()};
    if (N == 0) {
      steps = 0;
    }

    for (int j = 0; j < steps; ++j) {
      // computing floating-point values for s, i, r
      double s1{model.get_s() - p.beta * model.get_s() * model.get_i() / N};
      double i1{model.get_i() + p.beta * model.get_s() * model.get_i() / N -
                p.gamma * model.get_i()};
      double r1{model.get_r() + p.gamma * model.get_i()};

      // computing integer part
      int s{static_cast<int>(s1)};
      int i{static_cast<int>(i1)};
      int r{static_cast<int>(r1)};

      // separating decimal part
      s1 -= s;
      i1 -= i;
      r1 -= r;

      // equivalent to sum of decimal parts
      int diff{N - (s + i + r)};

      // distributing remainder from decimal parts, one step at a time
      while (diff > 0) {
        if (s1 >= i1 && s1 >= r1) {
          ++s;
          s1 = 0;
          --diff;
        } else if (i1 >= s1 && i1 >= r1) {
          ++i;
          i1 = 0;
          --diff;
        } else {
          ++r;
          r1 = 0;
          --diff;
        }
      }
      // at this point diff should be equal to 0

      previous.set_s(model.get_s());
      previous.set_i(model.get_i());
      previous.set_r(model.get_r());

      model.set_s(s);
      model.set_i(i);
      model.set_r(r);

      // no point in going on if I'm always starting from the same integers
      if (model == previous) {
        std::cout << "Converged after " << j << " steps.\nBreaking loop.\n";
        break;
      }
    }
    print_SIR(model);

    std::ofstream out_file("results.txt");
    if (!out_file) {
      std::cerr << "Failed opening results.txt.\n";
      return EXIT_FAILURE;
    }
    out_file << std::setw(15) << "Susceptibles:" << std::setw(15)
             << "Infectious:" << std::setw(15) << "Removed:" << '\n'
             << std::setw(15) << model.get_s() << std::setw(15) << model.get_i()
             << std::setw(15) << model.get_r() << '\n';
    out_file.close();
  } catch (std::exception const& e) {
    std::cerr << "Caught exception: '" << e.what() << "'\n";
    return EXIT_FAILURE;
  }
}