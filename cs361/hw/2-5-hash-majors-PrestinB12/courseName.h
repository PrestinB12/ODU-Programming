#ifndef COURSENAME_H
#define COURSENAME_H
#include <iostream>
#include <string>
#include <functional>
#include <cstddef>

using namespace std;

struct CourseName
{
	std::string dept;
	int num;

	CourseName();
	CourseName(std::string theDept, int theNum);

	bool operator==(const CourseName &right) const;
	bool operator<(const CourseName &right) const;

	std::size_t operator()(const CourseName &cn) const
	{
		std::hash<std::string> str_hash;
		return str_hash(cn.dept);
	}
};

std::ostream &operator<<(std::ostream &out, const CourseName &c);

//*** Your code here
namespace std
{
	template < >	//creates the template for the hashing
	struct hash<CourseName>
	{
		std::size_t operator()(const CourseName &cn) const
		{
			std::hash<std::string> str_hash;	//hashing vector
			return str_hash(cn.dept);
		}
	};
}

#endif