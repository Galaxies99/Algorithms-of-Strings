# include <iostream>
# include <vector>
# include "Manacher_Algo.hpp"

using namespace std;

const int MAX = 2e5 + 10;
char S[MAX];

int main() {
  cin >> S;
  
  ManacherAlgorithm manacher(S);
  
  cout << manacher.work() << endl;
  
  return 0;
}
