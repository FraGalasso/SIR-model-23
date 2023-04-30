#include <cmath>
#include <iostream>

#include "parameters.hpp"
#include "sir.hpp"

/*void print_SIR(SIR m) {
  std::cout << "Susceptibles: " << m.Supsceptibles()
            << "\nInfected: " << m.Infected() << "\nRemoved: " << m.Removed()
            << '\n';
}*/

int main() {
  Parameters p{0.3, 0.1};
  SIR model{50, 6, 0};

  for (int j = 0; j < 15; ++j) {
    const int s = model.Supsceptibles();
    const int i = model.Infected();
    const int r = model.Removed();
    const int N = s + i + r;

    double s1 = round(s - p.beta * s * i / N);
    double i1 = round(i + p.beta * s * i / N - p.gamma * i);
    double r1 = round(r + p.gamma * i);
    int N1 = s1 + i1 + r1;

    std::cout << s1 << '\t' << i1 << '\t' << r1 << '\t' << N1 << '\n';

    model.set_s(s1);
    model.set_i(i1);
    model.set_r(r1);
  }
}