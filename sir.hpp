#ifndef SIR_HPP
#define SIR_HPP

struct Parameters {
  // infection probability
  double const beta;

  // removal probability
  double const gamma;
};

class SIR {
 private:
  // susceptibles
  int S;

  // infectious
  int I;

  // removed
  int R;

 public:
  // constructor, defined at line 5 of sir.cpp
  SIR(int s = 0, int i = 0, int r = 0);

  // getting susceptibles, defined at line 12 of sir.cpp
  int get_s() const;

  // getting infectious, defined at line 14 of sir.cpp
  int get_i() const;

  // getting removed, defined at line 16 of sir.cpp
  int get_r() const;

  // setting susceptibles, defined at line 18 of sir.cpp
  void set_s(int s);

  // setting infectious, defined at line 20 of sir.cpp
  void set_i(int i);

  // setting removed, defined at line 22 of sir.cpp
  void set_r(int r);

  // equality operator, defined at line 24 of sir.cpp
  bool operator==(const SIR& m);
};

#endif