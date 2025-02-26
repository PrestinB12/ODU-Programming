#include "course.h"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <utility>
#include <list>
#include "courseName.h"

using namespace std;

//review 3 example 2 in cs330 house one specifically, look at 


/**
 * Create a new course named CourseName() and having no
 * known prerequisites;
 */
Course::Course()
: name(), prereqs()
{
	//nothing
}

/**
 * Create a new course named cname and having no
 * known prerequisites;
 */
Course::Course (const CourseName& cname)
: name(cname), prereqs()
{
	prereqs.clear();
}

Course::Course(const CourseName& cname, std::initializer_list<CourseName> prereqsList)
: name(cname), prereqs(prereqsList)
{
	prereqs.sort();
}

/**
 * @return the number of known prerequisites to this course.
 */
int Course::getNumberOfPrereqs() const
{
	return prereqs.size();
}

/**
 * Adds cname to the list of prerequisites for this course.
 * If this name is already in the list, this has no effect.
 *
 * @param cname name of a prerequisite course
 */

std::list<CourseName>::iterator Course::begin()
{
	return prereqs.begin();
}
std::list<CourseName>::iterator Course::end()
{
	return prereqs.end();
}
std::list<CourseName>::const_iterator Course::begin() const
{
	return prereqs.begin();
}
std::list<CourseName>::const_iterator Course::end() const
{
	return prereqs.end();
}

void Course::addPrereq(const CourseName& cname)
{
	prereqs.remove(cname);
	auto it = prereqs.begin();
	//std::list<CourseName>::const_iterator itr = prereqs.begin();
	while(it != prereqs.end() && *it < cname)
		
		++it;
	prereqs.insert(it, cname);
	
	//prereqs.push_back(cname);
	//assert (numberOfPrerequisites < maxPrerequisites);
	//prereqs[numberOfPrerequisites] = cname;
	//++numberOfPrerequisites;

}

/**
 * Removes cname from the list of prerequisites for this course.
 * If this name is not in the list, this has no effect.
 *
 * @param cname name of a prerequisite course
 */
void Course::removePrereq(const CourseName& cname)
{
	prereqs.remove(cname);
}

/**
 * Get the name of the i_th prerequisite.
 *
 * @precondition 0 <= i && i < getNumberofPrereqs()
 * @param i index of the prerequisite to retrieve
 * @return name of the prerequisite course
 */

/*
	//Not needed
CourseName Course::getPrereq(int i) const
{
	//CourseName * prereqs;
	assert (i >= 0 && i < numberOfPrerequisites);
	return prereqs;
}
*/

/**
 * Compare two courses for equality.
 */
bool Course::operator== (const Course& right) const
{
	using namespace std::rel_ops;
	//CourseName * prereqs;

	if (name != right.name)
		return false;
	if (prereqs.size() != right.prereqs.size())
		return false;
	auto it1 = prereqs.begin();
	auto it2 = right.prereqs.begin();
	while (it1 != prereqs.end() && it2 != right.prereqs.end())
	{
		if (*it1 != *it2)
		{
			return false;
		}
		++it1;
		++it2;
	}
	return (it1 != prereqs.end() && it2 != right.prereqs.end());
}

/**
 * Compare two courses for ordering.
 */
bool Course::operator< (const Course& right) const
{
	using namespace std::rel_ops;
	
	if (name != right.name)
		return name < right.name;
	if (prereqs.size() != right.prereqs.size())
		return prereqs.size() < right.prereqs.size();
	auto it1 = prereqs.begin();
	auto it2 = right.prereqs.begin();
	while (it1 != prereqs.end() && it2 != right.prereqs.end())
	{
		if (*it1 != *it2)
		{
			return *it1 < *it2;
		}
		++it1;
		++it2;
	}
	return false;
}

/*	
//Not Needed
Course::Course (const Course& c)
: name(c.name), numberOfPrerequisites(c.numberOfPrerequisites),
  maxPrerequisites(c.maxPrerequisites)
{
	//CourseName * prereqs;
	prereqs = new CourseName[maxPrerequisites];
	for (int i = 0; i < numberOfPrerequisites; ++i)
		prereqs = c.prereqs;
}

	//Also Not Needed
Course::~Course()
{
	//CourseName * prereqs;
	delete [] prereqs;
}
*/

const Course& Course::operator= (const Course& c)
{
	if (&c != this) // Check for self-assignment
    {
        //CourseName * prereqs;
		name = c.name;
        //numberOfPrerequisites = c.numberOfPrerequisites;
        //maxPrerequisites = c.maxPrerequisites;

        // Deallocate existing memory for prereqs
        //delete[] prereqs;

        // Allocate new memory and copy elements
        if (&c != this)
    {
        name = c.name;
       //numberOfPrerequisites = c.numberOfPrerequisites;
        prereqs = c.prereqs;
    }
    return *this;
	}
}

std::ostream& operator<< (std::ostream& out, const Course& c)
{
	out << c.getName() << " (" ;

	for(const CourseName& prereq : c.prereqs)
	{
		out << prereq;
		
		if(!(prereq == c.prereqs.back()))
		{
			out << ",";
		}
	}

	out << ")";
	return out;
}