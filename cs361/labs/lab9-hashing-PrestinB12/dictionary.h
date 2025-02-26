#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <iostream>
#include <string>
#include <unordered_set>

#include "spool.h"

class Dictionary
{
public:
	Dictionary(std::istream &input);
	bool contains(std::string word) const;
	unsigned size() const { return words.size(); }

private:
	std::unordered_set<Spool> words;

    static char toLowerCaseC(char c);

    static std::string toLowerCase(std::string str);

};

#endif
