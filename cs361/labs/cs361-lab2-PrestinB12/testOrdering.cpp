#include "unittest.h"
#include "ordering.h"
#include <array>
#include <algorithm>
#include <list>
#include <vector>

using namespace std;


UnitTest(testShiftMiddle) {
    int input[] = {2, 4, 6, 8, 5};
    int expected[] = {2, 4, 5, 6, 8};

    int pos = shiftIntoPosition (input, 5);

    assertThat (pos, isEqualTo(2));

    assertThat (arrayOfLength(input, 5), matches(arrayOfLength(expected, 5)));
}

UnitTest(testShiftBegin) {
    int input[] = {2, 4, 6, 8, 1};
    int expected[] = {1, 2, 4, 6, 8};

    int pos = shiftIntoPosition (input, 5);

    assertThat (pos, isEqualTo(0));

    assertThat (arrayOfLength(input, 5), matches(arrayOfLength(expected, 5)));
}

UnitTest(testShiftEnd) {
    int input[] = {2, 4, 6, 8, 10};
    int expected[] = {2, 4, 6, 8, 10};

    int pos = shiftIntoPosition (input, 5);

    assertThat (pos, isEqualTo(4));

    assertThat (arrayOfLength(input, 5), matches(arrayOfLength(expected, 5)));
}

UnitTest(testShiftEmpty) {
    int input[] = {10};
    int expected[] = {10};

    int pos = shiftIntoPosition (input, 1);

    assertThat (pos, isEqualTo(0));

    assertThat (arrayOfLength(input, 1), matches(arrayOfLength(expected, 1)));
}


// == Template tests ==


UnitTest(testShiftMiddleD) {
    double input[] = {2, 4, 6, 8, 5};
    double expected[] = {2, 4, 5, 6, 8};

    int pos = shiftIntoPosition (input, 5);

    assertThat (pos, isEqualTo(2));

    assertThat (arrayOfLength(input, 5), matches(arrayOfLength(expected, 5)));
}

UnitTest(testShiftBeginS) {
    string input[] = {"2", "4", "6", "8", "1"};
    string expected[] = {"1", "2", "4", "6", "8"};

    int pos = shiftIntoPosition (input, 5);

    assertThat (pos, isEqualTo(0));

    assertThat (arrayOfLength(input, 5), matches(arrayOfLength(expected, 5)));
}

UnitTest(testShiftEndS) {
    string input[] = {"2", "4", "6", "8", "A"};
    string expected[] = {"2", "4", "6", "8", "A"};

    int pos = shiftIntoPosition (input, 5);

    assertThat (pos, isEqualTo(4));

    assertThat (arrayOfLength(input, 5), matches(arrayOfLength(expected, 5)));
}



//  == Iterator tests ==


UnitTest(testShiftMiddleV) {
    vector<int> input {2, 4, 6, 8, 5};
    vector<int> expected {2, 4, 5, 6, 8};

    vector<int>::iterator pos = shiftIntoPosition (input.begin(), input.end());

    assertThat (pos, isEqualTo(input.begin()+2));

    assertThat (contentsOf(input), matches(contentsOf(expected)));
}

UnitTest(testShiftBeginA) {
    int input[] = {2, 4, 6, 8, 1};
    int expected[] = {1, 2, 4, 6, 8};

    int* pos = shiftIntoPosition (input, input+5);

    assertThat (pos-input, isEqualTo(0));

    assertThat (arrayOfLength(input, 5), matches(arrayOfLength(expected, 5)));
}

UnitTest(testShiftEndL) {
    list<string> input {"2", "4", "6", "8", "A"};
    list<string> expected {"2", "4", "6", "8", "A"};

    list<string>::iterator pos = shiftIntoPosition (input.begin(), input.end());

    assertThat (++pos, isEqualTo(input.end()));

    assertThat (contentsOf(input), matches(contentsOf(expected)));
}

UnitTest(testShiftEmptyVL) {
    vector<int> input;
    input.push_back(10);

    list<int> expected {10};

    auto pos = shiftIntoPosition (input.begin(), input.end());

    assertThat (pos, isEqualTo(input.begin()));

    assertThat (contentsOf(input), matches(contentsOf(expected)));
}