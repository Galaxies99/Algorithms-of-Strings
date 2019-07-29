# include <vector>

# ifndef _PalindromicTree_Algo_
# define _PalindromicTree_Algo_

class PalindromicTree {
  private:
    int M;
    struct Node {
      int M;
      int len, cnt;
      Node **son;
      Node *fail;
      
      Node(int M, int _len, Node *_fail = nullptr, int _cnt = 0) : M(M) {
        len = _len;
        cnt = _cnt;
        fail = _fail;
        son = new Node* [M];
        for (int i = 0; i < M; ++ i) son[i] = nullptr;
      }
      
      ~ Node() {
        for (int i = 0; i < M; ++ i) 
          if(son[i] != nullptr) delete son[i];
        delete []son;
      }
    }; 
    
    Node *even, *odd;
    std :: vector <int> S;
    std :: vector <Node*> order;
    std :: vector < std :: pair <int, int> > rec;
    
    Node* getFail(Node *x, int n) {
      if(x == nullptr) x = even;
      while (S[n - (x -> len) - 1] != S[n]) x = x -> fail;
      return x;
    }
    
    void buildTree() {
      Node *p = even;
      for (int i = 1; i < S.size(); ++ i) {
        int c = S[i];
        p = getFail(p, i);
        if(p -> son[c] == nullptr) {
          p -> son[c] = new Node(M, p -> len + 2);
          order.push_back(p -> son[c]);
          Node *q = getFail(p -> fail, i);
          if(q -> son[c] == nullptr || q -> son[c] == p -> son[c]) p -> son[c] -> fail = even;
          else p -> son[c] -> fail = q -> son[c];
        }
        p = p -> son[c]; 
        p -> cnt ++;
      }
    }
    
    void countCnt() {
      for (int i = order.size() - 1; ~i; -- i) {
        Node *p = order[i];
        if(p != odd) p -> fail -> cnt += p -> cnt; 
      }
    }
    
  public:
    PalindromicTree(int _M, const std :: vector <int> &T) : M(_M) {
      S.push_back(-1);
      for (int i = 0; i < T.size(); ++ i) S.push_back(T[i]);
      order.clear();
      odd = new Node(M, -1);
      even = new Node (M, 0, odd);
      order.push_back(even);
      order.push_back(odd);
      buildTree(); 
      countCnt();
    }
    
    int countNumber() {
      return odd -> cnt;
    }
    const std :: vector < std :: pair <int, int> >& getLengthTimes() {
      rec.clear();
      for (int i = 2; i < order.size(); ++ i) {
        Node *p = order[i];
        rec.push_back(std :: make_pair(p -> len, p -> cnt));
      }
      return rec;
    }
    
    ~PalindromicTree() {
      delete odd;
      delete even;
    }
};

# endif
