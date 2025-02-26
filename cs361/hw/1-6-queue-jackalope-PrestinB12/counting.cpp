#include "counting.h"
#include "matrix.h"
#include <list>
#include <queue>

using namespace std;

/**
 * Count the number of islands (areas composed entirely of
 * non-negative values connected either horizontally or
 * vertically.
 *
 * @param enclosure a rectangular area of represented with -1 for water
 *        and zeros for land.
 * @return the number of unconnected islands
 */
int countTheIslands(const Matrix<int> &enclosure)
{
	// Should use the fill function

	int islands = 0;	//islands defined as islands(s)
	bool visitedIslands[enclosure.length1()][enclosure.length2()] = {false};	// The matrix is constant (const) so we cannot edit the values whatsoever (that is why they are constant LOL)

	for (int i = 0; i < enclosure.length1(); ++i)	//To loop thru the matrix
	{
		for (int j = 0; j < enclosure.length2(); ++j)
		{
			if (enclosure(i, j) == 0 && !visitedIslands[i][j])	// If we have not visited the island yet
			{
				islands++;	//if an island is found, increment the count
				queue<Position> positions;
				positions.push(Position(i, j));	//The starting point of the islands

				while (!positions.empty())	//Go thru all positions in the que
				{
					Position current = positions.front();	//current location
					positions.pop();	//remove the positions that are visited (visited islands or islands)
					int r = current.x;	//Row defined as r
					int c = current.y;	//Column is c

					if (r >= 0 && r < enclosure.length1() && c >= 0 && c < enclosure.length2() && enclosure(r, c) == 0 && !visitedIslands[r][c])	//Using a range-based for-loop for islands not yet visited
					{
						visitedIslands[r][c] = true;	//adding to the list of visited islands
						positions.push(Position(r - 1, c)); // Up position
						positions.push(Position(r + 1, c)); // Down position
						positions.push(Position(r, c - 1)); // Left position
						positions.push(Position(r, c + 1)); // Right position
					}
				}
			}
		}
	}
	return islands;	//returns the island count 
}

/**
 * Starting at position p0, put valueToFill into that position and into
 * any positions containing zero connected to p0 by one or more horizontal
 * or vertical steps through other elements also containing zero.
 */
void fill (Matrix<int> &enclosure, int valueToFill, Position p0)
{
	//Must use std::queue
	queue<Position> positions;
	positions.push(p0);	//This adds to the position we start off with (position zero or p0)

	while (!positions.empty())	//Goes thru all positions on the que that are not empty
	{
		Position current = positions.front();
		positions.pop();
		int r = current.x;	//Row set as r
		int c = current.y;	//column set as c

		if (r >= 0 && r < enclosure.length1() && c >= 0 && c < enclosure.length2() && enclosure(r, c) == 0)	//using a range base for-loop
		{
			enclosure(r, c) = valueToFill;	//Sets the current value of rows and columns 

			positions.push(Position(r - 1, c));	//push to push the next points to the que
			positions.push(Position(r + 1, c));
			positions.push(Position(r, c - 1));
			positions.push(Position(r, c + 1));
		}
	}
}







