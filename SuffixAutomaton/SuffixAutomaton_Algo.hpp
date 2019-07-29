# include <vector>
# include <iostream>

# ifndef _SuffixAutomaton_Algo_
# define _SuffixAutomaton_Algo_

// There are many applications of SAM, so all public to use easily.
class SuffixAutomaton {
  public:
    struct state {
      int len;
      state *son[256], *link;
      
      state(int _len = 0, state *_link = nullptr) {
        len = _len; link = _link;
        for (int i = 0; i < 256; ++ i)
          son[i] = nullptr;
      }
      
      ~state() {
          if(link != nullptr) delete link;
      }
    }; 
    
    bool cmp(state *a, state *b) {
      return (a -> len) > (b -> len); 
    }
    
    state *rt, *lst;
    
    std :: vector <state*> order;
    
    void extend(unsigned char c) {
      state *cur = new state(lst -> len + 1, nullptr);
      order.push_back(cur);
      state *p = lst, *q, *clone;
      for (; p != nullptr && p -> son[c] == nullptr; p = p -> link) p -> son[c] = cur;
      if(p == nullptr) cur -> link = rt;
      else {
        q = p -> son[c];
        if(q -> len == p -> len + 1) cur -> link = q;
        else {
          clone = new state(p -> len + 1, q -> link);
          order.push_back(clone);
          for (int i = 0; i < 256; ++ i) clone -> son[i] = q -> son[i];
          for (; p != nullptr && p -> son[c] == q; p = p -> link) p -> son[c] = clone;
          q -> link = clone, cur -> link = clone; 
        }
      }
      lst = cur;
    } 
    
    SuffixAutomaton(const char *S) {
      order.clear();
      rt = new state(0);
      lst = rt; order.push_back(rt);
      for (int i = 0; S[i]; ++ i) extend((unsigned char)S[i]);
    }
    
    ~SuffixAutomaton() {
      if(lst != nullptr) delete lst;
    }
};

# endif
