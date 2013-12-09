//
// chat_message.hpp
// ~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2013 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef CHAT_MESSAGE_HPP
#define CHAT_MESSAGE_HPP

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
using namespace std;
inline static std::string& left(std::string& str)   
{   
	std::string::size_type index = str.find_first_not_of(" \n\r\t");  
	if (index != std::string::npos){str = str.substr(index);}  
	return  str;  
}  

inline static std::string& right(std::string& str)   
{   
	std::string::size_type index = str.find_last_not_of(" \n\r\t");  
	if (index != std::string::npos){str = str.substr(0, index + 1);}  
	return str;  
}  

inline static std::string& trim(std::string& str)   
{   
	return left(right(str));   
}  
class chat_message
{
public:
  enum { header_length = 4 };
  enum { max_body_length = 512 };

  chat_message()
    : body_length_(0)
  {	  
	 memset(data_,'\0', header_length + max_body_length);
  }

  const char* data() const
  {
    return data_;
  }

  char* data()
  {
    return data_;
  }

  size_t length() const
  {
    return header_length + body_length_;
  }

  const char* body() const
  {
    return data_ + header_length;
  }

  char* body()
  {
    return data_ + header_length;
  }

  size_t body_length() const
  {
    return body_length_;
  }

  void body_length(size_t new_length)
  {
    body_length_ = new_length;
    if (body_length_ > max_body_length)
      body_length_ = max_body_length;
  }

  bool decode_header()
  {
    using namespace std; // For strncat and atoi.
    char header[header_length + 1] = "";
    strncat(header, data_, header_length);
    body_length_ = atoi(header);
    if (body_length_ > max_body_length)
    {
      body_length_ = 0;
      return false;
    }
    return true;
  }

  void encode_header()
  {
    using namespace std; // For sprintf and memcpy.
    char header[header_length + 1] = "";
    sprintf(header, "%4d", body_length_);
    memcpy(data_, header, header_length);
  }

private:
  char data_[header_length + max_body_length];
  size_t body_length_;
};
#endif // CHAT_MESSAGE_HPP
