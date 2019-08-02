
# ifndef _BinaryIndexedTree_Algo_ 
# define _BinaryIndexedTree_Algo_

class BIT {
  # define lowbit(x) (x & (-x)) 
  private:
    int n;
    long long *c;

  public:
    BIT(int _n, int *a) {
      n = _n;
      c = new long long[n + 1];
      if(a != nullptr)
        for (int i = 1; i <= n; ++ i)
          add(i, a[i]);
    }  
        
    void add(int x, long long d) {
      for (; x <= n; x += lowbit(x)) c[x] += d; 
    }
    
    long long sum(int x) {
      long long res = 0;
      for (; x; x -= lowbit(x)) res += c[x];
      return res;
    }
    
    long long sum(int l, int r) {
      if(l > r) return 0;
      return sum(r) - sum(l-1);
    }
  
    ~BIT() {
      if(c != nullptr) delete c;
    }
  # undef lowbit 
};

class BITplus {
  private:
    BIT b, ib;
  public:
    BITplus(int _n) : b(_n, nullptr), ib(_n, nullptr) {}
    
    void add(int l, int r, int d) {
      b.add(l, d); b.add(r+1, -d);
      ib.add(l, 1ll * d * l);
      ib.add(r+1, -1ll * d * (r+1));
    }

    long long sum(int x) {
      return 1ll * (x+1) * b.sum(x) - ib.sum(x); 
    }
    
    long long sum(int l, int r) {
      return sum(r) - sum(l-1);
    }
};

# endif
