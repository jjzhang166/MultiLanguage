#include <assert.h>
#include <iostream>
#include "Util.h"

using namespace std;

namespace Util {

namespace {
    char _09AF_to_value(char ch)
    {
        if ('0' <= ch && ch <= '9') {
            return ch - '0';
        } else if ('A' <= ch && ch <= 'F') {
            return ch - 'A';
        } else if ('a' <= ch && ch <= 'f') {
            return ch - 'a' + 10;
        } else {
            throw string("Invalid char \"") + ch + "\".";
        }
    }

    char _hex2char(const string &origin)
    {
        if (origin.length() < 2) {
            throw string("Two chars required");
        }

        char ch_hi = _09AF_to_value(origin[0]);
        char ch_lo = _09AF_to_value(origin[1]);

        return ch_hi << 4 | ch_lo;
    }
}

string string_strip(const string &origin)
{
    string::size_type start_pos = origin.find_first_not_of(' ');
    string::size_type end_pos = origin.find_last_not_of(' ');
    //!FIXME: Should deal with '\t' as well.
    if (start_pos == string::npos) {
        return string();
    } else {
        return origin.substr(start_pos, end_pos-start_pos+1);
    }
}

string convert_special_chars(const string &origin)
{
    string ret;
    string::size_type last_pos = 0;
    string::size_type this_pos = origin.find('\\', last_pos);
    while (this_pos != string::npos) {
        if ((this_pos == 0 || origin[this_pos-1] != '\\') \
            && (this_pos <= origin.length()-2
                && (origin[this_pos+1] == 'x' || origin[this_pos+1] == 'X'))) {

            ret += origin.substr(last_pos, this_pos-last_pos);
            string strValue = origin.substr(this_pos+2, 2);

            try {
                char c = _hex2char(strValue);   //!TODO:
                ret += c;
            } catch (string msg) {
                cerr << "WARN: " << msg << endl;
                ret += "??";
            }

            last_pos = this_pos + 4;
            this_pos = origin.find('\\', last_pos);

        } else {
            this_pos = origin.find('\\', this_pos+2);
        }
    }

    if (last_pos <= origin.length()-1) {
        ret += origin.substr(last_pos);
    }
    return ret;
}

}
