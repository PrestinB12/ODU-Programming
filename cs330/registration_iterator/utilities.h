#ifndef UTILITIES_H_DEFINED
#define UTILITIES_H_DEFINED

#include <string>
#include <utility>

/**
 * Trim leading and trailing whitespace from a string.
 *
 * @param str string to prune
 *
 * @pre str is nonempty
 */
inline
void trim(std::string& str)
{
    if (str.empty()) {
        return;
    }

    int first_nonspace = str.find_first_not_of(" \t");
    int last_non_space = str.find_last_not_of(" \t");

    str = str.substr(first_nonspace, last_non_space + 1);
}

#endif
