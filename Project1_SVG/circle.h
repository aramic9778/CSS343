/**
 * SVG Circle
 **/

#ifndef CIRCLE_H
#define CIRCLE_H

#include "svg.h"
#include <iostream>
#include <string>

using namespace std;

class Circle : public SVG {

public:
  // operator<< equivalent to write the object out
  ostream &write(ostream &out) const override;

  // operator>> equivalent to read the object contents
  istream &read(istream &in) override;

private:
  // coordinates for center of circle
  int cx{0}, cy{0}, sw{5}; // stroke-width added

  // radius of circle
  int radius{0};

  // color of circle
  string color{"black"}, stroke{"black"}; // stroke color added
};

#endif
