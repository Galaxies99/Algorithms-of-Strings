# include <iostream>
# include <vector>
# include <string.h>
# include "PalindromicTree_Algo.hpp"

using namespace std;

const int MAX = 1e6 + 10;

char S[MAX];
int n;
vector <int> vec;

int main() {
  cin >> S;
  n = strlen(S);
  vec.resize(n);
  for (int i = 0; i < n; ++ i) vec[i] = S[i] - 'a';
  
  PalindromicTree palin(26, vec);
  
  vector < pair <int, int> > rec(palin.getLengthTimes());
  
  for (int i = 0; i < rec.size(); ++ i)
    cout << "length: " << rec[i].first << ", times:" << rec[i].second << endl;
  cout << "total times: " << palin.countNumber();
  return 0;
}
