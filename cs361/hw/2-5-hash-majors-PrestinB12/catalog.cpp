#include "catalog.h"
#include "courseName.h"
#include <algorithm>
#include <iterator>
#include <sstream>
#include <vector>

using namespace std;
const CourseCatalog::CourseSet CourseCatalog::emptySet;

CourseCatalog::CourseCatalog()
{
  //nothing here, LOL thankfully
}

void CourseCatalog::read(istream &input)
{
  string line;
  getline(input, line);
  while (input)
  {
    istringstream in(line);
    string word;
    in >> word;
    CourseName c1 = parseCourseName(word);
    coursesOffered.insert(c1);
    while (in >> word)
    {
      CourseName c2 = parseCourseName(word);
      addCourses(c1, c2);
    }
    getline(input, line);
  }
}

/**
 * Adds a pair of courses to the catalog if they have not previously been
 * encountered, and records that one course is an immediate pre-requisite
 * of the other.
 *
 * @param course1  a course, possibly never seen before
 * @param prereqOfC1  another course that is an immediate pre-requisite
 *                    of this one.
 */
void CourseCatalog::addCourses(
    const CourseName &course1,
    const CourseName &prereqOfCourse1)
{
  coursesOffered.insert(course1);   //inserts the 2 courses into the map of the courses and prereqs
  coursesOffered.insert(prereqOfCourse1);
  prereqs[course1].insert(prereqOfCourse1);
}

/**
 * Remove a course from the catalog, including any
 * relationships in which it enables other courses.
 */
void CourseCatalog::removeCourse(const CourseName &c)
{
  coursesOffered.erase(c);  //calls the erase function for courses that are being offered
  for(auto &other: prereqs) //range based for-loop
  {
    other.second.erase(c);  //erases in each course "c" the prereqs
  }
  prereqs.erase(c); //erases prereqs from the course
}

/**
 * Fetch all known prerequisites of a given course.
 * @param cname a course name
 * @return a pair of iterators denoting a begin-end range of course names,
 *      each of which is an immediate prerequisite of cname.
 */
const std::unordered_set<CourseName> &  //adds the vector
CourseCatalog::getPrereqsOf(const CourseName &cname) const
{
  auto itr = prereqs.find(cname); //using the iterator (itr) to find the prereqs of the courses
  
  if(itr != prereqs.end()) 
  {
    return itr->second; //move the iterator to the next position
  }
  return emptySet;
}

bool CourseCatalog::containsCourse(const CourseName &cname) const
{
  return coursesOffered.count(cname) > 0; //checks if the course is there
}

CourseName CourseCatalog::parseCourseName(string combined)
{
  int i = 0;  //iterations start at 0
  while (combined[i] >= 'a')
    ++i;  //increment the count of the course names
  string dept = combined.substr(0, i);
  istringstream numIn(combined.substr(i));
  int num;
  numIn >> num;
  return CourseName(dept, num); //returns the course name with the matched string
}

std::ostream &operator<<(std::ostream &out, const CourseCatalog &cat)
{
  for (const CourseName &c : cat) //range based for-loop
  {
    out << c << endl; //outputs
  }
  return out;
}

bool CourseCatalog::operator==(const CourseCatalog &right) const
{
  return coursesOffered == right.coursesOffered && prereqs == right.prereqs;  //returns all courses
}