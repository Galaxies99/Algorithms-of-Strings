# include <iostream>
# include <vector>
# include "KMP_Algo.hpp"

using namespace std;

const int MAX = 2e5 + 10;
char S[MAX], T[MAX];

int main() {
  cin >> S >> T;
  
  KMPAlgorithm kmp(S, T);
  vector <int> vec(kmp.work());
  
  for (int i = 0; i < vec.size(); ++ i)
    cout << vec[i] << ' ';
  cout << endl;
  
  return 0;
}
