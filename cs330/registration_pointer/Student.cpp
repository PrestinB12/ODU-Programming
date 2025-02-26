#include <utility>
#include "Student.h"

// Allow the compiler to define the remaining
// comparison operators
using namespace std::rel_ops;

//------------------------------------------------------------------------------
Student::Student()
    :Student("ERROR")
{
}

//------------------------------------------------------------------------------
Student::Student(std::string n)
    :name(n)
{
    // @todo create a new empty schedule
}

//------------------------------------------------------------------------------
// @todo implement this function
Student::Student(const Student& src)
{
    // @todo copy the name

    // @todo create a deep copy of src.schedule
}

//------------------------------------------------------------------------------
// @todo implement this function
Student::~Student()
{
    // @todo make sure that the schedule attribute (data member) is deallocated
}

//------------------------------------------------------------------------------
void swap(Student& lhs, Student& rhs)
{
    // @todo swap the lhs name and rhs name

    // @todo swap the lhs schedule and rhs schedule
}

//------------------------------------------------------------------------------
void Student::display(std::ostream &outs) const
{
    outs << " " << name << "\n";

    // @todo Add the line to output the schedule.
}

//------------------------------------------------------------------------------
bool Student::enrollIn(const Course &toAdd)
{
    return schedule->add(toAdd);
}


