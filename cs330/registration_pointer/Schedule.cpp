#include <utility>
#include <algorithm>
#include <numeric>

#include "Schedule.h"

using namespace std::rel_ops;

const int Schedule::CREDIT_LIMIT = 12;

//------------------------------------------------------------------------------
int Schedule::getCredits() const
{
    return std::accumulate(this->begin(), this->end(), 0,
                           [](int c, const Course& crs) {
                               return c + crs.getCredits();
                           });
}

//------------------------------------------------------------------------------
bool Schedule::add(Course course)
{
    if (wouldViolateCreditLimit(course)) {
        return false;
    }

    if (alreadyInSchedule(course)) {
        return false;
    }

    // Success - all checks passed
    allCourses.push_back(course);
    return true;
}

//------------------------------------------------------------------------------
bool Schedule::wouldViolateCreditLimit(Course course) const
{
    return (this->getCredits() + course.getCredits()) > CREDIT_LIMIT;
}

//------------------------------------------------------------------------------
bool Schedule::alreadyInSchedule(Course course) const
{
    return allCourses.end() != std::find(this->begin(), this->end(), course);
}

//------------------------------------------------------------------------------
std::ostream& operator<<(std::ostream &outs, const Schedule &prt)
{
    for (const Course& crs : prt) {
        outs << "  - " << crs << "\n";
    }

    outs << "  (" << prt.getCredits() << " Total Credits)" << "\n";

    return outs;
}
