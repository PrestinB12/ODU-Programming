#ifndef PALINDROME_H
#define PALINDROME_H

#include <string>

/**
* Tests to see if a phrase is a palindrome. Ignores upper/lower case
* differences and non-alphabetic characters.
*/
bool isAPalindrome (std::string phrase);

/**
 * Strip away all non-aphabetic chracters and convert all
 * upper-case characters to lower-case.
 */
std::string preprocess (std::string phrase);

#endif