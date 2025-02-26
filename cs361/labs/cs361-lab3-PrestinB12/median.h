#ifndef MEDIAN_H
#define MEDIAN_H
#include <vector>

class Median
{
private:
    //int numberOfValues;
    //double data[8];
    std::vector<double> data;

public:
    /**
     * Constructor for the median calculator.
     * Initially, has 0 values.
    */
    Median();

    /**
     * Add a new value to the collection. Values are kept
     * in ascending order.
     * 
     * @param newValue a new value
    */
    void add (double newValue);

    /**
     * How many values have been added to the collection?
     * 
     * @returns number of values in the collection
    */
    int size() const;

    /**
     * Get the index_th elemet form the collection. The values ar kept in
     * ascneding order, so get(0) will return the smallest value and get(size()-1)
     * will return the largest.
     * 
     * @param index position of hte desired value
     * @returns the index_th largest value in the collection if 0 <= index < size(),
     *      returns NAN if index < 0 or index >= size()
    */
    double get(int index) const;

    /**
     * Computes the median average of the collection. This is either the middle value
     * (if the number of values is odd) or the midpoint between the two middle values
     * (if the number of values is even).
     * 
     * @returns The median average, or NAN if size() == 0.
    */
    double median() const;
};

#endif
