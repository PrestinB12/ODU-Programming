#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <string>


//
//	binary tree node for animal guessing game
//
//	Each node contains a question and and pointers
//      to the node representing yes and no responses, or
//      an animal name and two null pointers
//


struct node {
  std::string detailText;
  node* ifYes;
  node* ifNo;

  node (std::string q, node* yes = NULL, node* no = NULL)
    : detailText(q), ifYes(yes), ifNo(no)
    {}

  // read a tree from in storing the tree root in t
  static void read (std::istream& in, node*& t);
  
  // write the tree whose root is given.
  // Note: the form written out by this function should be something
  //   that read(...) will accept, recreating the original tree.
  static void write (std::ostream& out, const node* root);
  
    
private:

  friend std::istream& operator>> (std::istream&, node*&);
  friend std::ostream& operator<< (std::ostream&, const node*);

};

inline
std::ostream& operator<< (std::ostream& out, const node* n)
{
  node::write (out, n);
  return out;
}

inline
std::istream& operator>> (std::istream& in, node*& n)
{
  node::read (in, n);
  return in;
}

#endif
