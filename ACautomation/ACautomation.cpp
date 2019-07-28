# include <iostream>
# include <vector>
# include <string>
# include "ACautomation_Algo.hpp"

using namespace std;

const int MAX = 2e5 + 10;

int n;
vector <string> vec;
string s;
char passage[MAX];

int main() {
  cin >> n;
  for (int i = 0; i < n; ++ i) {
    cin >> s;
    vec.push_back(s); 
  }
  cin >> passage;
  
  ACautomation ACauto(vec, passage);
  vector <int> cnt(ACauto.work());
  
  for (int i = 0; i < n; ++ i) cout << cnt[i] << ' ';
  cout << endl;
  return 0;
}
