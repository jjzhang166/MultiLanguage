#ifndef __UTIL_H__
#define __UTIL_H__

#include <string>
using std::string;

namespace Util {

string string_strip(const string &origin);
string convert_special_chars(const string &origin);

}
#endif //__UTIL_H__
