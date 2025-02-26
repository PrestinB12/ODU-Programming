#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <algorithm>
#include <functional>

#include "bodgeUnitTest.h"

#include "Course.h"
#include "Student.h"
#include "Schedule.h"


//-----------------------------------------------------------------------------
// Schedule Unit Tests
//-----------------------------------------------------------------------------
const std::vector<Course> COURSES = {
    {"CS121", 34599, 4},
    {"CS300", 34567, 3},
    {"CS300", 34567, 3},
    {"CS300", 34567, 3},
    {"CS330", 12345, 3},
    {"CS330", 12749, 3},
    {"CS330", 23456, 3},
    {"CS355", 45678, 3},
    {"CS355", 45678, 3},
    {"CS361", 34569, 3},
    {"IT310", 78192, 3},
    {"Stat330", 78195, 3}
};

bool testAppendNoCheck()
{
    Schedule s;
    s.add(COURSES[0]);

    Schedule::const_iterator it = s.begin();

    // The iterator should reference a copy of course[0]
    // i.e., the first course added.
    bodgeAssert((*it) == COURSES[0]);

    // Add two more COURSES
    s.add(COURSES[1]);
    s.add(COURSES[4]);

    it = s.begin();

    // COURSES 0, 1 and 4 should have been added
    // to the Schedule, s
    bodgeAssert((*it) == COURSES[0]);
    bodgeAssert(*(++it) == COURSES[1]);
    bodgeAssert(*(++it) == COURSES[5]);

    return true;
}

bool testGetCredits()
{
    Schedule s;
    s.add(COURSES[0]);

    // course[0] is worth 4 credit-hours
    bodgeAssert(s.getCredits() == 4);

    // Add two more COURSES (3 credit-hours each)
    s.add(COURSES[1]);
    s.add(COURSES[4]);

    bodgeAssert(s.getCredits() == 10);

    return true;
}

bool testWouldExceedCreditLimit()
{
    Schedule s;
    s.add(COURSES[0]);

    Schedule::const_iterator it = s.begin();

    bodgeAssert((*it) == COURSES[0]);

    // Add two more COURSES
    s.add(COURSES[1]);
    s.add(COURSES[4]);

    it = s.begin();

    // COURSES 0, 1 and 4 should have been added
    // to the Schedule, s
    bodgeAssert((*it) == COURSES[0]);
    bodgeAssert(*(++it) == COURSES[1]);
    bodgeAssert(*(++it) == COURSES[4]);

    return true;
}

bool testAlreadyInSchedule()
{
    Schedule s;

    for (int i = 0; i < 6; i++) {
        s.add(COURSES[i]);
    }

    // Test that only COURSES 0, 1, and 4 were added
    bodgeAssert(s.size() == 3);

    Schedule::const_iterator it = s.begin();

    bodgeAssert((*it) == COURSES[0]);
    bodgeAssert(*(++it) == COURSES[1]);
    bodgeAssert(*(++it) == COURSES[4]);

    return true;
}
//-----------------------------------------------------------------------------
bool testOutputWithOneCourse()
{
    Schedule s;
    s.add(COURSES[5]);

    std::ostringstream outs;
    outs << s;

    /**
     * Output should be:
     *  - 3 credits - CS330 (CRN 12345)
     *  (3 Total Credits)
     */
    const std::string expectedOutput = R"(  - 3 credits - CS330 (CRN 12749)
  (3 Total Credits)
)";

    bodgeAssert(expectedOutput == outs.str());

    return true;
}

//------------------------------------------------------------------------------
// Student Unit Tests
//------------------------------------------------------------------------------
bool testDefaultConstructor()
{
    Student aStu;

    bodgeAssert(aStu.getName() == "ERROR");

    bodgeAssert(aStu.getSchedule() != nullptr);
    bodgeAssert(aStu.getSchedule()->isEmpty());

    return true;
}

bool testNameArgConstructor()
{
    Student aStu("Thomas");

    bodgeAssert(aStu.getName() == "Thomas");

    bodgeAssert(aStu.getSchedule() != nullptr);
    bodgeAssert(aStu.getSchedule()->isEmpty());

    return true;
}

bool testCopyConstructor()
{
    //--------------------------------------------------------------------------
    // Copy a student with an empty schedule
    //--------------------------------------------------------------------------
    Student stu1("John Smith");
    Student stu2(stu1);

    // Technically the next two lines are equivalent since the Student `==`
    // operator only compares names.
    bodgeAssert(stu1 == stu2);
    bodgeAssert(stu1.getName() == stu2.getName());

    // Check we have two distinct students
    bodgeAssert(&stu1 != &stu2);

    //--------------------------------------------------------------------------
    // Copy a student with a non-empty schedule
    //--------------------------------------------------------------------------
    stu1.enrollIn(COURSES[0]);
    stu1.enrollIn(COURSES[3]);
    stu1.enrollIn(COURSES[5]);

    Student stu3(stu1);

    bodgeAssert(stu1.getName() == stu2.getName());

    // Compare schedules
    bodgeAssert(stu1.getSchedule()->size() == stu3.getSchedule()->size())

    Schedule::const_iterator stu1It = stu1.getSchedule()->begin();
    Schedule::const_iterator stu3It = stu3.getSchedule()->begin();

    bodgeAssert(*stu1It == *stu3It);
    bodgeAssert(&(*stu1It) != &(*stu3It));
    ++stu1It;
    ++stu3It;

    bodgeAssert(*stu1It == *stu3It);
    bodgeAssert(&(*stu1It) != &(*stu3It));
    ++stu1It;
    ++stu3It;

    bodgeAssert(*stu1It == *stu3It);
    bodgeAssert(&(*stu1It) != &(*stu3It));

    return true;
}

bool testAssignmentOp()
{
    //--------------------------------------------------------------------------
    // Copy a student with an empty schedule
    //--------------------------------------------------------------------------
    Student lhs("John Smith");
    Student rhs1 = lhs;

    // Technically the next two lines are equivalent since the Student `==`
    // operator only compares names.
    bodgeAssert(lhs == rhs1);
    bodgeAssert(lhs.getName() == rhs1.getName());

    // Check we have two distinct students
    bodgeAssert(&lhs != &rhs1);

    //--------------------------------------------------------------------------
    // Copy a student with a non-empty schedule
    //--------------------------------------------------------------------------
    lhs.enrollIn(COURSES[0]);
    lhs.enrollIn(COURSES[3]);
    lhs.enrollIn(COURSES[5]);

    Student rhs2 = lhs;

    bodgeAssert(lhs.getName() == rhs1.getName());

    // Compare schedules
    bodgeAssert(lhs.getSchedule()->size() == rhs2.getSchedule()->size())

    Schedule::const_iterator lhsIt = lhs.getSchedule()->begin();
    Schedule::const_iterator rhs2It = rhs2.getSchedule()->begin();

    bodgeAssert(*lhsIt == *rhs2It);
    bodgeAssert(&(*lhsIt) != &(*rhs2It));
    ++lhsIt;
    ++rhs2It;

    bodgeAssert(*lhsIt == *rhs2It);
    bodgeAssert(&(*lhsIt) != &(*rhs2It));
    ++lhsIt;
    ++rhs2It;

    bodgeAssert(*lhsIt == *rhs2It);
    bodgeAssert(&(*lhsIt) != &(*rhs2It));

    return true;
}

bool testSwap()
{
    Student lhs("John Smith");
    lhs.enrollIn(COURSES[0]);
    lhs.enrollIn(COURSES[3]);
    lhs.enrollIn(COURSES[5]);

    Student rhs("Robert Jones");

    const std::string lhsStartName = lhs.getName();
    const Schedule* lhsStartSchedule = lhs.getSchedule();

    std::string rhsStartName = rhs.getName();
    const Schedule* rhsStartSchedule = rhs.getSchedule();

    // Perform the swap
    swap(lhs, rhs);

    // Check that the names were swapped
    bodgeAssert(lhs.getName() == rhsStartName);
    bodgeAssert(rhs.getName() == lhsStartName);

    // Check that the schedules were swapped
    bodgeAssert(lhs.getSchedule() == rhsStartSchedule);
    bodgeAssert(rhs.getSchedule() == lhsStartSchedule);

    return true;
}

bool testDisplay()
{
    Student stu("John Smith");
    stu.enrollIn(COURSES[0]);
    stu.enrollIn(COURSES[3]);
    stu.enrollIn(COURSES[5]);

    // Since Schedule::display was already tested... we can use it here.
    std::ostringstream outsExpected;
    outsExpected << " John Smith" << '\n';
    outsExpected << *stu.getSchedule();

    const std::string expectedOutput = outsExpected.str();

    std::ostringstream outsActual;
    outsActual << stu;

    const std::string actualOutput = outsActual.str();

    bodgeAssert(expectedOutput == actualOutput);

    return true;
}

//-----------------------------------------------------------------------------
int main(int argc, char** argv)
{
    UnitTestPair scheduleTests[] = {
        {testAppendNoCheck, "testAppendNoCheck"},
        {testGetCredits, "testGetCredits"},
        {testWouldExceedCreditLimit, "testWouldExceedCreditLimit"},
        {testAlreadyInSchedule, "testAlreadyInSchedule"},
        {testOutputWithOneCourse, "testOutputWithOneCourse"}
    };

    std::cout << "Schedule Tests:\n";
    for (const UnitTestPair& testPair : scheduleTests) {
        runTest(testPair.first, testPair.second);
    }

    UnitTestPair studentTests[] = {
        {testDefaultConstructor, "testDefaultConstructor"},
        {testNameArgConstructor, "testNameArgConstructor"},
        {testCopyConstructor, "testCopyConstructor"},
        {testAssignmentOp, "testAssignmentOp"},
        {testSwap, "testSwap"},
        {testDisplay, "testDisplay"}
    };

    std::cout << "\n";
    std::cout << "Student Tests:\n";
    for (const UnitTestPair& testPair : studentTests) {
        runTest(testPair.first, testPair.second);
    }

    return 0;
}

