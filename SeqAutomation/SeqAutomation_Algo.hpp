# include <vector>

# ifndef _SeqAutomation_Algo_
# define _SeqAutomation_Algo_

class SeqAutomation {
  private:
    int n, m;
    int *hd, *nxt, tot, rt;
    int **nxtChar;
    
    void buildAutomation(const std :: vector <int> &S) {
      for (int i = 0; i < m; ++ i) hd[i] = rt;
      for (int i = 0; i < n; ++ i) {
        int p = i + 2, c = S[i];
        nxt[p] = hd[c];
        for (int j = 0; j < m; ++ j)
          for (int k = hd[j]; k && nxtChar[k][c] == 0; k = nxt[k]) nxtChar[k][c] = p;
        hd[c] = p;
      }
    }
    
  public:
    SeqAutomation(int _m, const std :: vector <int> &S) {
      n = S.size(), m = _m; rt = 1;
      nxtChar = new int* [n + 2];
      for (int i = 0; i < n + 2; ++ i) {
        nxtChar[i] = new int [m];
        for (int j = 0; j < m; ++ j) nxtChar[i][j] = 0;
      }
      hd = new int [m];
      for (int i = 0; i < m; ++ i) hd[i] = 0;
      nxt = new int [n + 2];
      for (int i = 0; i < n + 2; ++ i) nxt[i] = 0;
      buildAutomation(S);
    }
    
    bool checkExists(const std :: vector <int> T) {
      int p = rt;
      for (int i = 0; i < T.size(); ++ i) {
        int c = T[i];
        if(nxtChar[p][c] == 0) return false;
        p = nxtChar[p][c];
      }
      return true;
    }
    
    ~SeqAutomation() {
      for (int i = 0; i < n + 2; ++ i)
        if(nxtChar[i] != nullptr) delete [] nxtChar[i];
      if(nxtChar != nullptr) delete [] nxtChar;
      if(hd != nullptr) delete [] hd;
      if(nxt != nullptr) delete [] nxt;
    }
};

# endif
