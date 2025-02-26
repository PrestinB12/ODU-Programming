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
    //yes
}

//------------------------------------------------------------------------------
/**
 * @todo implement this method.
 */
int Schedule::getCredits() const
{
    return getCredits();
    
    // Replace this stub return.
}

//------------------------------------------------------------------------------
/**
 * @todo implement this function
 */
void Schedule::appendNoCheck(Course course)
{
    allCourses.push_back(course);   //use push-back to add new thing to the end of the vector

    //return false;
}

//------------------------------------------------------------------------------
/**
 * @todo implement this function
 */
bool Schedule::wouldViolateCreditLimit(Course course) const
{
    if (course.getCredits() >= 12)
    {
        return false;
    }
    else (course.getCredits());
    {
        return false;
    }
    
    // replace return true with the actual logic
    return false;
}

//------------------------------------------------------------------------------
/**
 * @todo implement this function
 */
bool Schedule::alreadyInSchedule(Course course) const
{
    const_iterator itr = allCourses.begin();

    while(itr != allCourses.end())
    {
        if (*itr == course)
        {
            std::cerr << "This course is already in your class schedule" << "\n";   //output
            return true;
        }

        ++itr;

        std::cerr << "This course is not in your schedule and is able to be selected" << "\n";  //output
    }
    
    // replace return false with the actual logic
    return false;
}

//------------------------------------------------------------------------------
/**
 * @todo implement this function
 */
void Schedule::display(std::ostream& outs) const
{
    const_iterator itr = allCourses.begin();    //iterator itr

    while (itr != allCourses.end());    //while loop was more familiar with than range-based for-loop
    {
        outs << " - " << *itr << "\n";

        ++itr;  //iterator incriminate
    }

    // Write your output loop before this line
    outs << "  (" << getCredits() << " Total Credits)" << "\n";

    //return false;
}
