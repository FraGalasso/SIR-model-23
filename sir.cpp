#include "sir.hpp"

#include <stdexcept>

SIR::SIR(int s, int i, int r) : S{s}, I{i}, R{r} {
  if ((s < 0) || (i < 0) || (r < 0)) {
    throw std::runtime_error("Negative values are not allowed.");
  }
}

int SIR::get_s() const { return S; }
int SIR::get_i() const { return I; }
int SIR::get_r() const { return R; }

void SIR::set_s(int s) { S = s; }
void SIR::set_i(int i) { I = i; }
void SIR::set_r(int r) { R = r; }