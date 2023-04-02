#include "string.hpp"

#include <cstdint>
#include <cstring>

using std::string;

namespace bif {

String& String::operator=(const string& s)
{
  int64_t size = s.size();
  allocate(size);
  for (int i = 0; i < size; i++) { set(i, s[i]); }
  return *this;
}

String& String::operator=(const char* s)
{
  int size = strlen(s);
  allocate(size);
  for (int i = 0; i < size; i++) { set(i, s[i]); }
  return *this;
}

String::operator string() const
{
  string output;
  for (int i = 0; i < size(); i++) { output += *get(i); }
  return output;
}

string String::to_string() const { return *this; }

String String::debif(const Bifer::ptr& bifer, DataRange header)
{
  return bif::debif<Array<char>>(bifer, header);
}

} // namespace bif
