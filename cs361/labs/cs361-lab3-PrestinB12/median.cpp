#include <algorithm>
#include <limits>
#include <cmath>
#include <vector>
#include "median.h"
#include <iostream>


using namespace std;
using std::vector;
/**
 * Constructor for the median calculator.
 * Initially, has 0 values.
 */
Median::Median()
{
}

/**
 * Add a new value to the collection. Values are kept
 * in ascending order.
 *
 * @param newValue a new value
 */
void Median::add(double newValue)
{
    // Add newValue to the end
   // data[numberOfValues] = newValue;
   // ++numberOfValues;
    data.push_back(newValue);
    // Now shift it to the left until it is in the correctly
    // ordered position
    int k = data.size() - 1;
    while (k > 0 && data[k] < data[k-1])
    {
        swap(data[k], data[k-1]);
        --k;
    }
}

/**
 * How many values have been added to the collection?
 *
 * @returns number of values in the collection
 */
int Median::size() const
{
    return data.size();
}

/**
 * Get the index_th elemet form the collection. The values ar kept in
 * ascneding order, so get(0) will return the smallest value and get(size()-1)
 * will return the largest.
 *
 * @param index position of hte desired value
 * @returns the index_th largest value in the collection if 0 <= index < size(),
 *      returns NAN if index < 0 or index >= size()
 */
double Median::get(int index) const
{
    if (index >= 0 && index < data.size()) {
        return data[index];
    } 
    else {
        return numeric_limits<double>::quiet_NaN();
    }
}

/**
 * Computes the median average of the collection. This is either the middle value
 * (if the number of values is odd) or the midpoint between the two middle values
 * (if the number of values is even).
 *
 * @returns The median average, or NAN if size() == 0.
 */
double Median::median() const
{
    if (data.size() > 0) {
        if (data.size() % 2 == 0) {
            int mid = data.size() / 2;
            return 0.5 * (data[mid] + data[mid-1]);
        } else {
            int mid = data.size() / 2;
            return data[mid];
        }
    } 
    else {
        return numeric_limits<double>::quiet_NaN();
    }
}
