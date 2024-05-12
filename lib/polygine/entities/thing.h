#ifndef THING_H
#define THING_H

#include "utils/typer.h"
#include "entities/form.h"

class Thing {
private:
  float _mass;
  fltvec _velocity;
  fltvec _position;

  Form _form;

public:
  Thing(float &m, fltvec &v, fltvec &p, Form &f);

  float getMass() {return _mass;}
  fltvec getPosition() {return _position;}
  fltvec getVelocity() {return _velocity;}

};

#endif
