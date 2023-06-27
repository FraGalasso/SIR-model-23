#ifndef PERSONA_HPP
#define PERSONA_HPP

#include <random>
#include <vector>
#include <iostream>

enum class Stato { Susceptible, Infectious, Removed };

class Persona {
 private:
  int x;
  int px, py;
  Stato s;

 public:
  Persona(int X, int Px, int Py, Stato S) : x{X}, px{Px}, py{Py}, s{S} {};
  int GetX() const { return x; }
  int GetPx() const { return px; }
  int GetPy() const { return py; }
  void SetX(int y) { x = y; };
  void SetPx(int p) { px = p; }
  void SetPy(int p) { py = p; }
};

class Popolazione {
 private:
  std::vector<Persona> v;

 public:
  Popolazione(std::vector<Persona> V) : v{V} {};

  Persona GetPerson(int i) const { return v[i]; }

  int size() { return v.size(); }

  void evolve() {
    for (int i = 0; i < size(); ++i) {
      v[i] = GetPerson(i);
      int r = v[i].GetX();
      int px = v[i].GetPx();
      int py = v[i].GetPy();

      // int dx;
      // int dy;
      if (px == 1) {
        if ((r % 10) == 9) {
          // dx = -9;
          r -= 9;
        } else {
          // dx = 1;
          ++r;
        }
      }
      if (px == -1) {
        if (r % 10 == 0) {
          // dx = 9;
          r += 9;
        } else {
          --r;
        }
      }
      if (py == 1) {
        if (r >= 0 && r <= 9) {
          // dy = 90;
          r += 90;
        } else {
          // dy = -10;
          r -= 10;
        }
      }
      if (py == -1) {
        if (r >= 90 && r <= 99) {
          // dy = -90;
          r -= 90;
        } else {
          // dy = 10;
          r += 10;
        }
      }
      if ((px * px) != 1 && (py * py) != 1) {
        // dx = 0;
        // dy = 0;
        r = 0;
      }
      v[i].SetX(r);
    };
  };
  void random_distribution() {
    std::mt19937 gen(time(0));
    // random bit generator (mersenne twister)
    for (int i = 0; i < size(); ++i) {
      std::uniform_int_distribution<> x_distribution(0, 99);
      int x = x_distribution(gen);
      std::uniform_int_distribution<> px_distribution(-1, 1);
      int px = px_distribution(gen);
      std::uniform_int_distribution<> py_distribution(-1, 1);
      int py = py_distribution(gen);
      v[i].SetX(x);
      v[i].SetPx(px);
      v[i].SetPy(py);
    }
  }

  void collision() {
    for (int i = 0; i < size(); ++i) {
      v[i] = GetPerson(i);
      v[i + 1] = GetPerson(i + 1);
      int r = v[i].GetX();
      int px = v[i].GetPx();
      int py = v[i].GetPy();
      int r_ = v[i + 1].GetX();
      int px_ = v[i + 1].GetPx();
      int py_ = v[i + 1].GetPy();
      if (r == r_) {
        px = -px;
        px_ = -px_;
        py = -py;
        py_ = -py; 

        /* if (px < 0) {
           --r;
           ++r_;
         }
         if (px > 0) {
           ++r;
           --r_;
         }
         if (py > 0) {
           r += 10;
           r_ -= 10;
         }
         if (py < 0) {
           r -= 10;
           r_ += 10;
         }
      }; */
      }
      
        if (px == 1) {
          if ((r % 10) == 9) {
            r -= 9;
          } else {
            ++r;
          }
        }
        if (px == -1) {
          if (r % 10 == 0) {
            r += 9;
          } else {
            --r;
          }
        }
        if (py == 1) {
          if (r >= 0 && r <= 9) {
            r += 90;
          } else {
            r -= 10;
          }
        }
        if (py == -1) {
          if (r >= 90 && r <= 99) {
            r -= 90;
          } else {
            r += 10;
          }
        }
        if ((px * px) != 1 && (py * py) != 1) {
          std::cout<<"Errore"<<'\n'; //da sistemare
        }
        
        v[i].SetX(r);
        v[i+1].SetX(r_);
        v[i].SetPx(px);
        v[i].SetPy(py);
        v[i + 1].SetPx(px_);
        v[i + 1].SetPy(py_);
        
       /* if(r != r_){
        v[i].SetX(r);
        v[i+1].SetX(r_);
        } */
       /* v[i].SetPx(px);
        v[i].SetPy(py);
        v[i + 1].SetPx(px_);
        v[i + 1].SetPy(py_);
        //v[i + 1].SetX(r_);
        */
        
      }
    };
  };


#endif