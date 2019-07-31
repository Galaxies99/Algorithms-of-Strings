// 596 / 1600 LZ78 with simple division.
# include "core.h"
# include <vector>
# include <queue>
# include <deque> 
 
typedef unsigned char uchar;
 
const bool IS_DIV = 1;
constexpr int NODE_MAXSIZE = 1024 * 512 + 8;
const int MAX_BIT = 15;
 
struct TrieNode {
  int id; uchar ch;
  TrieNode *son[256];
  TrieNode *par;
  
  TrieNode(int _id = 0, TrieNode *_par = nullptr, uchar _ch = 0) {
    id = _id; par = _par; ch = _ch;
    for (int i = 0; i < 256; ++ i) son[i] = nullptr;
  }
  
  ~TrieNode() {
    for (int i = 0; i < 256; ++ i) 
      if (son[i] != nullptr) {
        delete son[i];
        son[i] = nullptr;
      }
  }
};
 
struct bufferEncode {
  std :: deque <bool> buf;
  
  bufferEncode() {
    while(! buf.empty()) buf.pop_back();
  }
  
  void incode(int id, uchar ch) {
    int highbit = 0;
    for (int i = MAX_BIT - 1; ~i; --i) 
      if ((id >> i) & 1) {
        highbit = i;
        break;
      }
    for (int i = 3; ~i; --i) buf.push_back((highbit >> i) & 1);
    for (int i = highbit; ~i; --i) buf.push_back((id >> i) & 1);
    for (int i = 7; ~i; --i) buf.push_back((ch >> i) & 1);
  }
  
  void raw(uchar ch) {
    for (int i = 7; ~i; -- i) buf.push_back((ch >> i) & 1);
  }
};
 
struct bufferDecode {
  int cursor;
  const std :: array <char, MAXSIZE> &array;
  int array_size;
  std :: deque <bool> buf;
  
  bufferDecode(const std :: array<char, MAXSIZE> &_array, int _size) : array(_array), array_size(_size) {
    cursor = 0;
    while(!buf.empty()) buf.pop_back();
  }
  
  void getNext() {
    if(reachEnd()) return ;
    uchar dat = array[cursor ++];
    for (int i = 7 - IS_DIV; ~i; -- i) buf.push_back((dat >> i) & 1);
  }
  
  uchar getUchar() {
    while (buf.size() < 8) getNext(); 
    uchar ret = 0;
    for (int i = 0; i < 8; ++ i) {
      ret = (ret << 1) + *buf.begin();
      buf.pop_front();
    }
    return ret;
  }
  
  int getInt(int digits) {
    while (buf.size() < digits) getNext();
    int ret = 0;
    for (int i = 0; i < digits; ++ i) {
      ret = (ret << 1) + *buf.begin();
      buf.pop_front();
    }
    return ret;
  }
  
  void decode(int &id, uchar &ch) {
    int highbit = getInt(4);
    id = getInt(highbit + 1);
    ch = getUchar();
  }
  
  bool reachEnd() const {
    return cursor >= array_size;
  }
  
  void debugPrt() {
    for (std :: deque <bool> :: iterator it = buf.begin(); it != buf.end(); ++ it)
      printf("%d", *it);
    puts("");
  }
};
 
TrieNode *rt = new TrieNode(0);
void PPCA :: rawData :: compress() {
  bufferEncode file;
  int cursor = 0, idpool = 1;
  
  while (cursor < __elem_array_size) {
    TrieNode *p = rt;
    uchar ch = __elem_array[cursor];
    if (p -> son[ch] == nullptr) {
      p -> son[ch] = new TrieNode(idpool ++, p, ch);
//      printf("(0, %c)\n", ch);
      file.incode(0, ch);
      ++ cursor;
      continue;
    }
    bool isend = 0;
    while(p -> son[ch] != nullptr) {
      p = p -> son[ch];
      cursor ++;  
      if(cursor == __elem_array_size) {
        isend = 1;
        break;
      }
      ch = __elem_array[cursor];
    }
    if(isend == 1) {
//      printf("(%d, empty)\n", p -> id); 
      file.incode(p -> id, 255);
    }
    else {
      p -> son[ch] = new TrieNode(idpool ++, p, ch);
//      printf("(%d, %c)\n", p -> id, ch);
      file.incode(p -> id, ch); 
      ++ cursor;
    }
  }
  
  __elem_array_size = 0;
  while(file.buf.size() >= 8 - IS_DIV) {
    uchar x = 0;
    for (int i = 0; i < 8 - IS_DIV; ++ i) {
      bool p = *file.buf.begin();
      file.buf.pop_front();
      x = (x << 1) + p;
    }
    __elem_array[__elem_array_size ++] = x;
  }
  if (file.buf.size() != 0) {
    uchar x = 0;
    int res = file.buf.size();
    for (int i = 0; i < res; ++ i) {
      bool p = *file.buf.begin();
      file.buf.pop_front();
      x = (x << 1) + p;
    }
    for (int i = res; i < 8 - IS_DIV; ++ i) x = (x << 1);
    __elem_array[__elem_array_size ++] = x;
  }
  delete rt;
}
 
TrieNode *nodepool[NODE_MAXSIZE];
void PPCA :: rawData :: decompress() {
  nodepool[0] = new TrieNode(0);
  
  int idpool = 1;
  std :: vector <uchar> vec;  
  bufferDecode in(getElemArray(), getSize());
  bufferEncode out;
  
  while(!in.reachEnd()) {
    int id; uchar ch;
    in.decode(id, ch);  
    
    if(ch != 255) {
      nodepool[idpool] = new TrieNode(idpool, nodepool[id], ch);
      nodepool[id] -> son[ch] = nodepool[idpool];
      
      vec.clear();
      TrieNode *p = nodepool[idpool];
      while(p -> id != 0) {
        vec.push_back(p -> ch);
        p = p -> par;
      }
      for (int i = vec.size() - 1; ~i; -- i) 
        out.raw(vec[i]);
      ++ idpool;
    } else {
      vec.clear();
      TrieNode *p = nodepool[id];
      while(p -> id != 0) {
        vec.push_back(p -> ch);
        p = p -> par;
      }
      for (int i = vec.size() - 1; ~i; -- i) 
        out.raw(vec[i]);
      break;
    }
  }
  
  __elem_array_size = 0;
  while(out.buf.size() >= 8) {
    uchar x = 0;
    for (int i = 0; i < 8; ++ i) {
      bool p = *out.buf.begin();
      out.buf.pop_front();
      x = (x << 1) + p;
    }
    __elem_array[__elem_array_size ++] = x;
  }
  delete nodepool[0];
}
