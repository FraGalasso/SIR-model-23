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
    // ottengo i valori di s, i, r in floating point
    double s1{model.get_s() - p.beta * model.get_s() * model.get_i() / N};
    double i1{model.get_i() + p.beta * model.get_s() * model.get_i() / N -
              p.gamma * model.get_i()};
    double r1{model.get_r() + p.gamma * model.get_i()};

    // trovo la parte intera
    int s{static_cast<int>(floor(s1))};
    int i{static_cast<int>(floor(i1))};
    int r{static_cast<int>(floor(r1))};

    // separo la parte decimale
    s1 -= s;
    i1 -= i;
    r1 -= r;

    // equivalente alla somma dei resti
    int diff{N - (s + i + r)};

    // uno alla volta, assegno quello che rimane ai vari s, i, r
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
    // a questo punto i dovrebbe essere uguale a = 0
    if ((s + i + r) != N) {
      throw std::runtime_error(
          "Something went wrong with rounding operations.\n");
    }

    previous.set_s(model.get_s());
    previous.set_i(model.get_i());
    previous.set_r(model.get_r());

    model.set_s(s);
    model.set_i(i);
    model.set_r(r);

    // se parto sempre dagli stessi valori interi otterrò sempre gli stessi
    // risultati
    if (model == previous) {
      std::cout << "Converged after " << j << " steps.\nBreaking loop.\n";
      break;
    }
  }
  print_SIR(model);
}
