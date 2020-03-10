//  DNS_FORWADER 2020
#ifndef DNS_FORWARDER_CPP_INCLUDE_UTIL_BUFFER_H_
#define DNS_FORWARDER_CPP_INCLUDE_UTIL_BUFFER_H_
#include <array>

namespace util_ns {
 static const int kMsgMaxSize = 1024;  // ToDo  (Daya)
                                       // Dimention this for queries with multiple     questions
                                       // number of questions is a 16 bits field
                                       // Each answere could contain multiple host adresses
 struct Buffer {
  std::array<unsigned char, kMsgMaxSize> buffer_;
  int buff_len_{0};
  void BuffeLen(int len) {
    buff_len_ = len;
  }
 };
}  //  namespace util_ns
#endif  //  DNS_FORWARDER_CPP_INCLUDE_UTIL_BUFFER_H_
