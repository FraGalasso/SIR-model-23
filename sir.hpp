#ifndef SIR_HPP
#define SIR_HPP

class SIR {
 private:
  int S;
  int I;
  int R;

 public:
  SIR(int s, int i, int r) : S{s}, I{i}, R{r} {};

  int Supsceptibles() { return S; };
  int Infected() { return I; };
  int Removed() { return R; };

  void set_s(int s) { S = s; }
  void set_i(int i) { I = i; }
  void set_r(int r) { R = r; }
};

#endif