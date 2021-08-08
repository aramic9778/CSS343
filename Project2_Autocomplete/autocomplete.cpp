#include "autocomplete.h"
#include <algorithm>
#include <fstream>

using namespace std;

void testBSTAll();

void Autocomplete::readFile(const string &fileName) {
  ifstream ifs(fileName);
  if (!ifs) {
    cout << "Bad filename!" << endl;
    return;
  }
  int n;
  ifs >> n;
  int k;
  char ch;
  string s;
  char s0[256];

  phrases.clear();
  for (int i = 0; i < n; i++) {
    ifs >> k;
    do {
      ifs >> ch;
    } while (ch == ' ' || ch == '\t');
    s0[0] = ch;
    ifs.getline(s0 + 1, 256);
    s = s0;
    // cout << k << " ;  " << s << endl;
    phrases[s] = k;
  }

  ifs.close();
  phrases.rebalance();
  // cout << phrases << endl;
}

bool Autocomplete::sortByWeight(BSTMap::value_type &a, BSTMap::value_type &b) {
  return a.second > b.second;
}

vector<BSTMap::value_type>
Autocomplete::complete(const BSTMap::key_type &prefix) const {
  vector<BSTMap::value_type> v;
  v = phrases.getAll(prefix);
  sort(v.begin(), v.end(), sortByWeight);
  return v;
}
