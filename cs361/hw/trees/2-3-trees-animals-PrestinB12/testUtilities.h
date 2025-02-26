#ifndef TEST_UTILITIES 
#include <string>
#include "node.h"


using namespace std;

/**
 * @brief Collapses repeated adjacent whitespace characters (blanks, tabs) into
 *        a single blank.
 * 
 * @param s a string
 * @return std::string  string with repeated adjacent whitespace collapsed
 */
std::string normalizeWhiteSpace (const std::string& s);

/**
 * @brief Does a deep comparison of two trees to see if they have the same
 *        shape and the same data in corresponding nodes.
 * 
 * @param a a tree
 * @param b another tree
 * @return true if the trees are isomorphic
 * @return false if the trees differ in shape or data
 */
bool isomorphic (const node* a, const node* b);

#endif