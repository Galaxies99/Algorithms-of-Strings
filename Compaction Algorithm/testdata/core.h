//
// Created by 郑文鑫 on 2019-07-20.
//

#ifndef COMPRESS_CORE_H
#define COMPRESS_CORE_H


// Set max required size as 32MB
constexpr int MAXSIZE = 1024 * 512 + 8;

#include <array>
#include <chrono>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
namespace PPCA {
template <class U, class V> struct __lib_check_same {
  constexpr operator bool() const { return false; }
};

template <class T> struct __lib_check_same<T, T> {
  constexpr operator bool() const { return true; }
};

void msg(const std::string &message) {
  std::cout << message;
  exit(0);
}

class rawData {
private:
  std::array<char, MAXSIZE> __elem_array;
  std::array<char, MAXSIZE> __empty;
  int __elem_array_size;

public:
  rawData() { __empty.fill(0); }
  rawData(const std::array<char, MAXSIZE> &rhs) =
      delete;
  void reload(const std::vector<char> &rhs){
    this->__elem_array_size = rhs.size();
    std::copy(rhs.cbegin(), rhs.cend(), __elem_array.begin());
  }
  rawData &operator=(const std::array<unsigned char, MAXSIZE> &rhs) = delete;
  // This function is intended to get the Bytes of [start, start + size) into
  // type T where T can only be unsigned char, char, short, int and long
  // Otherwise you will receive a compiling error
  template <class T> T getData(const int &start, const int &size) {
    static_assert(__lib_check_same<unsigned char, T>() ||
                  __lib_check_same<char, T>() ||
                  __lib_check_same<short, T>() ||
                  __lib_check_same<int, T>() || __lib_check_same<long, T>(),
                  "Function getData requires one of these types: unsigned "
                  "char, char, short, int, long");
    T tmp = 0;
    for (int i = start; i < size + start; ++i)
      tmp = (tmp << 8) | (__elem_array[i]);
    return tmp;
  }
  // Get the size of the data
  const int getSize() const { return __elem_array_size; }
  void clear() { __elem_array.swap(__empty); }
  const short operator[](int idx) const {
    if (idx > __elem_array_size)
      msg("Error: idx[" + std::to_string(idx) + "] out of the limit[" +
          std::to_string(__elem_array_size) + "]");
    return __elem_array[idx];
  }
  // Compress the target data
  void compress();
  // Decompress the target data
  void decompress();
  const std::array<char, MAXSIZE> &getElemArray() const{ return __elem_array; }
};

bool __lib_check_same_result(const rawData &src, const rawData &dest) {
  for (int i = 0; i < src.getSize(); ++i)
    if (src[i] != dest[i])
      return false;
  return true;
}

double __lib_cal_rate(const rawData &src, const rawData &dest) {
  return dest.getSize() <= 0 ? 0.0 : 100.0 * dest.getSize() / src.getSize();
}
class Timer {
private:
  std::chrono::high_resolution_clock::time_point last;

public:
  double accumulated;
  Timer() : accumulated(0) {}
  void start() { last = std::chrono::high_resolution_clock::now(); }
  double stop() {
    std::chrono::high_resolution_clock::time_point nw =
        std::chrono::high_resolution_clock::now();
    double secs =
        (std::chrono::duration_cast<std::chrono::duration<double>>(nw - last))
            .count();
    accumulated += secs;
    return secs;
  }
};
} // namespace PPCA

#endif // COMPRESS_CORE_H
PPCA::rawData src, dest;
std::vector<char> raw, stdData;
int main(int argc, char **argv) {
  int count = 0;
#ifdef VisualStudio
  std::cout << "Please input the count of test cases." << std::endl;
  std::cin >> count;
#endif
#ifndef VisualStudio
  if (argc != 2)
    PPCA::msg("Error: Require 2 arguments here.");
  count = std::stoi(std::string(argv[1]));
#endif
  for (int i = 1; i <= count; ++i) {
    raw.clear();
    std::string filename("t" + std::to_string(i) + ".bin");
    std::ifstream fin(filename, std::ios::binary);
    char c;
    int idx = 0;
    while ((c = fin.get()) != EOF) {
      raw.push_back(c);
      idx++;
    }
    fin.close();
    src.reload(raw);
    dest.reload(raw);
    PPCA::Timer timerCompress;
    double compressTime, decompressTime, compressRate;
    timerCompress.start();
    dest.compress();
    timerCompress.stop();
    if (timerCompress.accumulated > 1000) {
      std::cout << "Test #" << i << ": [Compress] [TLE] Your time "
                << std::fixed << timerCompress.accumulated << "s  v.s. Limit 2s" << std::endl;
      continue;
    }
    compressTime = timerCompress.accumulated;
    compressRate = PPCA::__lib_cal_rate(src, dest);
    PPCA::Timer timerDecompress;
    timerDecompress.start();
    dest.decompress();
    timerDecompress.stop();
    if (timerDecompress.accumulated > 2000) {
      std::cout << "Test #" << i << ": [Decompress] [TLE] Your time "
                << std::fixed << timerDecompress.accumulated << "s  v.s. Limit 2s"
                << std::endl;
      continue;
    }
    if (PPCA::__lib_check_same_result(src, dest)) {
      std::cout << "Test #" << i << std::fixed << ": Your compress Ratio " << compressRate
                << " Running Time:[Compress]" << std::fixed << timerCompress.accumulated
                << "s [Decompress]" << timerDecompress.accumulated << "s"
                << std::endl;
      continue;
    } else {
      std::cout << "Error on Test #" << i
                << ": Your decompression OR compression is wrong."  << std::fixed << ": Your compress Ratio " << compressRate
                                                                    << " Running Time:[Compress]" << std::fixed << timerCompress.accumulated
                                                                    << "s [Decompress]" << timerDecompress.accumulated << "s" << std::endl;
      // exit(0);
    }
  }
}
