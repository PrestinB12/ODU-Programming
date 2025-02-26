#ifndef SCHEDULE_H_INCLUDED
#define SCHEDULE_H_INCLUDED

#include <iostream>
#include <list>
#include <vector>

#include "Course.h"



//------------------------------------------------------------------------------
class Schedule {
    public:
        static const int CREDIT_LIMIT;

        // using CourseCollection = std::list<Course>;
        using CourseCollection = std::vector<Course>;

        using iterator       = CourseCollection::iterator;
        using const_iterator = CourseCollection::const_iterator;

    private:
        /**
         * All courses in _this_ schedule.
         */
        CourseCollection allCourses;

    public:
        Schedule() = default;

        Schedule(const Schedule& src) = default;

        ~Schedule() = default;

        Schedule& operator=(const Schedule& rhs) = default;

        /**
         * Retrieve the total number of credits
         */
        int getCredits() const;

        /**
         * Attempt to add a course AND
         * perform all validation checks by calling:
         *   - wouldViolateCreditLimit
         *   - alreadyInSchedule
         */
        bool add(Course course);

        /**
         * Check if adding this course would violate
         * the CREDIT_LIMIT. This is an evaluation of
         * (toAdd.getCredits() + this->totalCredits) > CREDIT_LIMIT
         *
         * @returns false if adding the course
         *    would not violate the CREDIT_LIMIT
         */
        bool wouldViolateCreditLimit(Course course) const;

        /**
         * Check if a course with the same number is already
         * present in the schedule.
         *
         * @returns true if while traversing the collection
         *   of courses, a course with the same course number
         *   was found
         */
        bool alreadyInSchedule(Course course) const;

        /**
         * Display a listing of each course and
         * the total number of credit hours
         */
        void display(std::ostream& outs) const;

        iterator begin();
        iterator end();

        const_iterator begin() const;
        const_iterator end() const;

        /**
         * Return the number of courses in the schedule
         */
        size_t size() const;

        /**
         * Return true if there are no classes stored.
         */
        bool isEmpty() const;

        /**
         * A convenient wrapper around the Copy Constructor.
         *
         * @return pointer to a copy of the current schedule
         */
        Schedule* clone() const;
};


//-----------------------------------------------------------------------------
inline
Schedule::iterator Schedule::begin()
{
    return allCourses.begin();
}

//-----------------------------------------------------------------------------
inline
Schedule::iterator Schedule::end()
{
    return allCourses.end();
}

//-----------------------------------------------------------------------------
inline
Schedule::const_iterator Schedule::begin() const
{
    return allCourses.begin();
}

//-----------------------------------------------------------------------------
inline
Schedule::const_iterator Schedule::end() const
{
    return allCourses.end();
}

inline
size_t Schedule::size() const
{
    return allCourses.size();
}

//-----------------------------------------------------------------------------
inline
bool Schedule::isEmpty() const
{
    return this->allCourses.empty();
}

//-----------------------------------------------------------------------------
inline
Schedule* Schedule::clone() const
{
    return new Schedule(*this);
}

/**
 * Display a listing of each course and
 * the total number of credit hours
 */
std::ostream& operator<<(std::ostream &outs, const Schedule &prt);

#endif
