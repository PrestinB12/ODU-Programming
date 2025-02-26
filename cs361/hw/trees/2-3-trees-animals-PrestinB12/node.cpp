#include "node.h"
#include <cassert>

/*
Input/Output format for this program.

A tree of questions and answers is represented by multiple lines of
text. There will always be at least one line of text.

Each line represents one node in the tree. Each begins with either a
'Q' or an 'A', indicating whether the node is a Question node or an
Answer node, followed by one or more blank spaces, followed by the
text of the question or answer. The text of a question or answer
begins with the first non-blank character after the Q or A and
continues until the end of the line.

Each 'Q' line is followed immediately by two blocks of 'Q' and 'A'
lines. The first block describes the collection of questions and
answers relevant following a "yes" answer to the first question. The
second block describes the collection of questions and answers
relevant to a "no" answer to the opening question.

For example,

Q Does it live in the water?
Q   Does it have webbed feet?
A     Duck
A     Fish
A   Cat


Describes a tree in which the first question to be asked is "Does it
live in the water?". If the person playing the game answers "yes",
then the block of lines

Q   Does it have webbed feet?
A     Duck
A     Fish

is relevant (i.e., the program will next ask about webbed feet). If
the person answers "no". then the block of lines

A   Cat

is relevant (i.e., the program will next ask "Is it a cat?".

The "indentation" shown in the sample above is purely for human
readability.  It is not required in your output, though your input
routine should tolerate it if it is present.

 */



using namespace std;

// write the tree whose root is given.
// Note: the form written out by this function should be something
//   that read(...) will accept, recreating the original tree.
void node::write (std::ostream& out, const node* root)
{
    if (root->ifYes != nullptr && root->ifNo != nullptr)
  {
    out << "Q " << root->detailText << std::endl;
    write(out, root->ifYes);  //recursion for the following question(s)
    write(out, root->ifNo);
  }
  else
  {
    out << "A " << root->detailText << std::endl;
  }
}

void node::read(std::istream& in, node*& t) 
{
    std::string line;
    std::getline(in, line);

    // Removes the leading/trailing whitespaces and the first two characters
    size_t start = line.find_first_not_of(" \t", 2); // Start from the third character
    size_t end = line.find_last_not_of(" \t");

    if (start != std::string::npos && end != std::string::npos) 
    {
        // Extract the non-whitespace characters from the line
        t = new node(line.substr(start, end - start + 1));
        if (line[0] == 'Q') 
        {
            read(in, t->ifYes);
            read(in, t->ifNo);
        }
    } 
    else 
    {
        t = nullptr;
    }
}

/*
// read a tree from in storing the tree root in t
void node::read (istream& in, node*& t)
{
  std::string line;
  std::getline(in, line); //reads the input(s)

  if (line.empty()) //If empty
  {
    t = nullptr;
    return;
  }

  // Write your function remove the whitespace
    for(beginSpace != std::string::npos)
    {
        const auto endSpace = result.find_first_not_of(whitespace, beginSpace);
        const auto range = endSpace - beginSpace;

        result.replace(beginSpace, range, fill);

        const auto newStart = beginSpace + fill.length();
        beginSpace = result.find_first_of(whitespace, newStart);
    }


  // If you removing the whitspace returns an index replace i here, if it returns a string replace line.substr() with the string variable
  t = new node(line.substr(i)); //Removes whitespace, returns the index of "i" if it has a string

  if (line[0] == 'Q') //If question
  {
    read(in, t->ifYes);
    read(in, t->ifNo);
  }
}
*/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
bool std::operator>>(std::istream&, node*&)
{
  //stuff
}
bool std::operator<<(std::ostream&, const node*&)
{
  //stuff
}
inline std::ostream& operator<<(std::ostream& out, const node* n)
{
  //stuff
}
inline std::istream& operator>>(std::istream&in, node*& n)
{
  //stuff
}
*/

