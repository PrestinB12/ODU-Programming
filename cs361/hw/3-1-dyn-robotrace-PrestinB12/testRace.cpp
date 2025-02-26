#include "checkpoint.h"
#include "race.h"
#include "unittest.h"
#include <vector>
#include <algorithm>

using namespace std;

Checkpoint cp0(0, 0, 0);
Checkpoint cp100(100, 100, 0);

UnitTest(NoCheckPoints) {
	vector<Checkpoint> raceCourse {cp0, cp100};

	double time = minRaceTime(raceCourse);

    // Best solution is to bypass the checkpoint for a 10 pt penalty
	assertThat (time, isApproximately(141.4, 0.1));
}


UnitTest(RaceWithSimpleBypass) {
	Checkpoint cp(100, 0, 10);
	vector<Checkpoint> raceCourse {cp0, cp, cp100};

	double time = minRaceTime(raceCourse);

    // Best solution is to bypass the checkpoint for a 10 pt penalty
	assertThat (time, isApproximately(151.4, 0.1));
}

UnitTest(RaceWithNoBypass) {
	Checkpoint cp(100, 0, 65);
	vector<Checkpoint> raceCourse {cp0, cp, cp100};

	double time = minRaceTime(raceCourse);

    // Best solution is to take the checkpoint
	assertThat (time, isApproximately(201.0, 0.1));
}

UnitTest(ZigZagByPass) {
	Checkpoint cp1(100, 0, 200);
	Checkpoint cp2(0, 100, 50);
	vector<Checkpoint> raceCourse {cp0, cp1, cp2, cp100};

	double time = minRaceTime(raceCourse);

    // Best solution is to bypass cp1
	assertThat (time, isApproximately(251.0, 0.1));
}

UnitTest(ZigZagNoByPass) {
	Checkpoint cp1(100, 0, 150);
	Checkpoint cp2(0, 100, 150);
	vector<Checkpoint> raceCourse {cp0, cp1, cp2, cp100};

	double time = minRaceTime(raceCourse);

    // Best solution is to do both checkpoints
	assertThat (time, isApproximately(343.4, 0.1));
}
