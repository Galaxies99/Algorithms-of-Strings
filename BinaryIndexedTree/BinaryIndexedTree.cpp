# include <iostream>
# include "BinaryIndexedTree_Algo.hpp"

using namespace std;

const int MAX = 2e5 + 10;

int n, a[MAX];

int main() {
  int m, op, x, y, d;
  cin >> n >> m;
  
  for (int i = 1; i <= n; ++ i) cin >> a[i];
   
  BITplus bit(n);
  
  for (int i = 1; i <= n; ++ i) bit.add(i, i, a[i]);
  
  while(m --) {
    cin >> op >> x;
    if(op == 1) cin >> y >> d, bit.add(x, y, d);
    else cout << bit.sum(x, x) << endl;
  }
  
  return 0;
}
