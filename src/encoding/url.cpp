//  :copyright: (c) 2003 Davis E. King (davis@dlib.net)
//  :license: Boost, see licenses/Boost.txt for more details.
/**
 *  \addtogroup Lattice
 *  \brief URL encode/decode data.
 */

#include "lattice/encoding/url.hpp"


namespace lattice
{
// FUNCTIONS
// ---------


/** Convert character to hex.
 */
unsigned char toHex(unsigned char x)
{
    return x + (x > 9 ? ('A'-10) : '0');
}

/** Convert all ASCII character ranges back to bytes.
 */
unsigned char fromHex(unsigned char x)
{
    if (x <= '9' && x >= '0')
        x -= '0';
    else if (x <= 'f' && x >= 'a')
        x -= 'a' - 10;
    else if (x <= 'F' && x >= 'A')
        x -= 'A' - 10;
    else
        x = 0;
    return x;
}


/** Pre-allocate upper bound of the encoded-string, that is, ~3x the
 *  size of the original string, and re-allocate string once.
 */
std::string urlencode(const std::string &string)
{
    std::string result;
    result.reserve(3 * string.size());

    for (auto it = string.cbegin(); it != string.cend(); ++it)
    {
        if ((*it >= 'a' && *it <= 'z')||
            (*it >= 'A' && *it <= 'Z')||
            (*it >= '0' && *it <= '9'))
        {
            result += *it;
        } else if (*it == ' ') {
            result += '+';
        } else {
            result += '%';
            result += toHex(*it >> 4);
            result += toHex(*it % 16);
        }
    }

    result.shrink_to_fit();
    return result;
}


/** Pre-allocate upper bound of the encoded-string, that is, roughly the
 *  size of the original string, and re-allocate string once.
 */
std::string urldecode(const std::string &string)
{
    std::string result;
    result.reserve(string.size());

    std::string::size_type i;
    for (i = 0; i < string.size(); ++i)
    {
        if (string[i] == '+') {
            result += ' ';
        } else if (string[i] == '%' && string.size() > i+2) {
            const unsigned char ch1 = fromHex(string[i+1]);
            const unsigned char ch2 = fromHex(string[i+2]);
            const unsigned char ch = (ch1 << 4) | ch2;
            result += ch;
            i += 2;
        } else {
            result += string[i];
        }
    }

    result.shrink_to_fit();
    return result;
}

}   /* lattice */
