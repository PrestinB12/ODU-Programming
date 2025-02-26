#include <cstdlib>
#include <algorithm>
#include <vector>

using namespace std;

unsigned rnd(unsigned limit)  //O(1)
{
  return rand() % limit;  //O(1)
}

//  Generate a random permutation of the integers from
//  0 .. n-1, storing the results in array a.
//
void permute (int a[], int n) 
{
  // Array of booleans: used[k] is true if we have already
  // put k somewhere into the array a
  bool* used = new bool[n]; //O(1)
  fill (used, used+n, false); //O(n)
  for (int i = 0; i < n; i++) //O(n)
    {
      // Guess at a value to put into a[i]
      a[i] = rnd(n);  //O(1)
      while (used[a[i]])  //O(1), average is i divided by 2 (or i/2)
        {
	 // If it's one that we've already used, guess again.
         a[i] = rnd(n); //O(1)
        }
      used[a[i]] = true;  //O(1)
    }
  delete [] used; //O(1)
}