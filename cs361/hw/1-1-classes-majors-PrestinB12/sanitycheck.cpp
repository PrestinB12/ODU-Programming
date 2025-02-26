#include "course.h"

int Course::sanityCheck() {
    CourseName cn = name;
    int k = numberOfPrerequisites;
    int m = maxPrerequisites;
    CourseName* p = prereqs;
    return k + m + ((p == 0) ? 0 : 1) + cn.num;
}