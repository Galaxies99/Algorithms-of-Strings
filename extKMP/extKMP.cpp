# include <iostream>
# include <vector>
# include "extKMP_Algo.hpp"

using namespace std;

const int MAX = 2e5 + 10;
char S[MAX], T[MAX];

int main() {
  cin >> S >> T;
  
  extKMPAlgorithm extkmp(S, T);
  vector <int> vec(extkmp.work());
  
  for (int i = 0; i < vec.size(); ++ i)
    cout << vec[i] << ' ';
  cout << endl;
  
  return 0;
}
