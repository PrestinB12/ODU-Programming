#include "catalog.h"
#include "unittest.h"
#include <sstream>
#include <algorithm>
#include <iterator>
#include <set>

using namespace std;

string toString(const CourseCatalog& cat) {
	ostringstream out;
	out << cat;
	return out.str();
}

UnitTest(CatalogConstructor) {
	CourseCatalog cat;
	assertThat (cat.end(), isEqualTo(cat.begin()));
}


bool hasPrereq (const CourseCatalog& cat,
		const CourseName& course, const CourseName& prereq)
{
	return cat.getPrereqsOf(course).count(prereq) > 0;
}

UnitTest(CatalogAddCourse) {
	CourseName cs150 ("CS", 150);
	CourseName cs250 ("CS", 250);
	CourseName cs361 ("CS", 361);
	CourseName cs330 ("CS", 330);
	CourseName cs350 ("CS", 350);

	CourseCatalog cat;
	cat.addCourses(cs250, cs150);
	assertThat (distance(cat.begin(), cat.end()), isEqualTo(2));
	assertTrue(cat.containsCourse(cs150));
	assertTrue(cat.containsCourse(cs250));
	assertFalse(cat.containsCourse(cs361));
	assertFalse(cat.containsCourse(cs330));
	assertFalse(cat.containsCourse(cs350));

	assertThat(distance(cat.begin(), cat.end()), isEqualTo(2));
	assertTrue(cat.containsCourse(cs150));
	assertTrue(cat.containsCourse(cs250));

	string out = toString(cat);
	assertThat (out, contains("CS150"));
	assertThat (out, contains("CS250"));

	cat.addCourses(cs350, cs361);
	assertThat (distance(cat.begin(), cat.end()), isEqualTo(4));
	assertTrue(cat.containsCourse(cs150));
	assertTrue(cat.containsCourse(cs250));
	assertTrue(cat.containsCourse(cs361));
	assertFalse(cat.containsCourse(cs330));
	assertTrue(cat.containsCourse(cs350));

	out = toString(cat);
	assertThat (out, contains("CS150"));
	assertThat (out, contains("CS250"));
	assertThat (out, contains("CS350"));
	assertThat (out, contains("CS361"));

	cat.addCourses(cs350, cs330);
	assertThat (distance(cat.begin(), cat.end()), isEqualTo(5));
	assertTrue(cat.containsCourse(cs150));
	assertTrue(cat.containsCourse(cs250));
	assertTrue(cat.containsCourse(cs361));
	assertTrue(cat.containsCourse(cs330));
	assertTrue(cat.containsCourse(cs350));

	cat.addCourses(cs330, cs250);
	assertThat (distance(cat.begin(), cat.end()), isEqualTo(5));
	assertTrue(cat.containsCourse(cs150));
	assertTrue(cat.containsCourse(cs250));
	assertTrue(cat.containsCourse(cs361));
	assertTrue(cat.containsCourse(cs330));
	assertTrue(cat.containsCourse(cs350));

	cat.addCourses(cs361, cs250);
	assertThat (distance(cat.begin(), cat.end()), isEqualTo(5));
	assertTrue(cat.containsCourse(cs150));
	assertTrue(cat.containsCourse(cs250));
	assertTrue(cat.containsCourse(cs361));
	assertTrue(cat.containsCourse(cs330));
	assertTrue(cat.containsCourse(cs350));


	auto pre = cat.getPrereqsOf(cs250);
    assertThat(pre.size(), isEqualTo(1));
    assertThat(pre.count(cs150), is(1));

    pre = cat.getPrereqsOf(cs350);
    assertThat(pre.size(), is(2));
    assertThat(pre.count(cs330), is(1));
    assertThat(pre.count(cs361), is(1));

    pre = cat.getPrereqsOf(cs150);
    assertThat(pre.size(), is(0));
}

UnitTest(CatalogRemoveCourse) {
	CourseName cs150 ("CS", 150);
	CourseName cs250 ("CS", 250);
	CourseName cs361 ("CS", 361);
	CourseName cs330 ("CS", 330);
	CourseName cs350 ("CS", 350);

	CourseCatalog cat;
	cat.addCourses(cs250, cs150);
	cat.addCourses(cs350, cs361);
	cat.addCourses(cs350, cs330);
	cat.addCourses(cs330, cs250);
	cat.addCourses(cs361, cs250);

	cat.removeCourse(cs330);

	assertThat (distance(cat.begin(), cat.end()), isEqualTo(4));
	assertTrue(cat.containsCourse(cs150));
	assertTrue(cat.containsCourse(cs250));
	assertTrue(cat.containsCourse(cs361));
	assertFalse(cat.containsCourse(cs330));
	assertTrue(cat.containsCourse(cs350));

    auto prereq350 = cat.getPrereqsOf(cs350);
    assertThat (prereq350.size(), isEqualTo(1));
    assertThat (prereq350.count(cs361), is(1));
}

UnitTest(CatalogCopy) {
	CourseName cs150 ("CS", 150);
	CourseName cs250 ("CS", 250);
	CourseName cs361 ("CS", 361);
	CourseName cs330 ("CS", 330);
	CourseName cs350 ("CS", 350);

	CourseCatalog cat;
	cat.addCourses(cs250, cs150);
	cat.addCourses(cs350, cs361);
	cat.addCourses(cs350, cs330);
	cat.addCourses(cs330, cs250);
	cat.addCourses(cs361, cs250);

	CourseCatalog cat2 (cat);

	assertThat(cat2, isEqualTo(cat));

	cat.removeCourse(cs330);

	assertThat(cat2, isNotEqualTo(cat));

	assertThat (distance(cat2.begin(), cat2.end()), isEqualTo(5));
	assertTrue(cat2.containsCourse(cs150));
	assertTrue(cat2.containsCourse(cs250));
	assertTrue(cat2.containsCourse(cs361));
	assertTrue(cat2.containsCourse(cs330));
	assertTrue(cat2.containsCourse(cs350));

    auto pre = cat.getPrereqsOf(cs350);
    assertThat(pre.size(), isEqualTo(1));
    assertThat(pre.count(cs330), is(0));
    assertThat(pre.count(cs361), is(1));
}



UnitTest(CatalogAssign) {
	CourseName cs150 ("CS", 150);
	CourseName cs250 ("CS", 250);
	CourseName cs361 ("CS", 361);
	CourseName cs330 ("CS", 330);
	CourseName cs350 ("CS", 350);

	CourseCatalog cat;
	cat.addCourses(cs250, cs150);
	cat.addCourses(cs350, cs361);
	cat.addCourses(cs350, cs330);
	cat.addCourses(cs330, cs250);
	cat.addCourses(cs361, cs250);

	CourseCatalog cat2;

	CourseCatalog cat3 (cat2 = cat);

	assertThat(cat2, isEqualTo(cat));
	assertThat(cat3, isEqualTo(cat));

	cat.removeCourse(cs330);

	assertThat(cat2, isNotEqualTo(cat));

	assertThat (distance(cat2.begin(), cat2.end()), isEqualTo(5));
	assertTrue(cat2.containsCourse(cs150));
	assertTrue(cat2.containsCourse(cs250));
	assertTrue(cat2.containsCourse(cs361));
	assertTrue(cat2.containsCourse(cs330));
	assertTrue(cat2.containsCourse(cs350));

    auto pre = cat.getPrereqsOf(cs350);
    assertThat(pre.size(), is(1));
    assertThat(pre.count(cs330), is(0));
    assertThat(pre.count(cs361), is(1));
}





UnitTest(CatalogRead) {
	CourseName cs100 ("cs", 100);
	CourseName cs150 ("cs", 150);
	CourseName cs200 ("cs", 200);
	CourseName cs300 ("cs", 300);

	string testIn =
			string("cs100\n") +
			"cs200 cs100\n" +
			"cs300 cs200 cs100\n";
	istringstream in (testIn);
	CourseCatalog cat;
	cat.read(in);

	assertTrue (cat.containsCourse(cs100));
	assertTrue (cat.containsCourse(cs200));
	assertTrue (cat.containsCourse(cs300));
	assertFalse (cat.containsCourse(cs150));

	auto prereqs100 = cat.getPrereqsOf(cs100);
    assertThat(prereqs100.size(), isEqualTo(0));
	auto prereqs200 = cat.getPrereqsOf(cs200);
    assertThat(prereqs200.size(), isEqualTo(1));
	auto prereqs300 = cat.getPrereqsOf(cs300);
    assertThat(prereqs300.size(), isEqualTo(2));

}




