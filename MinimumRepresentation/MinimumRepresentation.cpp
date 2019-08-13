# include <iostream>
# include <vector>
# include <string.h>
# include "MinimumRepresentation_Algo.hpp"

using namespace std;

const int MAX = 1e6 + 10;

char S[MAX];
int n;
vector <int> vec;

int main() {
  cin >> S;
  n = strlen(S);
  vec.resize(n);
  for (int i = 0; i < n; ++ i) vec[i] = S[i];
  
  MinimumRepresentation calc(vec);
  
  vector <int> rec(calc.work());
  
  for (int i = 0; i < rec.size(); ++ i)
    cout << (char) rec[i];
  cout << endl;
  return 0;
}
