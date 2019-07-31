// 453 / 1600 LZ77 with division (use special code to prevent)
# include "core.h"
# include <vector>
# include <queue>
# include <deque> 
 
typedef unsigned char uchar;
 
const int BIT_MASK = 4;
const bool IS_DIV = 0;
 
struct slidingWindows {
  static const int WindowsSize = (1 << BIT_MASK) - 1;
  int bg, ed;
  std :: deque <uchar> data;
  
  slidingWindows(int _ed = 0) : bg(_ed), ed(_ed) { 
    while(!data.empty()) data.pop_back();
  }
  
  void slide() {
    while(ed - bg > WindowsSize) {
      data.pop_front();
      ++ bg;
    }
  }
  
  int length() const {
    return ed - bg;
  }
  
  void debugPrt() const {
    for (std :: deque <uchar> :: const_iterator it = data.cbegin(); it != data.cend(); ++ it)
      printf("%c", *it);
    puts("");
  }
};
 
struct bufferEncode {
  std :: deque <bool> buf;
  
  bufferEncode() {
    while(! buf.empty()) buf.pop_back();
  }
  
  void incode(int offset, int length, uchar ch = 0) {
    if(offset == -1 && length == -1) {
      buf.push_back(0);
      for (int i = 7; ~i; -- i) buf.push_back((ch >> i) & 1);
      buf.push_back(0);
      return ;
    } else {
      -- offset; -- length;
      buf.push_back(1);
      for (int i = BIT_MASK - 1; ~i; -- i) buf.push_back((offset >> i) & 1);
      for (int i = BIT_MASK - 1; ~i; -- i) buf.push_back((length >> i) & 1);
      buf.push_back(0);
    }
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
  
  void decode(int &offset, int &length, uchar &ch) {
    if(getInt(1) == 0) {
      offset = length = -1;
      ch = getUchar();
      getInt(1);
    } else {
      offset = getInt(BIT_MASK) + 1;
      length = getInt(BIT_MASK) + 1;
      getInt(1);
    }
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
 
 
bool checkCorrect(const std :: vector <uchar> &buf, const slidingWindows &w, int &offset, int &length) {
  if(buf.size() > w.length()) return false;
  for (std :: deque <uchar> :: const_iterator it = w.data.cbegin(); it != w.data.cend(); ++ it) {
    std :: deque <uchar> :: const_iterator it2 = it;
    int i;
    for (i = 0; i < buf.size() && it2 != w.data.cend(); ++ i, ++ it2) 
      if (buf[i] != *it2) break;
    if (i == buf.size()) {
      offset = w.data.cend() - it;
      length = buf.size();
      return true;
    }
    if (it2 == w.data.cend()) return false;
  }
  return false;
}
 
void PPCA :: rawData :: compress() {
  slidingWindows w;
  std :: vector <uchar> buffer;
  bufferEncode file;
  
  while(w.ed < __elem_array_size) {
    int offset = -1, length = -1, cursor = w.ed;
    buffer.clear();
    while(buffer.size() <= slidingWindows :: WindowsSize && cursor < __elem_array_size) {
      buffer.push_back((uchar)__elem_array[cursor]);
      if(checkCorrect(buffer, w, offset, length)) cursor ++;
      else {
        if(offset == -1 && length == -1) {
          file.incode(-1, -1, (uchar)__elem_array[cursor]);
//        printf("(0, 0, %c)\n", __elem_array[cursor]);
          cursor ++;
        } else {
          file.incode(offset, length);
//        printf("(%d, %d)\n", offset, length);
        }
        break;
      }
      if(cursor == __elem_array_size) {
//      printf("(%d, %d)\n", offset, length);
        file.incode(offset, length);
      }
    }
//  std :: cout << w.ed << ' ' << cursor << std :: endl;
    for (int i = w.ed; i < cursor; ++ i) w.data.push_back((uchar)__elem_array[i]);
    w.ed = cursor;
    w.slide(); 
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
}
 
void PPCA :: rawData :: decompress() {
  slidingWindows w;
  bufferDecode in(getElemArray(), getSize());
  bufferEncode out;
  uchar temp[4100];
   
  while(!in.reachEnd()) {
    int offset, length; uchar ch;
    in.decode(offset, length, ch);
    if(offset == -1 && length == -1) {
      w.data.push_back(ch);
      out.raw(ch);
      ++ w.ed;
      w.slide();
    } else {
      int tempn = 0;
      for (std :: deque <uchar> :: iterator it = w.data.end() - offset; it < w.data.end() - offset + length; ++ it) {
        temp[tempn] = *it;
        out.raw(temp[tempn]);
        ++ tempn;
      }
      for (int i = 0; i < length; ++ i) w.data.push_back(temp[i]);
      w.ed += length;
      w.slide();
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
}
