# include <iostream>
# include <vector>
# include <string.h>
# include "SeqAutomation_Algo.hpp"

using namespace std;

const int MAX = 1e6 + 10;

char S[MAX];
int n;
vector <int> vec;

int main() {
  cin >> S; n = strlen(S);
  vec.resize(n);
  for (int i = 0; i < n; ++ i) vec[i] = S[i] - 'a';
  
  SeqAutomation seqauto(26, vec);
  
  int m;
  cin >> m;
  while(m --) {
    cin >> S; 
    int p = strlen(S);
    vec.clear(); vec.resize(p);
    for (int i = 0; i < p; ++ i) vec[i] = S[i] - 'a';
    cout << (seqauto.checkExists(vec) ? "Yes" : "No") << endl;
  }
  
  return 0;
}
