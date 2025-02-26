#include <iomanip>

#include "Course.h"

//------------------------------------------------------------------------------
Course::Course()
    :number("ERROR 000"),
     crn(0),
     credits(0)
{
}

//------------------------------------------------------------------------------
Course::Course(std::string n, int c, int h)
    :number(n),
     crn(c),
     credits(h)
{
}

//------------------------------------------------------------------------------
bool Course::operator==(const Course& rhs) const
{
    return this->number == rhs.number;
}

//------------------------------------------------------------------------------
bool Course::operator<(const Course& rhs) const
{
    return this->number < rhs.number;
}

//------------------------------------------------------------------------------
void Course::display(std::ostream &outs) const
{
    outs << credits << " credits - "
         << number << " (CRN " << crn << ")";
}

//------------------------------------------------------------------------------
void Course::read(std::istream& ins)
{
    ins >> std::ws;
    ins >> number >> crn >> credits;
}

//------------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& outs, const Course& prt)
{
    prt.display(outs);

    return outs;
}

//------------------------------------------------------------------------------
std::istream& operator>>(std::istream& ins, Course& rd)
{
    rd.read(ins);

    return ins;
}

