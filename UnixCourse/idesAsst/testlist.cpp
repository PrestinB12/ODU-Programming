#include <iostream>
#include <string>
#include "namelist.h"

using std::cout;
using std::endl;

const char* names[] = {"Adams", "Baker", "Clarke", "Daniels", "Evans",
		 "Franklin", "Gerhardt", "Hardy", "Ives", "Jacobs",
		 "Knight", "Lee", "Miller", "Newsome", "O'Conner",
		 "Peterson", "Quen", "Reilly", "Smith", "Thompson",
		 "Unser", "Valdez", "Wilson", "Xavier", "Young",
		       "Zimmerman"
};  


void testList (int numberOfItems)
{
  NameList L;
  // Test part 1 - try adding to the front

  for (int i = 0; i < numberOfItems; ++i)
    {
      L.addToFront (names[i]);
    }
  L.print(cout);
  cout << endl;
  cout << "**end of test " << numberOfItems << ", part 1 ***" << endl;


  // Test part 2 - try adding to the end
  L.clear();
  for (int i = 0; i < numberOfItems; ++i)
    {
      L.addToEnd (names[i]);
    }
  L.print(cout);
  cout << endl;
  cout << "**end of test " << numberOfItems << ", part 2 ***" << endl;

}


int main()
{
  for (int test = 2; test >= 0; --test)
    {
      testList(test);
    }

  return 0;
}
