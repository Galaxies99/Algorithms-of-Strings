// 596 / 1600 Huffman right

# include "core.h"
# include <cstring>
# include <vector>
# include <queue>
# include <deque> 
# include <map>
 
typedef unsigned char uchar;
  
const bool IS_DIV = 1;
constexpr int NODE_MAXSIZE = 1024 * 512 + 8;
 
struct bufferEncode {
  std :: deque <bool> buf;
  
  bufferEncode() {
    while(! buf.empty()) buf.pop_back();
  }
  
  void incode() {
    
  }
  
  void raw(uchar ch) {
    for (int i = 7; ~i; -- i) buf.push_back((ch >> i) & 1);
  }
  
  void rawint_with_digits(int x) {
    int d; 
    if(x < 256) d = 1;
    else d = 2;
    if(d == 1) buf.push_back(0);
    if(d == 2) buf.push_back(1);
    for (int i = d * 8 - 1; ~i; -- i)
      buf.push_back((x >> i) & 1);
  }
  
  void rawstring(std :: string &cur) {
    for (int i = 0; i < cur.size(); ++ i) 
      buf.push_back(cur[i] == '1');
  }
  
  void rawint_prev(int x, int d) {
    for (int i = 0; i < d; ++ i) buf.push_front((x >> i) & 1);
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
  
  void decode() {
    
  }
  
  int getint_with_digits() {
    int type = getInt(1) + 1;
    return getInt(type * 8);
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

int times[256];

std :: priority_queue < 
                        std :: pair <int, int>, 
                        std :: vector < std :: pair <int, int> >, 
                        std :: greater < std :: pair <int, int> > 
                      > que;
std :: map <uchar, std :: string> mp;

std :: vector <int> G[512];

void getCode(int x, std :: string code = "") {
  if(G[x].size() == 0) {
    mp[(uchar)x] = code;
    return ;
  }
  getCode(G[x][0], code + "0");
  getCode(G[x][1], code + "1");
}

int getHuffman(const int *times, bool type) {
  mp.clear(); 
  for (int i = 0; i < 512; ++ i) G[i].clear();
  while(!que.empty()) que.pop();
  
  for (int i = 0; i < 256; ++ i)
    if(times[i] > 0) que.push(std :: make_pair(times[i], i));
  
  int rt = 256;
  if(que.size() == 1) {
    rt = que.top().second; 
  } else {
    while(que.size() > 1) {
      std :: pair <int, int> top1 = que.top(); que.pop();
      std :: pair <int, int> top2 = que.top(); que.pop();
      que.push(std :: make_pair(top1.first + top2.first, rt)); 
      G[rt].push_back(top1.second);
      G[rt].push_back(top2.second);
      ++ rt;
    }
    -- rt;
  }
  
  if(type == 0) getCode(rt);
  return rt;
}

void PPCA :: rawData :: compress() {
  bufferEncode file;
  memset(times, 0, sizeof times);
  
  for (int i = 0; i < __elem_array_size; ++ i) 
    times[(uchar)__elem_array[i]] ++;
  
  getHuffman(times, 0);
  
  int count = 0;
  for (int i = 0; i < 256; ++ i)
    if(times[i] > 0) ++ count;
  file.rawint_with_digits(count - 1);
  
  for (int i = 0; i < 256; ++ i)
    if(times[i] > 0) {
      file.raw((uchar) i);
      file.rawint_with_digits(times[i]);
    }
  
  int len = 0;
  std :: string code;
  for (int i = 0; i < __elem_array_size; ++ i) {
    code = mp[(uchar)__elem_array[i]];
    file.rawstring(code);
    len += code.size();
  }
  
  file.rawint_prev(len, 20);
  
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
}
 
void PPCA :: rawData :: decompress() {
  bufferDecode in(getElemArray(), getSize());
  bufferEncode out;
  
  memset(times, 0, sizeof times);
  
  int len = in.getInt(20);
  int count = in.getint_with_digits() + 1;
  for (int i = 0; i < count; ++ i) {
    uchar ch = in.getUchar(); 
    times[ch] = in.getint_with_digits();
  }
  
  int rt = getHuffman(times, 1);
  int p = rt;
  
  while(len --) {
    if(p < 256) {
      out.raw((uchar) p);
      p = rt;
    }
    int t = in.getInt(1);
    if(t == 0) p = G[p][0];
    else p = G[p][1];
  }
  if(rt >= 256 && p < 256) out.raw((uchar) p);
  
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
}

