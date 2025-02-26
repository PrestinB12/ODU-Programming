#include <utility>
#include <algorithm>
#include <numeric>

#include "Schedule.h"

using namespace std::rel_ops;

//------------------------------------------------------------------------------
/**
 * @todo sanity check - is this function complete?
 */
Schedule::Schedule()
{
}

//------------------------------------------------------------------------------
/**
 * @todo implement this method.
 */
int Schedule::getCredits() const
{
    // Replace this stub return.
    return -1;
}

//------------------------------------------------------------------------------
/**
 * @todo implement this function
 */
void Schedule::appendNoCheck(Course course)
{

}

//------------------------------------------------------------------------------
/**
 * @todo implement this function
 */
bool Schedule::wouldViolateCreditLimit(Course course) const
{
    // replace return true with the actual logic
    return true;
}

//------------------------------------------------------------------------------
/**
 * @todo implement this function
 */
bool Schedule::alreadyInSchedule(Course course) const
{
    // replace return false with the actual logic
    return false;
}

//------------------------------------------------------------------------------
/**
 * @todo implement this function
 */
void Schedule::display(std::ostream& outs) const
{
    // Write your output loop before this line
    outs << "  (" << getCredits() << " Total Credits)" << "\n";
}
