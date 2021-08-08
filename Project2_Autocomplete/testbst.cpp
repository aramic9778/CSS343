// /**
//  * Testing BST - Binary Search Tree functions
//  *
//  * This file has series of tests for BST
//  * Each test is independent and uses assert statements
//  * Test functions are of the form
//  *
//  *      test_netidXX()
//  *
//  * where netid is UW netid and XX is the test number starting from 01
//  *
//  * Test functions can only use the public functions from BST
//  * testBSTAll() is called from main in main.cpp
//  * testBSTAll calls all other functions
//  * @author Multiple
//  * @date ongoing
//  */

#include "bstmap.h"
#include <cassert>
#include <sstream>

using namespace std;

// global value for testing
// NOLINTNEXTLINE
stringstream globalSS;

// need to reset SS before calling this
void printer(const BSTMap::value_type &p) {
  globalSS << "[" << p.first << "=" << p.second << "]";
}

// // Testing == and []
void test01() {
  cout << "Starting test01" << endl;
  cout << "* Testing ==, !=, [] and copy constructor" << endl;
  BSTMap b1;
  auto val = b1["hello"];
  assert(val == 0);
  b1["hello"] = 5;
  val = b1["hello"];
  assert(val == 5);
  b1["world"] = 42;

  BSTMap b2;
  assert(b1 != b2);
  b2["hello"] = 5;
  b2["world"] = 42;
  assert(b1 == b2);

  BSTMap b3(b2);
  assert(b1 == b3);
  cout << "Ending tes01" << endl;
}

// Testing traversal
void test02() {
  cout << "Starting test02" << endl;
  cout << "* Testing traversal" << endl;
  BSTMap b;
  b["x"] = 10;
  b["f"] = 5;
  b["b"] = 3;
  b["e"] = 4;
  b["z"] = 50;
  // cout << b;

  globalSS.str("");
  b.inorder(printer);
  string order = globalSS.str();
  assert(order == "[b=3][e=4][f=5][x=10][z=50]");

  globalSS.str("");
  b.preorder(printer);
  order = globalSS.str();
  assert(order == "[x=10][f=5][b=3][e=4][z=50]");

  globalSS.str("");
  b.postorder(printer);
  order = globalSS.str();
  assert(order == "[e=4][b=3][f=5][z=50][x=10]");
  cout << "Ending test02" << endl;
}

// Testing rebalance
void test03() {
  cout << "Starting test03" << endl;
  cout << "* Testing rebalance" << endl;
  BSTMap b;
  b["1"] = 1;
  b["2"] = 2;
  b["3"] = 3;
  b["4"] = 4;
  b["5"] = 5;
  b["6"] = 6;
  assert(b.height() == 6);
  // cout << b << endl;
  b.rebalance();
  assert(b.height() == 3);
  // cout << b << endl;
  b.clear();
  assert(b.height() == 0);
  cout << "Ending test03" << endl;
}

void testEmpty() {
  cout << "Start testing method empty()" << endl;
  BSTMap b;
  assert(b.empty());
  cout << "End testing method empty()" << endl;
}

void testSize() {
  cout << "Start testing method size()" << endl;
  BSTMap b;
  assert(b.empty());
  b["a"] = 1;
  assert(b.size() == 1);
  cout << "End testing method size()" << endl;
}

void testCount() {
  cout << "Start testing method count()" << endl;
  BSTMap b;
  assert(b.count("a") == 0);
  b["a"] = 10;
  assert(b.count("a") == 1);
  cout << "End testing method count()" << endl;
}

void testHeight() {
  cout << "Start testing method height()" << endl;
  BSTMap b;
  assert(b.height() == 0);
  b["h"] = 8;
  assert(b.height() == 1);
  b["a"] = 1;
  assert(b.height() == 2);
  cout << "End testing method height()" << endl;
}

void testSquareBracketOperator() {
  cout << "Start testing method operator[]" << endl;
  BSTMap b;
  b["h"] = 8;
  b["z"] = 26;
  b["a"] = 1;
  b["h"] = 9;
  b["z"] = 27;
  b["a"] = 2;
  cout << "End testing method operator[]" << endl;
}

void testCopyConstructor() {
  cout << "Start testing copy constructor" << endl;
  BSTMap b;
  BSTMap c(b);
  b["h"] = 8;
  b["z"] = 26;
  b["a"] = 1;
  BSTMap d(b);
  cout << "End testing copy constructor" << endl;
}

void testTreePrinterHelper() {
  cout << "Start testing BSTMap printer functions" << endl;
  BSTMap b;
  cout << b << endl;
  b["h"] = 8;
  b["z"] = 26;
  b["a"] = 1;
  cout << b << endl;
  b["c"] = 3;
  cout << b << endl;
  cout << "End testing BSTMap printer functions" << endl;
}

// // Calling all test functions
void testBSTAll() {
  test01();
  test02();
  test03();
  // TODO(student) Add more tests
  testEmpty();
  testSize();
  testCount();
  testHeight();
  testSquareBracketOperator();
  testCopyConstructor();
  testTreePrinterHelper();
}