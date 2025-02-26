#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
#include <set>

#include "dictionary.h"

using namespace std;

char Dictionary::toLowerCaseC(char c)
{
	if (c >= 'A' && c <= 'Z')
		return c + ('a' - 'A');
	else
		return c;
}

string Dictionary::toLowerCase(string str)
{
	for (unsigned i = 0; i < str.size(); ++i)
		str[i] = toLowerCaseC(str[i]);
	return str;
}


Dictionary::Dictionary(istream &input)
{
	string word;
	getline(input, word);
	while (input)
	{
		words.insert(Spool(toLowerCase(word)));
		getline(input, word);
	}
}

bool Dictionary::contains(string word) const
{
  word = toLowerCase(word);
  if (word == "")
     return true;
  else 
     return words.count(Spool(word)) > 0;
}
