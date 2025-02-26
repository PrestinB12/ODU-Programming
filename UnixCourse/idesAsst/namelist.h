#ifndef NAMELIST_H
#define NAMELIST_H

#include <iostream>
#include <string>




struct NameListNode {
  std::string name;
  NameListNode* next;

  NameListNode (std::string newName)
  {
    name = newName;
    next = 0;
  }

  ~NameListNode() {delete next; next = 0;}
  void print (std::ostream& out) const;
};


class NameList {
private:
  NameListNode* firstNode;

public:
  NameList () {firstNode = NULL;}

  ~NameList() {clear();}

  void addToFront (std::string newName);
  void addToEnd (std::string newName);

  void clear();

  void print (std::ostream& out) const;
};


#endif




