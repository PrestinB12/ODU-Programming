#include "unittest.h"
#include "ordering.h"
#include <vector>
#include <limits>
#include <cmath>

#include "median.h"

using namespace std;

UnitTest(testMedianConstructor) {
    Median md;
    assertThat (md.size(), is(0));
    assertTrue (isnan(md.median()));
    assertTrue (isnan(md.get(0)));
}

UnitTest(testMedianAdd) {
    Median md;

    md.add(2.0);

    assertThat (md.size(), is(1));
    assertThat (md.get(0), is(2.0));
    assertThat (md.median(), is(2.0));

    md.add (0.0);

    assertThat (md.size(), is(2));
    assertThat (md.get(0), is(0.0));
    assertThat (md.get(1), is(2.0));
    assertThat (md.median(), is(1.0));
}


UnitTest(testMedianOdd) {
    vector<double> input {2.0, 10.0, 8.0, 6.0, 4.0};
    vector<double> expected {2.0, 4.0, 6.0, 8.0, 10.0};

    Median md;

    for (unsigned i = 0; i < input.size(); ++i)
    {
        md.add(input[i]);
    }
    assertThat (md.size(), is(input.size()));

    for (unsigned i = 0; i < input.size(); ++i)
    {
        assertThat (md.get(i), is(expected[i]));
    }

    assertThat (md.median(), isEqualTo(6.0));
}

UnitTest(testMedianEven) {
    vector<double> input {2.0, 4.0, 6.0, 8.0, 10.0, 12.0};
    vector<double> expected {2.0, 4.0, 6.0, 8.0, 10.0, 12.0};

    Median md;

    for (unsigned i = 0; i < input.size(); ++i)
    {
        md.add(input[i]);
    }
    assertThat (md.size(), is(input.size()));

    for (unsigned i = 0; i < input.size(); ++i)
    {
        assertThat (md.get(i), is(expected[i]));
    }

    assertThat (md.median(), isEqualTo(7.0));
}

UnitTest(testMedianLongInput) {
    Median md;
    const int N = 1000; // use any even number

    for (unsigned i = 0; i <= N; ++i)
    {
        md.add((double)i);
    }
    assertThat (md.size(), is(N+1));

    for (unsigned i = 0; i <= N; ++i)
    {
        assertThat (md.get(i), is((double)(i)));
    }

    assertThat (md.median(), isEqualTo((double)(N/2)));
}
