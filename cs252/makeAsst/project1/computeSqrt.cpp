#include "sqrt.h"
#include <cstdlib>
#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
  if (argc != 2)
	{
	  cerr << "Usage: " << argv[0] << " number" << endl;
	  return -1;
	}

  double d = atof(argv[1]);
  cout << computeSqrt(d, 0.0001) << endl;

  return 0;
}
