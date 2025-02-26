#include <iostream>
#include "namelist.h"

using namespace std;



void NameListNode::print(std::ostream& out) const {
  out << name;
}


void NameList::addToFront (std::string name)
{
  NameListNode* newNode = new NameListNode(name);
  newNode->next = firstNode;
  firstNode = newNode;
}

void NameList::addToEnd (std::string name)
{
  NameListNode* newNode = new NameListNode(name);
  NameListNode* lastNode = firstNode;
  while (lastNode->next != NULL)
    lastNode = lastNode->next;
  lastNode->next = newNode;
}


void NameList::clear()
{
  delete firstNode;
  firstNode = 0;
}


void NameList::print (std::ostream& out) const
{
  NameListNode* current = firstNode;
  int columns = 0;
  while (current != NULL)
    {
      out << current->name;
      columns += current->name.length();
      if (current->next != NULL)
	{
	  out << ", ";
	  columns += 2;
	  if (columns > 64)
	    {
	      out << "\n";
	      columns = 0;
	    }
	}
      current = current->next;
    }
}
