#include "checkpoint.h"
#include "race.h"

#include <iomanip>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;




void robot (istream& in)
{
  int nTargets;
  in >> nTargets;

  vector<Checkpoint> course;

  Checkpoint cpoint (0, 0, 0);
  course.push_back (cpoint);

  for (int i = 0; i < nTargets; ++i)
    {
      in >> cpoint.x >> cpoint.y >> cpoint.penalty;
      course.push_back (cpoint);
    }
  cpoint = Checkpoint(100, 100, 0);
  course.push_back (cpoint);

  cout << fixed << setprecision(3) << minRaceTime(course) << endl;
}


int main (int argc, char** argv)
{
  if (argc == 1)
    robot(cin);
  else
    {
      ifstream in (argv[1]);
      robot (in);
    }
  return 0;
}


