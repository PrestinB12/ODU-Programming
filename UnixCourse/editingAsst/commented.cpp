/**
 * Performs the standard binary search using two comparisons per level.
 * Returns index where item is found or or the index where it chould
 * be inserted  if not found
 *
 * From Weiss,  Data Structures and Algorithm Analysis, 4e
 * ( modified SJ Zeil)
 */
template <typename Comparable>
int binarySearch( const Comparable* a, int size, const Comparable & x )
{
  int low = 0, high = size - 1;     // Set the bounds for the search

    while( low <= high )
    {
      // Examine the element at the midpoint 
      int mid = ( low + high ) / 2; 

       if( a[ mid ] < x )
         low = mid + 1;  // If x is in the array, it must be in the upper half.
       else if( a[ mid ] > x )
         high = mid - 1; // If x is in the array, it must be in the lower half.
       else
         return mid;   // Found
    }
    // Return the position where x would be inserted to
    // preserve the ordering within the array.
    return low; 
}
