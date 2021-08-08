#include "line.h"
#include <fstream>
#include <iostream>

using namespace std;

// operator<< equivalent to write the object out
ostream &Line::write(ostream &out) const {
  out << "      <line ";
  out << "x1=\"" << x1 << "\" ";
  out << "y1=\"" << y1 << "\" ";
  out << "x2=\"" << x2 << "\" ";
  out << "y2=\"" << y2 << "\" ";
  out << "stroke=\"" << color << "\" ";    // I also added color of stroke
  out << "stroke-width=\"" << sw << "\" "; // I added stroke-width for line
  out << " />" << endl;

  return out;
}

// operator>> equivalent to read the object contents
istream &Line::read(istream &in) {
  in >> x1 >> y1 >> x2 >> y2 >> sw >> color;
  return in;
}