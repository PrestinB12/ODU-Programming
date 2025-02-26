#include <iostream>
#include <fstream>
#include <string>

#include "matrix.h"
#include "counting.h"

using namespace std;


void solve (const Matrix<int>& enclosure)
{
	int c = countTheIslands(enclosure);
	cout << "The zoo can keep " << c << " jackalopes." << endl;
}

void readFrom(istream& in)
{
	int width, height;
	in >> width >> height;
	Matrix<int> enclosure(width, height);

	string line;
	getline (in, line);  // discard the first end-of-line

	for (int y = 0; y < height; ++y)
	{
		getline (in, line);
		for (int x = 0; x < width; ++x)
		{
			int terrain = 0;
			if (line[x] == 'x' || line[x] == 'X')
				terrain = -1;
			enclosure(x,y) = terrain;
		}
	}

	solve (enclosure);

}

int main (int argc, char** argv)
{
	{
		if (argc > 1)
		{
			ifstream in (argv[1]);
			readFrom(in);
		}
		else
		{
			readFrom (cin);
		}
	}
  return 0;
 
}
