#ifndef SCHEDULE_H_INCLUDED
#define SCHEDULE_H_INCLUDED

#include <iostream>

#include "Course.h"

#define CREDIT_LIMIT 12

/**
 * A Schedule contains a single set of course enrollements.
 *
 * If implemented correctly, it should be impossible for any `Schedule` to have:
 *   1. total credits exceeding the CREDIT_LIMIT.
 *   2. two courses that share the same course number.
 */
class Schedule {
    private:
        /**
         * The atom of a Linked List
         */
        struct Node {
            Course data;
            Node*  next;

            /**
             * Construct a node that contains
             * a given room, with next set to null
             */
            Node(Course c);
        };

        /**
         * Beginning of the linked list
         */
        Node* head;

        /**
         * End of the linked list
         */
        Node* tail;

        /**
         * Total number of credits.
         *
         * **Hint:** This is not the number of courses. It is the overall
         * (i.e., cumulative number of credit-hours).
         */
        int totalCredits;

        /**
         * Add a course the schedule. This is a standard
         * linked list append.
         *
         * @pre (!wouldViolateCreditLimit && notAlreadyInSchedule)
         */
        void appendNoCheck(Course course);

    public:
        /**
         * Construct an empty schedule
         */
        Schedule();

        /**
         * Copy Constructor
         */
        Schedule(const Schedule& src);

        /**
         * Destructor
         */
        ~Schedule();

        /**
         * Retrieve the total number of credits
         */
        int getCredits() const;

        /**
         * Attempt to add a course AND
         * perform all validation checks by calling:
         *   - wouldViolateCreditLimit
         *   - alreadyInSchedule
         *   - appendNoCheck
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
         * @returns true if while traversing the linked list
         *   of courses, a course with the same course number
         *   was found
         */
        bool alreadyInSchedule(Course course) const;

        /**
         * Display a listing of each course and
         * the total number of credit hours
         */
        void display(std::ostream& outs) const;

        /**
         * Assignment Operator
         */
        Schedule& operator=(Schedule rhs);


        /**
         * Let us use the Copy-and-Swap idiom discussed in the Review 01
         * Example Set.
         */
        friend
        void swap(Schedule& lhs, Schedule& rhs);
};

//------------------------------------------------------------------------------
inline
int Schedule::getCredits() const
{
    return totalCredits;
}

//------------------------------------------------------------------------------
inline
bool Schedule::add(Course course)
{
    if (wouldViolateCreditLimit(course)) {
        return false;
    }

    if (alreadyInSchedule(course)) {
        return false;
    }

    // Success - all checks passed
    appendNoCheck(course);
    return true;
}

/**
 * Print the Schedule through use of the display member function
 */
inline
std::ostream& operator<<(std::ostream &outs, const Schedule &prt)
{
    prt.display(outs);

    return outs;
}

//------------------------------------------------------------------------------
inline
void swap(Schedule& lhs, Schedule& rhs)
{
    using std::swap;

    swap(lhs.head, rhs.head);
    swap(lhs.tail, rhs.tail);
    swap(lhs.totalCredits, rhs.totalCredits);
}
#endif
