# include <vector>
# include <string.h>

# ifndef _KMP_Algo_
# define _KMP_Algo_

class KMPAlgorithm {
  private:
    int *nxt;
    const char *S, *T;
    int lenS, lenT;
    std :: vector <int> pos;
      
    void getNext() {
      nxt[0] = -1;
      int k = -1;
      for (int i = 1; i < lenT; ++i) {
        while(k != -1 && T[k+1] != T[i]) k = nxt[k];
        if(T[k+1] == T[i]) ++ k;
        nxt[i] = k;
      }
    }
    
    void KMP() {
      int k = -1;
      for (int i = 0; i < lenS; ++ i) {
        while(k != -1 && T[k+1] != S[i]) k = nxt[k];
        if(T[k+1] == S[i]) ++ k;
        if(k == lenT - 1) {
          pos.push_back(i - k);
          k = nxt[k];
        }
      }
    }
  
  public:
    KMPAlgorithm(char *_S, char *_T) {
      S = _S, T = _T;
      lenS = strlen(S); lenT = strlen(T);
      nxt = new int [lenT];
      if(nxt == nullptr) throw "Error!";
    }
    
    const std :: vector <int>& work() {
      getNext();
      KMP();
      return pos;
    }
    
    ~ KMPAlgorithm() {
      if(nxt != nullptr) delete [] nxt;
    }
};
    
# endif
