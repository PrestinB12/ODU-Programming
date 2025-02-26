#include "itinerary.h"
#include "unittest.h"
#include <vector>
#include <algorithm>

using namespace std;

Leg norHam {"Norfolk", "Hampton", "I64", 17.0};
Leg hamRich {"Hampton", "Richmond", "I64", 77.0};
Leg dcRich {"D.C.", "Richmond", "US-301", 121.2};
Leg dcArlington {"D.C.", "Arlington", "K St NW", 5.3};

UnitTest(OneRoad) {

	Itinerary itinerary;
	itinerary.addRoad(norHam);
	itinerary.addRoad(hamRich);

	Leg leg1 {"Norfolk", "Hampton", "I64", 17.0};
	Leg leg2 {"Norfolk", "Richmond", "I64", 94.0};
	Leg leg2R {"Richmond", "Norfolk", "I64", 94.0};


	vector<Leg> expected1 {leg1};
	auto path1 = itinerary.travelPlan("Norfolk", "Hampton");
	assertThat(path1, is(expected1));
	assertThat(itinerary.getLastTripLength(), isApproximately(17.0, .1));

	vector<Leg> expected2 {leg2};
	auto path2 = itinerary.travelPlan("Norfolk", "Richmond");
	assertThat(path2, is(expected2));
	assertThat(itinerary.getLastTripLength(), isApproximately(94.0, .1));

	vector<Leg> expected3 {leg2R};
	auto path3 = itinerary.travelPlan("Richmond", "Norfolk");
	assertThat(path3, is(expected3));
	assertThat(itinerary.getLastTripLength(), isApproximately(94.0, .1));

}

UnitTest(TwoRoads) {
	
	Itinerary itinerary;
	itinerary.addRoad(norHam);
	itinerary.addRoad(hamRich);
	itinerary.addRoad(dcRich);

	Leg leg1 {"Norfolk", "Richmond", "I64", 94.0};
	Leg leg2 {"Richmond", "D.C.", "US-301", 121.2};

	vector<Leg> expected1 {leg1, leg2};
	auto path1 = itinerary.travelPlan("Norfolk", "D.C.");
	assertThat(path1, is(expected1));
	assertThat(itinerary.getLastTripLength(), isApproximately(215.2, .1));

}

UnitTest(Disconnected) {
	Itinerary itinerary;
	itinerary.addRoad(norHam);
	itinerary.addRoad(hamRich);
	itinerary.addRoad(dcArlington);

	vector<Leg> expected1;
	auto path1 = itinerary.travelPlan("Norfolk", "D.C.");
	assertThat(path1, is(expected1));

}



UnitTest(NoTrip) {
	Itinerary itinerary;
	itinerary.addRoad(norHam);
	itinerary.addRoad(hamRich);
	itinerary.addRoad(dcRich);


	vector<Leg> expected1;
	auto path1 = itinerary.travelPlan("Richmond", "Richmond");
	assertThat(path1, is(expected1));
	assertThat(itinerary.getLastTripLength(), isApproximately(0.0, .1));

}

