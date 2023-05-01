#include <cmath>
#include <iostream>
#include <stdexcept>
#include <vector>

#include "parameters.hpp"
#include "sir.hpp"

void print_SIR(SIR m) {
  std::cout << "Susceptibles: " << m.get_s() << "\nInfectious: " << m.get_i()
            << "\nRemoved: " << m.get_r() << '\n';
}

int main() {
  Parameters p{0.3, 0.015};
  SIR model{100000, 20};
  SIR previous{};

  const int N{model.get_s() + model.get_i() + model.get_r()};

  for (int j = 0; j < 50000; ++j) {
    // computing floating-point values for s, i, r
    double s1{model.get_s() - p.beta * model.get_s() * model.get_i() / N};
    double i1{model.get_i() + p.beta * model.get_s() * model.get_i() / N -
              p.gamma * model.get_i()};
    double r1{model.get_r() + p.gamma * model.get_i()};

    // computing integer part
    int s{static_cast<int>(floor(s1))};
    int i{static_cast<int>(floor(i1))};
    int r{static_cast<int>(floor(r1))};

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
}
