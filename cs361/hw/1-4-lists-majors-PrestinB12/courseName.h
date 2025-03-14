#ifndef COURSENAME_H
#define COURSENAME_H

#include <iostream>
#include <string>

using namespace std;

struct CourseName {
	std::string dept;
	int num;


	CourseName();

	CourseName (std::string theDept, int theNum);

	bool operator== (const CourseName& right) const;
	bool operator< (const CourseName& right) const;
};

std::ostream& operator<< (std::ostream& out, const CourseName& c);



#endif
