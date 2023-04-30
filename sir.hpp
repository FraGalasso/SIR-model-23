#ifndef SIR_HPP
#define SIR_HPP

class SIR {
 private:
  int S;
  int I;
  int R;

 public:
  explicit SIR(int s = 0, int i = 0, int r = 0);

  int get_s() const;
  int get_i() const;
  int get_r() const;

  void set_s(int s);
  void set_i(int i);
  void set_r(int r);
};

#endif