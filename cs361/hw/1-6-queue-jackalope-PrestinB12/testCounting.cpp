#include "counting.h"
#include "matrix.h"
#include "unittest.h"
#include <algorithm>
#include <array>
#include <sstream>

using namespace std;

int input[3*4] = {
	0, 0, 1, 1,
	1, 1, 0, 1,
	0, 1, 0, 0
};


int expected1[3*4] = {
	5, 5, 1, 1,
	1, 1, 0, 1,
	0, 1, 0, 0
};

int expected2[3*4] = {
	0, 0, 1, 1,
	1, 1, 4, 1,
	0, 1, 4, 4
};

int expected3[3*4] = {
	0, 0, 1, 1,
	1, 1, 0, 1,
	-1, 1, 0, 0
};


UnitTest(testFill) {
	Matrix<int> m0 (3, 4, input, input+3*4);
	Matrix<int> m1 = m0;
	fill(m1, 5, Position(0,0));
	Matrix<int> exp1 (3, 4, expected1, expected1+3*4);
	assertThat(m1, is(exp1));

	Matrix<int> m2 = m0;
	fill(m2, 4, Position(1,2));
	Matrix<int> exp2 (3, 4, expected2, expected2+3*4);
	assertThat(m2, is(exp2));
	
	Matrix<int> m3 = m0;
	fill(m3, -1, Position(2,0));
	Matrix<int> exp3 (3, 4, expected3, expected3+3*4);
	assertThat(m3, is(exp3));
}

UnitTest(testCount) {
	Matrix<int> m0 (3, 4, input, input+3*4);
	assertThat(countTheIslands(m0), is(3));
}


