#include <cmath>
#include <iostream>
#include <stdexcept>
#include <vector>

#include "parameters.hpp"
#include "sir.hpp"

void print_SIR(SIR m) {
  std::cout << "Susceptibles: " << m.get_s() << "\nInfected: " << m.get_i()
            << "\nRemoved: " << m.get_r() << '\n';
}

int main() {
  Parameters p{0.7, 0.1};
  SIR model{1000, 20};

  for (int j = 0; j < 500; ++j) {
    const int N{model.get_s() + model.get_i() + model.get_r()};

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
      throw std::runtime_error("oh oh\n");
    }

    std::cout << s << '\t' << i << '\t' << r << '\t' << s + i + r << '\n';

    model.set_s(s);
    model.set_i(i);
    model.set_r(r);
  }
  print_SIR(model);
}
