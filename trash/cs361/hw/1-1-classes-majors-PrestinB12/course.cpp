#include "course.h"

#include <cassert>
#include <iostream>
#include <string>
#include <utility>

using namespace std;


/**
 * Create a new course named cname and having no
 * known prerequisites;
 */
Course::Course (const CourseName& cname)
: name(cname), numberOfPrerequisites(0), maxPrerequisites(10),
  prereqs(new CourseName[maxPrerequisites])
{

}


/**
 * @return the number of known prerequisites to this course.
 */
int Course::getNumberOfPrereqs() const
{
	return numberOfPrerequisites;
}

/**
 * Adds cname to the list of prerequisites for this course.
 * If this name is already in the list, this has no effect.
 *
 * @param cname name of a prerequisite course
 */
void Course::addPrereq(const CourseName& cname)
{
	for (int i = 0; i < numberOfPrerequisites; ++i)
		if (prereqs[i] == cname)
			return;
	assert (numberOfPrerequisites < maxPrerequisites);
	prereqs[numberOfPrerequisites] = cname;
	++numberOfPrerequisites;
}

/**
 * Removes cname from the list of prerequisites for this course.
 * If this name is not in the list, this has no effect.
 *
 * @param cname name of a prerequisite course
 */
void Course::removePrereq(const CourseName& cname)
{
	for (int i = 0; i < numberOfPrerequisites; ++i)
		if (prereqs[i] == cname)
		{
			for (int j = i+1; j < numberOfPrerequisites; ++j)
				prereqs[j-1] = prereqs[j];
			--numberOfPrerequisites;
			break;
		}
}

/**
 * Get the name of the i_th prerequisite.
 *
 * @precondition 0 <= i && i < getNumberofPrereqs()
 * @param i index of the prerequisite to retrieve
 * @return name of the prerequisite course
 */
CourseName Course::getPrereq(int i) const
{
	assert (i >= 0 && i < numberOfPrerequisites);
	return prereqs[i];
}

