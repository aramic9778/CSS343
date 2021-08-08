#include "circle.h"
#include <fstream>
#include <iostream>

using namespace std;

// operator<< equivalent to write the object out
ostream &Circle::write(ostream &out) const {
  out << "      <circle ";
  out << "cx=\"" << cx << "\" ";
  out << "cy=\"" << cy << "\" ";
  out << "r=\"" << radius << "\" ";
  out << "stroke=\"" << stroke << "\" ";   // I added stroke color
  out << "stroke-width=\"" << sw << "\" "; // I added stroke - width for circle
  out << "fill=\"" << color << "\" ";
  out << " />" << endl;

  return out;
}

// operator>> equivalent to read the object contents
istream &Circle::read(istream &in) {
  in >> cx >> cy >> radius >> stroke >> sw >> color;
  return in;
}