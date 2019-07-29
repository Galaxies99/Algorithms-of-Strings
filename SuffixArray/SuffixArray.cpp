# include <iostream>
# include <string.h>
# include <vector>
# include "SuffixArray_Algo.hpp"

using namespace std;

const int MAX = 1e6 + 10;
char S[MAX];
vector <int> vec;

int main() {
  cin >> S;
  int n = strlen(S);
  vec.resize(n);
  for (int i = 0; i < n; ++ i) vec[i] = S[i];
  
  SuffixArray SA(256, vec);
  
  vector <int> ans(SA.getSA());
  
  for (int i = 1; i <= n; ++ i) cout << ans[i] << ' ';
  
  return 0;
}
