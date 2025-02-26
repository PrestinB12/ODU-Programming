/*
 * counting.h
 *
 *  Created on: Jun 10, 2020
 *      Author: zeil
 */

#ifndef COUNTING_H_
#define COUNTING_H_

#include <iostream>
#include "matrix.h"


struct Position {
	int x;
	int y;

	Position (int x0, int y0)
	: x(x0), y(y0) {}
};

inline
std::ostream& operator<< (std::ostream& out, Position p)
{
	out << '(' << p.x << ',' << p.y << ')';
	return out;
}

/**
 * Count the number of islands (areas composed entirely of
 * non-negative values connected either horizontally or
 * vertically.
 *
 * @param enclosure a rectangular area of represented with -1 for water
 *        and zeros for land.
 * @return the number of unconnected islands
 */
int countTheIslands (const Matrix<int>& enclosure);

/**
 * Starting at position p0, put valueToFill into that position and into
 * any positions containing zero connected to p0 by one or more horizontal
 * or vertical steps through other elements also containing zero.
 */
void fill (Matrix<int>& enclosure, int valueToFill, Position p0);

#endif /* COUNTING_H_ */