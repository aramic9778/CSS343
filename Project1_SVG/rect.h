/**
 * SVG RECT
 **/

#ifndef RECT_H
#define RECT_H

#include "svg.h"
#include <iostream>
#include <string>

using namespace std;

class Rect : public SVG {

public:
  // operator<< equivalent to write the object out
  ostream &write(ostream &out) const override;

  // operator>> equivalent to read the object contents
  istream &read(istream &in) override;

private:
  // coordinates of begining of rectangle, width, height, and stroke-width
  int x{0}, y{0}, width{0}, height{0}, sw{0};

  // color of rectangle and stroke
  string color{"black"}, stroke{"none"};
};

#endif