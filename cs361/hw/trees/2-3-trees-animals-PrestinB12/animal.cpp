//
//	animal game -- test of binary trees 
//
//	Described in Chapter 13 of
//	Data Structures in C++ using the STL
//	Published by Addison-Wesley, 1997
//	Written by Tim Budd, budd@cs.orst.edu
//	Oregon State University
//
//      Modified by S Zeil, Old Dominion University, adding code
//      to read & write the question trees from a file.
//

#include <cassert>
#include <fstream>
#include <string>

#include "node.h"


using namespace std;

bool getYesNoAnswer() 
{
  // get yes no answer
  while (true)
    {
      string ans;
      getline(cin, ans);
      if ((ans[0] == 'y') || (ans[0] == 'Y'))
	return true;
      else if ((ans[0] == 'n') || (ans[0] == 'N'))
	return false;
      cout << "please answer yes or no.\n";
    }
}

void learnNewAnimal(node* current)
{
  // learn about a new animal type

  string currentAnimal = current->detailText;
  cout << "what is your animal?\n";
  string newAnimal;
  getline(cin, newAnimal);
  cout << "What is a yes/no question that I can use to tell a "
       << current->detailText << " from a " << newAnimal << " ?\n";
  string newQuestion;

  node * node1 = new node(newAnimal, 0, 0);
  node * node2 = new node(currentAnimal, 0, 0);
  // make sure allocation worked
  assert ((node1 != 0) && (node2 != 0));

  getline(cin, newQuestion);
  cout << "For a " << newAnimal << " is the answer yes or no?\n";
  if (getYesNoAnswer() != 0) 
    {
      current->ifYes = node1;
      current->ifNo = node2;
    }
  else
    {
      current->ifYes = node2;
      current->ifNo = node1;
    }
  current->detailText = newQuestion;
}



void animalGame(const char* fileName) 
{
  // initialize the database
  node* root = 0;
  {
    ifstream in (fileName);
    if (in.good())
      in >> root;
  }


  if (root == 0) // file was empty or nonexistent
    root = new node ("cat", 0, 0);


  // play the game
  node * current = root;
  // now start the game
  cout << "Let's play \"Guess the Animal\".\n";
  while (current != 0) 
    {
      // if current node has children it is a question
      if (current->ifYes != 0) 
	{
	  cout << current->detailText << '\n';
	  if (getYesNoAnswer())
	    current = current->ifYes;
	  else
	    current = current->ifNo;
	}
      // if no children it is an answer
      else 
	{
	  cout << "I know.  Is it a " << current->detailText << " ?\n";
	  if (getYesNoAnswer()) 
	    cout << "I won.\n";
	  else 
	    {
	      // we didn't get it.
	      // time to learn something
	      learnNewAnimal(current);
	    }
	  cout << "Try again?\n";
	  if (getYesNoAnswer())
	    current = root;
	  else 
	    current = 0;
	}
    }

  // Save the modified question set
  ofstream out (fileName);
  out << root << flush;
}

int main (int nargs, char** argv)
{
  if (nargs != 2)
    {
      cerr << "Usage: animal filename\n"
	   << "  where the filename denotes a file used both\n"
	   << "  to read an existing database of questions (may\n"
	   << "  be empty or even nonexistent, in which case a\n"
	   << "  default initialzation is used instead) and to\n"
	   << "  receive the modified database of questions\n"
	   << "afterwards." << endl;
      return -1;
    }

  animalGame(argv[1]);
  return 0;
  
}
