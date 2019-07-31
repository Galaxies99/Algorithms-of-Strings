// 704 / 1600 (could be wrong because of eof) 
# include "core.h"
# include <map>
# include <queue>
# include <iostream>
 
std :: map <char, int> mp;
std :: map <char, std :: string > code;
std :: priority_queue < std :: pair <int, int>, std :: vector< std :: pair <int, int> >, std :: greater < std :: pair <int, int> > > rec;
std :: vector < std :: pair<int, int> > edge[512 + 10];
std :: vector <char> zip, unzip;
int rt;

int abs(int x) {
  return x > 0 ? x : -x;
}
 
int fix(int x) {
  if(x < 0) x = 256 - abs(x);
  return x;
}
 
void getcode(int x, std :: string cur) {
  if(x < 256) {
    code[x] = cur;
    return ;
  }
  for (int i = 0; i < edge[x].size(); ++i) {
    if(edge[x][i].second == 0) 
      getcode(edge[x][i].first, cur + "0");
    
    if(edge[x][i].second == 1) 
      getcode(edge[x][i].first, cur + "1");
  }
}
 
void getHoffman(bool p) {
  while(!rec.empty()) rec.pop();
  for (std :: map <char, int> :: iterator it = mp.begin(); it != mp.end(); ++it)
    rec.push( std :: make_pair(it -> second, fix(it -> first)) );    
  if(rec.size() == 1) {
    rt = rec.top().second;
    code[rec.top().second] = "1";
  } else {
    int id = 257;
    while(rec.size() != 1) {
      std :: pair <int, int> top1 = rec.top();
      rec.pop();
      std :: pair <int, int> top2 = rec.top();
      rec.pop();
      
      edge[id].push_back( std :: make_pair(top1.second, 0) );
      edge[id].push_back( std :: make_pair(top2.second, 1) );
      
      rec.push( std :: make_pair(top1.first + top2.first, id) );
      ++ id;
    }   
    rt = rec.top().second;
    if(p) getcode(rec.top().second, "");
  } 
} 
 
void PPCA::rawData::compress() {
  mp.clear();
  code.clear();
  zip.clear();
  for (int i = 0; i < 512 + 10; ++i) edge[i].clear();
  
  for (int i=0; i<PPCA::rawData::__elem_array_size; ++i)
    mp[PPCA::rawData::__elem_array[i]] ++;
  
  getHoffman(1);
//  std::cout << rt << std::endl;
  
  zip.push_back(mp.size());
  int ok = 1;
  for (std::map<char, int>::iterator it = mp.begin(); it != mp.end(); ++it) {
    int t = it -> second;
    if(ok < 2 && t >= 256) ok = 2;
    if(ok < 3 && t >= 256 * 256) ok = 3;
    if(ok < 4 && t >= 256 * 256 * 256) ok = 4;
  }
  zip.push_back(ok);
  for (std::map<char, int>::iterator it = mp.begin(); it != mp.end(); ++it) {
    zip.push_back(it -> first);
    int t = it -> second;
    for (int i=1; i<=ok; ++i) {
      zip.push_back(t & 255);
      t >>= 8;
    }
  }
  
  int length = 0;
  int dec[12040], decn = 0;
  for (int i = 0; i < PPCA::rawData::__elem_array_size; ++i) {
    char c = PPCA::rawData::__elem_array[i];
    std :: string t = code[c];
    for (int j = 0; j < t.length(); ++j)
      dec[decn ++] = t[j] - '0';
    
    length += t.length();
      
    while(decn >= 8) {
      int c = 0;
      for (int j = 0; j < 8; ++ j)
        c = (c << 1) + dec[j];
      zip.push_back(c);
      decn -= 8;
      for (int j = 0; j < decn; ++j)
        dec[j] = dec[j + 8];
    }
  }
  
  if(decn) {
    int c = 0;
    for (int j = 0; j < 8; ++ j) 
      if(j < decn) c = (c << 1) + dec[j];
      else c = (c << 1);
    zip.push_back(c);
  }
  
  for (int i = 2; ~i; --i) {
    PPCA::rawData::__elem_array[i] = length & 255;
    length >>= 8;
  }
  
  PPCA::rawData::__elem_array_size = zip.size() + 3;
  for (int i = 3; i < PPCA::rawData::__elem_array_size; ++i)
    PPCA::rawData::__elem_array[i] = zip[i - 3];
}
 
void PPCA::rawData::decompress() {
  mp.clear();
  code.clear();
  unzip.clear();
  
  int length = 0;
  for (int i = 0; i <= 2; ++i) 
    length = length * 256 + fix(PPCA::rawData::__elem_array[i]);
  int count = PPCA::rawData::__elem_array[3];
  int ok = fix(PPCA::rawData::__elem_array[4]);
  count = fix(count);
  int j = 5;
  for (int i = 0; i < count; i ++) {
    char c = PPCA::rawData::__elem_array[j ++];
    int t[5];
    for (int k=1; k<=ok; ++k)
      t[k] = fix(PPCA::rawData::__elem_array[j ++]);
    int cc=0;
    for (int k=ok; k>=1; --k) cc = cc * 256 + t[k];
    mp[c] = cc; 
  }
  
  getHoffman(0);
  
  
  int cur = rt; bool end = 0;
  for (int i = j; i < PPCA::rawData::__elem_array_size; ++i) {
    int c = fix(PPCA::rawData::__elem_array[i]);
    for (int j = 7; ~j; --j) {
      if(cur <= 255) {
        unzip.push_back(cur);
        cur = rt;
      }
      if(c & (1 << j)) cur = edge[cur][1].first;
      else cur = edge[cur][0].first;
      -- length;
      if(length == 0) {
        end = 1;
        break;
      }
    }
    if(end) break;
  }
  if(cur <= 255) unzip.push_back(cur);
  PPCA::rawData::__elem_array_size = unzip.size();
  for (int i = 0; i < PPCA::rawData::__elem_array_size; ++i)
    PPCA::rawData::__elem_array[i] = unzip[i];
}
