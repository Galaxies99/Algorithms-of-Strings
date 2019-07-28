# include <queue>
# include <vector>
# include <string>
# include <string.h> 

# ifndef _ACautomation_Algo_
# define _ACautomation_Algo_

class ACautomation {
  private:
    struct TrieNode {
      char c;
      TrieNode *par, *ch[256], *fail;
      int id;

      TrieNode(char _c = 0, TrieNode *_par = nullptr, int _id = -1, TrieNode *_fail = nullptr) {
        c = _c; id = _id; par = _par; fail = _fail;
        for (int i = 0; i < 256; ++ i) ch[i] = nullptr;
      }
      
      ~TrieNode() {
        for (int i = 0; i < 256; ++ i)
          if (ch[i] != nullptr) delete ch[i]; 
      }
    };
    
    const char *passage;
    std :: vector <std :: string> words;
    std :: vector <int> cnt; 
    TrieNode *rt;
    
    void insertWord(std :: string word, int id) {
      TrieNode *p = rt;
      for (int i = 0, length = word.length(); i < length; ++ i) {
        unsigned char c = (unsigned char)word[i];
        if(p -> ch[c] == nullptr) 
          p -> ch[c] = new TrieNode(c, p);
        p = p -> ch[c];
      }
      p -> id = id;
    }
    
    void addWordVec() {
      for (int i = 0; i < words.size(); ++ i)
        insertWord(words[i], i);
    }
    
    void getFail() {
      std :: queue <TrieNode*> que;
      while(! que.empty()) que.pop();
       
      que.push(rt);
      while(! que.empty()) {
        TrieNode *top = que.front(); que.pop();
        for (int i = 0; i < 255; ++ i) {
          if(top -> ch[i] != nullptr) {
            if(top == rt) top -> ch[i] -> fail = rt;
            else {
              TrieNode *p = top -> fail;
              while(p != nullptr) {
                if(p -> ch[i] != nullptr) {
                  top -> ch[i] -> fail = p -> ch[i];
                  break;
                }
                p = p -> fail;
              }
              if(p == nullptr) top -> ch[i] -> fail = rt;
            }
            que.push(top -> ch[i]);
          }
        }
      }
    }
    
    void getMatch() {
      TrieNode *p = rt;
      for (int i = 0; passage[i]; ++i) {
        unsigned char c = passage[i];
        while(p -> ch[c] == nullptr && p != rt) p = p -> fail;
        p = p -> ch[c];
        if(p == nullptr) p = rt;
        TrieNode *t = p;
        while(t != rt) {
          if(t -> id != -1) cnt[t -> id] ++;
          t = t -> fail;
        }
      }
    }
  
  public:
    ACautomation(const std :: vector <std :: string> &_words, char *S) : words(_words) {
      passage = S;
      rt = new TrieNode();
      cnt.resize(words.size());
      for (int i = 0; i < cnt.size(); ++ i) cnt[i] = 0;
    }
    
    const std :: vector <int>& work() {
      addWordVec();
      getFail();
      getMatch(); 
      return cnt;
    }
    
    ~ACautomation() {
      if(rt != nullptr) delete rt;
    }
};

# endif
