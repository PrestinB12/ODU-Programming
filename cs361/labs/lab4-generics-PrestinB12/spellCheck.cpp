#include <algorithm>
#include <cctype>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iterator>

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
	transform(str.begin(), str.end(), str.begin(), toLowerCaseC);
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
  	transform(istream_iterator<string>(input), istream_iterator<string>(),
            back_inserter(words), toLowerCase);
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

vector<string> checkSpellingOf(const vector<string> &words, 
                               const Dictionary &inDictionary)
{
  vector<string> misspelled;
  copy_if(words.begin(), words.end(), back_inserter(misspelled),
          [&](const string &word) { return !inDictionary.contains(word); });
  return misspelled;
}

string stripPunctuation(string str)
{
	//string::iterator pos = ...;  
	//str.erase(pos, str.end()); 
	 auto pos = find_if_not(str.begin(), str.end(), 
                  [] (char c) {return isalnum(c);});
  	str.erase(pos, str.end());
  	return str;
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
  	transform(istream_iterator<string>(cin), istream_iterator<string>(), 
            back_inserter(words), stripPunctuation);

 	 vector<string> misspelled = checkSpellingOf(words, dictionary);
 	 cout << "Found " << misspelled.size() << " misspelled words:\n";
 	 copy(misspelled.begin(), misspelled.end(), ostream_iterator<string>(cout, "\n"));
  	cout << flush;
  	return 0;
}

