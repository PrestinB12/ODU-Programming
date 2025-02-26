#include "checkpoint.h"
#include "race.h"
#include <algorithm>
#include <cmath>
#include <limits>
#include <vector>

using namespace std;

double distanceBetween(const Checkpoint& cp1, const Checkpoint& cp2);

double minRaceTime(const vector<Checkpoint>& raceCourse) 
{
    vector<double> collectedPenalties;
    collectedPenalties.push_back(0);

    for (unsigned i = 1; i < raceCourse.size(); ++i) 
    {
        collectedPenalties.push_back(collectedPenalties[i - 1] + raceCourse[i].penalty);
    }

    vector<double> rr(raceCourse.size(), std::numeric_limits<double>::max());
    rr[0] = 0.0;

    for (unsigned goal = 1; goal < raceCourse.size(); ++goal) 
    {
        for (unsigned i = 0; i < goal; ++i) 
        {
            double toI = rr[i];
            double pauseAtI = 1.0;
            double iToGoalDistance = distanceBetween(raceCourse[i], raceCourse[goal]);
            double iToGoalPenalties = collectedPenalties[goal - 1] - collectedPenalties[i];
            double score = toI + pauseAtI + iToGoalDistance + iToGoalPenalties;
            rr[goal] = min(rr[goal], score);
        }
    }
    return rr.back() - 1.0;
}


double distanceBetween(const Checkpoint& cp1, const Checkpoint& cp2) 
{
    double dx = cp1.x - cp2.x;
    double dy = cp1.y - cp2.y;
    return sqrt(dx * dx + dy * dy);
}

