#ifndef INVENTORY_H_INCLUDED
#define INVENTORY_H_INCLUDED

#include <iostream>

#include "Course.h"
#include "Schedule.h"

#include "utilities.h"

/**
 * A Student has a name and a schedule.
 * <p>
 * For simplicity, we will assume no two students
 * share the same name. We will forgo a more
 * formal student id.
 */
class Student {
    private:
       /**
        * Full name (first and last)
        */
       std::string name;

       /**
        * Schedule containing all selected courses.
        *
        * Note `schedule` is now a pointer.
        */
       Schedule*   schedule;

    public:
        /**
         * Default to a student with
         * the name ERROR
         */
        Student();

        /**
         * Create a student with a specified name
         *
         * @param n desired name
         */
        Student(std::string n);

        /**
         * Copy an existing student's name and schedule.
         *
         * @param src existing student to duplicate
         */
        Student(const Student& src);

        /**
         * Make sure to deallocate the schedule
         */
        ~Student();

        /**
         * Overload the assignment operator (using the copy-and-swap idiom)
         */
        Student& operator=(Student rhs);

        friend
        void swap(Student& lhs, Student& rhs);

        /**
         * Change the name.
         *
         * @param n new name
         */
        void setName(std::string n);

        /**
         * Retrieve the name attribute
         */
        std::string getName() const;

        /**
         * Retrieve a pointer to the schedule
         */
        const Schedule* getSchedule() const;

        /**
         * Attempt to enroll in a course.
         *
         * @return true if the course was successfully added to
         *      the student schedule and false otherwise
         */
        bool enrollIn(const Course &toAdd);

        /**
         * Print a Summary of the Student and his/her schedule
         */
        void display(std::ostream &outs) const;

        /**
         * Logical Equivalence Operator
         */
        bool operator==(const Student& rhs) const;

        /**
         * Less-Than (Comes-Before) Operator
         */
        bool operator<(const Student& rhs) const;
};

//------------------------------------------------------------------------------
inline
void Student::setName(std::string n)
{
    this->name = n;
}

//------------------------------------------------------------------------------
inline
std::string Student::getName() const
{
    return name;
}

//------------------------------------------------------------------------------
inline
const Schedule* Student::getSchedule() const
{
    return schedule;
}

//------------------------------------------------------------------------------
inline
Student& Student::operator=(Student rhs)
{
    swap(*this, rhs);

    return *this;
}

//------------------------------------------------------------------------------
inline
bool Student::operator==(const Student& rhs) const
{
    return this->name == rhs.name;
}

//------------------------------------------------------------------------------
inline
bool Student::operator<(const Student& rhs) const
{
    return this->name < rhs.name;
}

//------------------------------------------------------------------------------
/**
 * Print the Student through use of the display member function
 */
inline
std::ostream& operator<<(std::ostream &outs, const Student &prt)
{
    prt.display(outs);

    return outs;
}

//------------------------------------------------------------------------------
/**
 * Read in a new Student
 */
inline
std::istream& operator>>(std::istream& ins, Student& rd)
{
    std::string nextName;

    getline(ins, nextName);
    trim(nextName);

    rd.setName(nextName);

    return ins;
}


#endif
