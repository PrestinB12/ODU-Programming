#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include "node.h"
#include "testUtilities.h"
#include "unittest.h"

using namespace std;

// Uncomment the next line to turn off test timing (e.g., while debugging a failed test).
// #define DEFAULT_UNIT_TEST_TIME_LIMIT 0L

string qWater = "Does it live in the water?";
string qWebbed = "Does it have webbed feet?";
string aDuck = "Duck";
string aFish = "Fish";
string aCat = "Cat";

string test1 =
    string("Q Does it live in the water?\n") +
    "Q   Does it have webbed feet?\n" +
    "A     Duck\n" +
    "A     Fish\n" +
    "A   Cat\n";

string test2 = "A     Duck\n";

string qBreadBox = "Is it bigger than a breadbox?";
string aElephant = "elephant";

string test3 =
    string("Q Is it bigger than a breadbox?\n") +
    "A  elephant\n" +
    "Q  Does it live in the water?\n" +
    "Q    Does it have webbed feet?\n" +
    "A      Duck\n" +
    "A      Fish\n" +
    "A    Cat\n";

node *tree1 = new node(qWater,
                       new node(qWebbed,
                                new node(aDuck),
                                new node(aFish)),
                       new node(aCat));

node *tree2 = new node(aDuck);

node *tree3 =
    new node(qBreadBox,
             new node(aElephant),
             new node(qWater,
                      new node(qWebbed,
                               new node(aDuck),
                               new node(aFish)),
                      new node(aCat)));

UnitTest(testRead1)
{
  istringstream in1(test1);
  node *actual;
  node::read(in1, actual);

  assertTrue(isomorphic(actual, tree1));
}

UnitTest(testRead2)
{
  istringstream in1(test2);
  node *actual;
  node::read(in1, actual);

  assertTrue(isomorphic(actual, tree2));
}

UnitTest(testRead3)
{
  istringstream in1(test3);
  node *actual;
  node::read(in1, actual);

  assertTrue(isomorphic(actual, tree3));
}

UnitTest(testWrite1)
{
  ostringstream out1;
  node::write(out1, tree1);

  assertEqual(normalizeWhiteSpace(out1.str()), normalizeWhiteSpace(test1));
}

UnitTest(testWrite2)
{
  ostringstream out1;
  node::write(out1, tree2);

  assertEqual(normalizeWhiteSpace(out1.str()), normalizeWhiteSpace(test2));
}

UnitTest(testWrite3)
{
  ostringstream out1;
  node::write(out1, tree3);

  assertEqual(normalizeWhiteSpace(out1.str()), normalizeWhiteSpace(test3));
}

