#include <algorithm>
#include <cctype>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
//#include <map>
//#include<set>

using namespace std;

char toLowerCaseC(char c)
{
	if (c >= 'A' && c <= 'Z')
		return c + ('a' - 'A');
	else
		return c;
}

string toLowerCase(string str)
{
	for (unsigned i = 0; i < str.size(); ++i)
		str[i] = toLowerCaseC(str[i]);
	return str;
}

class Dictionary
{
public:
	Dictionary(istream &input);
	bool contains(string word) const;
	unsigned size() const { return words.size(); }

private:
	vector<string> words;
};

Dictionary::Dictionary(istream &input)
{
	string word;
	getline(input, word);
	while (input)
	{
		words.push_back(toLowerCase(word));
		getline(input, word);
	}
	sort(words.begin(), words.end());
}

bool Dictionary::contains(string word) const
{
	word = toLowerCase(word);
  if (word == "")
     return true;
	for (unsigned i = 0; i < words.size(); ++i)
	{
		if (word == words[i])
			return true;
		else if (word < words[i])
			return false;
	}
	return false;
}

vector<string> checkSpellingOf(const vector<string> &words, const Dictionary &inDictionary)
{
	vector<string> misspelled;
	for (unsigned wordCount = 0; wordCount < words.size(); ++wordCount)
	{
	    string word = words[wordCount];
		if (!inDictionary.contains(word))
			misspelled.push_back(word);
	}
	return misspelled;
}

string stripPunctuation(string str)
{
	unsigned k = 0;
	while (k < str.size() && isalnum(str[k]))
		++k;
	return str.substr(0, k);
}

/**
 * Checks the spelling of a set of words supplied as
 * command-line parameters. If no command-line parameters
 * are supplied, prompts for a line of input containing
 * one or more words.
 */
int main(int argc, char **argv)
{
	cerr << "Loading..." << endl;
	ifstream dictInput("dictionary.txt");
	Dictionary dictionary(dictInput);
	cerr << "Loaded " << dictionary.size() << " words into dictionary." << endl;

	vector<string> words;

	cout << "Enter the text you would like to spellcheck:\n"
		 << flush;
	cout << "Use the end-of-input character (Ctrl-z in Windows, Ctrl-d\n";
	cout << "in Linux or MacOS) when done." << endl;
	string word;
	while (cin >> word)
	{
		word = stripPunctuation(word);
		words.push_back(word);
	}

	auto misspelled = checkSpellingOf(words, dictionary);
	cout << "Found " << misspelled.size() << " misspelled words:\n";
	for (auto misspelling: misspelled)
	{
		string word = misspelling;
		int wordNumber = -1;
		cout << word << " is misspelled at word number " 
		    << wordNumber << "\n";
	}
	cout << flush;
	return 0;
}