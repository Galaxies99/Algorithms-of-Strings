# include <string.h>
# include <iostream>

# ifndef _Manacher_Algo_
# define _Manacher_Algo_
class ManacherAlgorithm {
  private:
    char *S;
    int lenS, *p;
  
  public:
    ManacherAlgorithm(char *_S) {
      lenS = strlen(_S); 
      
      lenS = (lenS << 1) + 2;
      
      S = new char [lenS + 3];
      if(S == nullptr) throw "Error!";
      
      S[0] = '$';
      S[1] = '#';
      for (int i = 2; i < lenS; i += 2) {
        S[i] = _S[(i - 2) >> 1];
        S[i + 1] = '#';
      }
      S[lenS] = '\0';
       
      p = new int [lenS];
      if(p == nullptr) throw "Error!";
    }
    
    int work() {
      int mx = 0, id, res = -1;
      for (int i = 1; i < lenS; ++ i) {
        if(i < mx) p[i] = std :: min(p[id + id - i], mx - i);
        else p[i] = 1;
        
        while(i + p[i] < lenS && i - p[i] >= 0 && S[i + p[i]] == S[i - p[i]]) ++ p[i];
        
        if (mx < i + p[i]) {
          id = i;
          mx = i + p[i];
        }
        
        res = std :: max(res, p[i] - 1);
      }
      return res;
    }
    
    ~ ManacherAlgorithm() {
      if(p != nullptr) delete [] p;
      if(S != nullptr) delete [] S;
    }
};

# endif
