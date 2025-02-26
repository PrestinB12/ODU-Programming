#ifndef COURSE_H
#define COURSE_H

#include <iostream>
#include <initializer_list>
#include <iterator>
#include <string>
#include <list>
#include "courseName.h"

using namespace std;

class Course {

	//** You may not change the declarations in this private: area.

    //CourseName name;           ///< Name of the course
    //int numberOfPrerequisites; ///< How many prereqs are currently in the array?
    //int maxPrerequisites;      ///< How many prereqs will fit into the array?
    //CourseName * prereqs;      ///< Pointer to an array of course names.
    //std::list<CourseName> prereqs;

private:
	CourseName name;           ///< Name of the course
    int numberOfPrerequisites; ///< How many prereqs are currently in the array?
    //int maxPrerequisites;      ///< How many prereqs will fit into the array?
    //CourseName * prereqs;      ///< Pointer to an array of course names.
    std::list<CourseName> prereqs;

public:
    typedef std::list<CourseName>::const_iterator iterator;
    typedef std::list<CourseName>::const_iterator const_iterator;


	/**
	 * Create a new course named CourseName() and having no
	 * known prerequisites;
	 */
	Course();


	/**
	 * Create a new course named cname and having no
	 * known prerequisites;
	 */
	Course (const CourseName& cname);


	/**
	 * Create a new course named cname and having a list
	 * of known prerequisites;
	 */
	Course (const CourseName& cname, std::initializer_list<CourseName> prereqs);


	// Because this class no longer has pointers among its data members,
	// we no longer need our own Big 3.

	//Course (const Course& c);
	//~Course();

	const Course& operator= (const Course& c);
	
	//CourseName getPrereq(int i) const;


	/**
	 * @return the name of the course
	 */
	CourseName getName() const {return name;}

	/**
	 * @return the number of known prerequisites to this course.
	 */
	int getNumberOfPrereqs() const;

	/**
	 * Adds cname to the list of prerequisites for this course.
	 * If this name is already in the list, this has no effect.
	 *
	 * @param cname name of a prerequisite course
	 */
	void addPrereq(const CourseName& cname);

	/**
	 * Removes cname from the list of prerequisites for this course.
	 * If this name is not in the list, this has no effect.
	 *
	 * @param cname name of a prerequisite course
	 */
	void removePrereq(const CourseName& cname);


	std::list<CourseName>::iterator begin();
	std::list<CourseName>::iterator end();
	std::list<CourseName>::const_iterator begin() const;
	std::list<CourseName>::const_iterator end() const;

	/**
	 * Compare two courses for equality.
	 */
	bool operator== (const Course& right) const;

	/**
	 * Compare two courses for ordering.
	 */
	bool operator< (const Course& right) const;
	//const Course& Course::operator= (const Course& c);

	//const std::list<CourseName>& getPrereqs() const;

	/**
     * For use by instructor only.
     */
    bool sanityCheck();

	friend std::ostream& operator<< (std::ostream& out, const Course& c);
};

std::ostream& operator<< (std::ostream& out, const Course& c);

#endif