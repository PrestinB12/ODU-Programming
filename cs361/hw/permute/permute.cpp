#include <cstdlib>
#include <algorithm>
#include <vector>

using namespace std;

unsigned rnd(unsigned limit)
{
  return rand() % limit;
}

//  Generate a random permutation of the integers from
//  0 .. n-1, storing the results in array a.
//
void permute (int a[], int n)
{
  // Array of booleans: used[k] is true if we have already
  // put k somewhere into the array a
  bool* used = new bool[n];
  fill (used, used+n, false);
  for (int i = 0; i < n; i++)
    {
      // Guess at a value to put into a[i]
      a[i] = rnd(n);
      while (used[a[i]])
        {
	 // If it's one that we've already used, guess again.
         a[i] = rnd(n);
        }
      used[a[i]] = true;
    }
  delete [] used;
}
