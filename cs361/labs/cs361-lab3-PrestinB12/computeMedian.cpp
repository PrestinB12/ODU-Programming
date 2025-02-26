#include <array>
#include <algorithm>
#include <iostream>
#include <vector>

#include "median.h"

using namespace std;


Median md;

/**
 * Read a series of non-negative numbers from in, placing them into
 * numbers in ascending order.  Input ends at the first negative value.
 * 
 * @param in the input stream from which to read
 * @param numbers the sequence of numbers that have been read,
 *                sorted into ascending order
 */
void read (std::istream& in)
{
    double d = 0.0;
    while (in >> d)
    {
        md.add(d);
    }
}


int main(int argc, char** argv) {
    cout << "Enter a series of numbers, spearated by blanks or line breaks.\n";
    cout << "Enter ^Z (Windows) or ^D (Linux or MacOS) at the start of a line to end." << endl;
    read (cin);
    cout << "median is " << md.median() << endl;
}

