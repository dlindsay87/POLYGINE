#include "thing.h"

Thing::Thing(float &m, fltvec &v, fltvec &p, Form &f)
  : _mass(m), _velocity(v), _position(p), _form(f) {
    cout << "I am a thing." << endl;
}
