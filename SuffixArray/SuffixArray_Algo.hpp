# include <vector>
# include <iostream>
# include <string.h>

# ifndef _SuffixArray_Algo_
# define _SuffixArray_Algo_

class SuffixArray {
  private:
    const int M;
    int n;
    std :: vector <int> S;
    std :: vector <int> sa;
    std :: vector <int> rk; 
    int *bucket, *bucket2, *A, *B, *t; 
    
    void work() {
      bucket = new int [std :: max(M, n + 3)];
      bucket2 = new int [n + 5];
      t = new int [n + 5];
      A = new int [n + 5];
      B = new int [n + 5];
      
      for (int i = 0; i < M; ++ i) bucket[i] = 0; 
      for (int i = 1; i <= n; ++ i) bucket[S[i]] ++;
      for (int i = 1; i < M; ++ i) bucket[i] += bucket[i-1];
      for (int i = n; i; -- i) sa[bucket[S[i]] --] = i;
      
      rk[sa[1]] = 1;
      for (int i = 2; i <= n; ++ i) {
        rk[sa[i]] = rk[sa[i-1]];
        if(S[sa[i]] != S[sa[i-1]]) ++ rk[sa[i]];
      }
      
      for (int len = 1; rk[sa[n]] < n; len <<= 1) {   
        for (int i = 1; i <= n; ++ i) bucket[i] = bucket2[i] = 0;
        for (int i = 1; i <= n; ++ i) {
          A[i] = rk[i]; B[i] = ((i + len <= n) ? rk[i + len] : 0);
          bucket[A[i]] ++; bucket2[B[i]] ++;
        }
        for (int i = 1; i <= n; ++ i) bucket2[i] += bucket2[i-1];
        for (int i = n; i; --i) t[bucket2[B[i]] --] = i;
        for (int i = 1; i <= n; ++ i) bucket[i] += bucket[i-1];
        for (int i = n; i; --i) sa[bucket[A[t[i]]] --] = t[i];
        
        rk[sa[1]] = 1;
        for (int i = 2; i <= n; ++ i) {
          rk[sa[i]] = rk[sa[i-1]];
          if(A[sa[i]] != A[sa[i-1]] || B[sa[i]] != B[sa[i-1]]) ++ rk[sa[i]];
        }
      }
      
      delete []bucket;
      delete []bucket2;
      delete []t;
      delete []A;
      delete []B;
    }
    
  public:
    SuffixArray(int _M, const std :: vector <int> &vec) : M(_M) {
      S.push_back(0);
      for (int i = 0; i < vec.size(); ++ i) S.push_back(vec[i]);
      n = vec.size();
      rk.resize(n + 1);
      sa.resize(n + 1);
      work();
    }
    
    const std :: vector <int>& getRank() {
      return rk;
    }
    
    const std :: vector <int>& getSA() {
      return sa;
    }
    
    ~SuffixArray() {}
};

# endif
