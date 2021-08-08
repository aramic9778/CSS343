/**
 * SVG Ellipse
 **/

#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "svg.h"
#include <iostream>
#include <string>

using namespace std;

class Ellipse : public SVG {

public:
  // operator<< equivalent to write the object out
  ostream &write(ostream &out) const override;

  // operator>> equivalent to read the object contents
  istream &read(istream &in) override;

private:
  // coordinates for center of circle
  int cx{0}, cy{0}, rx{0}, ry{0}; // stroke-width added

  // color of circle
  string color{"black"};
};

#endif
