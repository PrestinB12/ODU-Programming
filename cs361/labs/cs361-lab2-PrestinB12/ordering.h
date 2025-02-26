#ifndef ORDERING_H
#define ORDERING_H

#include <algorithm>

/**
 * Given an array in which every element except the last is in sorted
 * (ascending) order, move the last element into the appropriate position
 * so that the entire array is sorted.
 * 
 * @param array an array of data elements, such that for any i,
 *        0 <= i < N-2 => array[i] <= array[i+1]
 * @param N  the number of elements in the array
 * @return the position into which the last element has been moved.
 */
template <typename T>
int shiftIntoPosition (T* array, int N) {
        int k = N-1;
    while (k > 0 && array[k] < array[k-1])
    {
        std::swap(array[k], array[k-1]);
        --k;
    }
    return k;
}

template <typename Iterator>
Iterator shiftIntoPosition (Iterator start, Iterator stop) {
Iterator current = stop;
--current;

if (current == start)
    return start;

Iterator previous = current;
--previous;

while (current != start && *current < *previous)
{
    std::swap(*current, *previous);
    current = previous;
    
    if (current != start)
        --previous;
}
return current;

}

#endif