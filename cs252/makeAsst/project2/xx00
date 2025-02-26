#include <cstdlib>
#include <sys/types.h>
#include <ctime>
#include <iostream>
#include <string>







// Check a proposed move to see if it is legal.
// A legal move must bite at least one remaining crumb.
bool biteIsLegal (int column, int row);


bool computerPlayerCanForceAWin (int& column, int& row,
				 int maxColumns, int lastNonEmptyRow);

bool computerPlayerMustLose (int& column, int& row,
			     int maxColumns, int lastNonEmptyRow);

// Display the cookie on the indicated output stream
void displayCookie(std::ostream& output);


// Check to see if the current game has been ended
// (i.e., has someone eaten the poison crumb?)
bool gameEnded();

// Get the human player's next move.
void getMoveByHumanPlayer (int& column, int& row);


// One time initialization of all data related to the computer player
void initializeComputerPlayer();


// One time initialization of all data related to the human player
void initializeHumanPlayer();

bool isADangerousMove (int column, int row);


void printRules();

void printScore();

// Get the computer player's next move.
void getMoveByComputerPlayer (int& column, int& row);

// Start a new game with a cookie of random size
void startAGame();


// Remove the crumb at the indicated position and
// all crumbs below and to the right of that position.
void takeABite (int column, int row);


void playAGame();

