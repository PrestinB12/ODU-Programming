#include "course.h"

bool constCheck (std::list<CourseName>::const_iterator&)
{
    return true;
}


bool Course::sanityCheck() {
    CourseName cn = name;
    int k = numberOfPrerequisites;
    std::list<CourseName> p = prereqs;
    Course::iterator iter = begin();
    return constCheck(iter);
}