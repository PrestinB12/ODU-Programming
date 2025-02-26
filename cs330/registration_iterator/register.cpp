#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <iterator>

#include "utilities.h"
#include "Course.h"
#include "Student.h"

using namespace std;

using StudentList = vector<Student>;

/**
 * 60 Dash dividing line
 */
const std::string DASH_DIVIDER(60, '-');

/**
 * Parse a list of student names
 *
 * @return list of Student objects
 */
StudentList readStudentList(std::istream& ins);

/**
 * Process an enrollment requests file. For each request,
 * lookup the student and attempt to add a selected course
 * to hist/her schedule.
 */
void processEnrollmentRequests(std::istream& ins, StudentList& students);

/**
 * Print the names of all students
 */
void writeStudentNames(std::ostream& outs, const StudentList& students);

/**
 * Print each student along with his/her full schedule
 */
void writeStudentSchedules(std::ostream& outs, const StudentList& students);

/**
 * Assignment 1: Course Registration
 *
 * @param argv[1] Student List filename
 * @param argv[2] Enrollment Requests filename
 */
int main(int argc, char** argv)
{
    // Check Command Line Arguments
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " student_file request_file" << "\n";
        return 1;
    }

    // Open student file
    ifstream studentFile(argv[1]);
    if (!studentFile) {
        cerr << "Error: " << argv[1] << " could not be opened" << "\n";
        return 2;
    }

    // Open request file
    ifstream requestsFile(argv[2]);
    if (!requestsFile) {
        cerr << "Error: " << argv[2] << " could not be opened" << "\n";
        return 3;
    }

    StudentList students = readStudentList(studentFile);
    writeStudentNames(cout, students);

    processEnrollmentRequests(requestsFile, students);
    writeStudentSchedules(cout, students);

    return 0;
}

//------------------------------------------------------------------------------
StudentList readStudentList(std::istream& ins)
{
    StudentList students;

    std::istream_iterator<Student> ins_it(ins);
    std::istream_iterator<Student> ins_end;
    std::copy(ins_it, ins_end, back_inserter(students));

    return students;
}

//------------------------------------------------------------------------------
void writeStudentNames(std::ostream& outs, const StudentList& students)
{
    outs << "\n"
         << "Student List" << "\n"
         << DASH_DIVIDER   << "\n";

    for (const Student& student : students) {
        outs << " " << student.getName() << "\n";
    }
}

//------------------------------------------------------------------------------
void processEnrollmentRequests(std::istream& ins, StudentList& students)
{
    std::string studentName;

    cout << "\n"
         << "Enrollment Request Log" << "\n"
         << DASH_DIVIDER             << "\n";

    ins >> ws;
    while (getline(ins, studentName, ';')) {
        Course nextCourse;

        ins >> ws >> nextCourse;

        StudentList::iterator it;
        it = find_if(students.begin(),
                     students.end(),
                     [&studentName](const Student& rhs) -> bool {
                         return rhs.getName() == studentName;
                     });

        if (it != students.end()) {
            const bool success = it->enrollIn(nextCourse);

            // const std::string resultStr = (success ? "WAS" : "WAS NOT");
            const char* resultStr = (success ? "WAS" : "WAS NOT");

            cout << left << setw(15)
                 << it->getName() << " "
                 << setw(7)
                 << resultStr     << " enrolled in "
                 << nextCourse.getNumber()  << "\n";
        }

        ins >> ws;
    }
}

//------------------------------------------------------------------------------
void writeStudentSchedules(std::ostream& outs, const StudentList& students)
{
    outs << "\n"
         << "Student Schedule Report"  << "\n"
         << DASH_DIVIDER               << "\n";

    std::ostream_iterator<Student> outs_it(outs, "\n");
    std::copy(students.begin(), students.end(), outs_it);
}
