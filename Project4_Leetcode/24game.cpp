#include <iostream>
#include <vector>
using namespace std;
bool solve(vector<double> &numbers, int s);
double checker = 0.00001; // variable to check with when 1 item left
bool judgePoint24(vector<int> &nums) {
  vector<double> numsDouble(nums.begin(), nums.end()); // changing int to double
  int sizeofArray = numsDouble.size();
  return solve(numsDouble, sizeofArray);
}
vector<double> getAllExpressions(
    double a, double b) // method to get all posible solution by using two cards
{
  return {a + b, a - b, b - a, a * b, a / b, b / a};
}
bool solve(vector<double> &numbers,
           int s) // helper function with vector of doubles and size of vector
{
  if (s == 1)                              // if one item left
    return abs(numbers[0] - 24) < checker; // return true or false
  for (int i = 0; i < s; i++)              // from 0 to size of Array
  {
    for (int j = i + 1; j < s; j++) // from 1 to size of Array
    {
      double index1 = numbers[i];  // taking 1 element
      double index2 = numbers[j];  // taking 2 element
      numbers[j] = numbers[s - 1]; // second number becomes last one
      for (double x : getAllExpressions(index1, index2)) // for 6 results
      {
        numbers[i] = x;            // we put each result on first place
        if (solve(numbers, s - 1)) // and try solve it again
          return true;
      }
      numbers[i] = index1; // if not solved we put index1 to its place
      numbers[j] = index2; // if not solved we put index2 to its place
    }
  }
  return false;
}

int main() {
  vector<int> vec = {1, 2, 1, 2};
  vector<int> vec1 = {4, 1, 8, 7};
  cout << judgePoint24(vec) << endl;
  cout << judgePoint24(vec1) << endl;
  return 0;
}

