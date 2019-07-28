# include <vector>
# include <string.h>

# ifndef _extKMP_Algo_
# define _extKMP_Algo_

class extKMPAlgorithm {
  private:
    int *nxt;
    const char *S, *T;
    int lenS, lenT;
    std :: vector <int> extend;
    
    void getNext() {
      int a = 0, p = 0;
      nxt[0] = lenT;
      for (int i = 1; i < lenT; ++ i) {
        if (i >= p || i + nxt[i - a] >= p) {
          if (i >= p) p = i;
          while (p < lenT && T[p] == T[p - i]) 
            ++ p;
          nxt[i] = p - i;
          a = i;
        } else nxt[i] = nxt[i - a];
      }
    }
    
    void extKMP() {
      int a = 0, p = 0;
      for (int i = 0; i < lenS; ++ i) {
        if (i >= p || i + nxt[i - a] >= p) {
          if (i >= p) p = i;
          while (p < lenS && p - i < lenT && S[p] == T[p - i]) 
            ++ p;
          extend[i] = p - i;
          a = i;
        } else extend[i] = nxt[i - a];
      }
    }
    
  public:
    extKMPAlgorithm(char *_S, char *_T) {
      S = _S, T = _T;
      lenS = strlen(S); lenT = strlen(T);
      nxt = new int [lenT];
      if(nxt == nullptr) throw "Error";
      extend.resize(lenS); 
    }
    
    const std :: vector <int>& work() {
      getNext();
      extKMP();
      return extend;
    }
    
    ~extKMPAlgorithm() {
      if(nxt != nullptr) delete [] nxt;
    }
};

# endif
