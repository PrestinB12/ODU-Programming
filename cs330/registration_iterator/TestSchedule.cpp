#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <algorithm>
#include <functional>

#include "Course.h"
#include "Student.h"
#include "Schedule.h"

/**
 * This is the Bodge-Unit-Testing... PseUdO-Framework
 *
 * Bodge - A clumsy or inelegant job, usually a temporary repair;
 * a patch, a repair. (From Wiktionary)
 */

#define bodgeAssert(expression) \
if (!(expression)) { \
    std::cout << " FAILURE: "\
              << __func__ << ":" << __LINE__\
              << " -> (" << #expression << ")\n";\
    return false;\
}
// End Macro

// Unit Test Pseudo-Framework
//-----------------------------------------------------------------------------
using UnitTestFunction = std::function<bool()>;
using UnitTestPair = std::pair<UnitTestFunction, const std::string>;

void runTest(const UnitTestFunction& testFunction, const std::string& description)
{
    std::cout << (testFunction() ? "PASSED" : "FAILED")
              << "->" << description
              << std::endl;
}
//-----------------------------------------------------------------------------

// Unit Tests
//-----------------------------------------------------------------------------
const std::vector<Course> COURSES = {
    Course("CS121", 34599, 4),
    Course("CS300", 34567, 3),
    Course("CS300", 34567, 3),
    Course("CS300", 34567, 3),
    Course("CS330", 12345, 3),
    Course("CS330", 12345, 3),
    Course("CS330", 23456, 3),
    Course("CS355", 45678, 3),
    Course("CS355", 45678, 3),
    Course("CS361", 34569, 3),
    Course("IT310", 78192, 3),
    Course("Stat330", 78195, 3)
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
    const std::string expectedOutput = R"(  - 3 credits - CS330 (CRN 12345)
  (3 Total Credits)
)";

    bodgeAssert(expectedOutput == outs.str());

    return true;
}

//-----------------------------------------------------------------------------
int main(int argc, char** argv)
{
    UnitTestPair tests[] = {
        {testAppendNoCheck, "testAppendNoCheck"},
        {testGetCredits, "testGetCredits"},
        {testWouldExceedCreditLimit, "testWouldExceedCreditLimit"},
        {testAlreadyInSchedule, "testAlreadyInSchedule"},
        {testOutputWithOneCourse, "testOutputWithOneCourse"}
    };

    for (const UnitTestPair& testPair : tests) {
        runTest(testPair.first, testPair.second);
    }

    return 0;
}

