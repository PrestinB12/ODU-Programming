#include <cstdlib>
#include <iostream>
#include <sstream>
#include <time.h>

using namespace std;

void permute (int[], int);


int main(int argc, char** argv)
{
  if (argc != 3)
    {
      cerr << "When you run this program, you must supply two parameters.\n" 
           << "The first is the size of the array you want to permute.\n"
           << "The second is the number of trials you want to perform.\n"
           << "\n"
           << "For example, if you called this program pdriver, you\n"
           << "might invoke it as:\n"
           << "   pdriver 100 10 \n"
           << "to generate 10 random permutations of 100 elements each."
	     << endl;
      return 1;
    }

  int N;
  int trials;

  {
    istringstream arg1 (argv[1]);
    arg1 >> N;

    istringstream arg2 (argv[2]);
    arg2 >> trials;
  }
  
  int *array = new int[N];

  srand(time(0));
  for (int t = 0; t < trials; t++)
    {
      permute (array, N);
      // for (int i = 0; i < N; ++i) cout << array[i] << ' '; cout << endl;
    }

  return 0;
}


   
