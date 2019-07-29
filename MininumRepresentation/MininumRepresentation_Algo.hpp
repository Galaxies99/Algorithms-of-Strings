# include <vector>

# ifndef _MininumRepresentation_Algo_
# define _MininumRepresentation_Algo_

class MininumRepresentation {
  private:
    int n;
    std :: vector <int> S;
    std :: vector <int> res;
    
    void getResult() {
      int i = 0, j = 1, k = 0, p;
      while(i < n && j < n && k < n) {
        p = S[(i + k) % n] - S[(j + k) % n];
        if(p == 0) ++ k;
        else {
          if(p > 0) i += k + 1;
          else j += k + 1;
          if(i == j) ++ j;
          k = 0;
        }
      }
      int start = i < j ? i : j;
      for (int j = 0; j < n; ++ j)
        res.push_back(S[(start + j) % n]);
    }
     
  public:
    MininumRepresentation(const std :: vector <int> &_S) : S(_S) {
      n = S.size();
      getResult();
    }
    
    const std :: vector <int>& work() {
      return res;
    }
    
    ~MininumRepresentation() {}
};

# endif
