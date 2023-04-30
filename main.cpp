#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>

#include "parameters.hpp"
#include "sir.hpp"

void print_SIR(SIR m) {
  std::cout << "Susceptibles: " << m.get_s()
            << "\nInfected: " << m.get_i() << "\nRemoved: " << m.get_r()
            << '\n';
}

int main() {
  Parameters p{0.7, 0.1};
  SIR model{50, 6};
 

  for (int j = 0; j < 15; ++j) {
    const int s = model.get_s();
    const int i = model.get_i();
    const int r = model.get_r();
    const int N = s + i + r;

    int s1 = static_cast<int>(round(s - p.beta * s * i / N));
    int i1 = static_cast<int>(round(i + p.beta * s * i / N - p.gamma * i));
    int r1 = static_cast<int>(round(r + p.gamma * i));
    int N1 = s1 + i1 + r1;
    if (N1 < N) {
      s1 += N - N1;
      N1 = N;
    };
    if (N1 > N) {
      s1 -= N1 - N;
      N1 = N;
    };

    std::cout << s1 << '\t' << i1 << '\t' << r1 << '\t' << N1 << '\n';

    model.set_s(s1);
    model.set_i(i1);
    model.set_r(r1);
  }
  print_SIR(model);
}
