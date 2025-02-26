//    Split Here


#include "cookie.h"

using namespace std;


// The "cookie" is represented as an array of int.
// Each element describes a row of the cookie.
//   -- If cookie[i] == j, that means that there are
//        j columns left in row i of the cookie


const int MAXROWS = 10;

// Number of rows currently remaining in the cookie
int numberOfRows;

// Number of columns currently remaining in the cookie
int numberOfColumns;

// The cookie.  If cookie[i] == j, then the cookie currently
// has crumbs filling the j columns at row i
int cookie[MAXROWS];
int initialNumberOfRows;




string humanPlayerName;
int nGamesWonByComputerPlayer;
int nGamesWonByHumanPlayer;





// Check a proposed move to see if it is legal.
// A legal move must bite at least one remaining crumb.
bool biteIsLegal (int column, int row)
{
  return (column >= 0) && (row >= 0) && row < numberOfRows
    && (column < cookie[row]);
}






bool computerPlayerCanForceAWin (int& column, int& row,
				 int maxColumns, int lastNonEmptyRow)
{
  // We can force a win if there is only one row and that has 
  //   more than one column
  if (numberOfRows == 1 && cookie[0] > 1)
    {
      column = 1;
      row = 0;
      return true;
    }
  // Or if there is only one column and that has more than one row
  if (numberOfColumns == 1 && numberOfRows > 1)
    {
      column = 0;
      row = 1;
      return true;
    }



  // If row 0 is the only row with more than 1 column, and
  // column 0 is the only column with more than 1 row, and the number of
  // elements in each are different, then we can force an eventual win
  // by evening them up.
  if (numberOfRows != numberOfColumns &&
      numberOfRows > 1 &&
      numberOfColumns > 1 &&
      cookie[1] == 1)
    {
      if (numberOfRows > numberOfColumns)
	{
	  column = 0;
	  row = numberOfColumns;
	}
      else 
	{
	  row = 0;
	  column = numberOfRows;
	}
      return true;
    }





  // More subtly, if we are down to two rows and the number of columns
  //   in each is different, we can force an eventual win by evening them
  //   up.
  if (numberOfRows == 2 && cookie[0] != cookie[1])
    {
      row = 0;
      column = cookie[1];
      return true;
    }
  // Or, if we are down to two columns and the number of rows
  //   in each is different, we can force an eventual win by evening them
  //   up.
  if (numberOfColumns == 2 && cookie[numberOfRows-1] == 1)
    {
      column = 0;
      row = 1;
      while (cookie[row] == 2)
	++row;
      return true;
    }


  // If none of those are true, no obvious way to force a win
  return false;
}


bool computerPlayerMustLose (int& column, int& row,
			     int maxColumns, int lastNonEmptyRow)
{
  if (cookie[0] == 1 && cookie[1] == 0)
    {
      // We have to bite the poison crumb.
      column = row = 0;
      return true;
    }
  return false;
}




// Display the cookie on the indicated output stream
void displayCookie(std::ostream& output)
{
  //** Insert your code here
}




// Check to see if the current game has been ended
// (i.e., has someone eaten the poisin crumb?)
bool gameEnded()
{
  return cookie[0] <= 0;
}







// Get the human player's next move.
void getMoveByHumanPlayer (int& column, int& row)
{
  cout << "Your turn to take a bite from the cookie.\n";
  cout << "Enter the column number and row number at which\n";
  cout << "  you wish to chomp (separated by a blank space): " << flush;
  cin >> column >> row;
  if (cin.fail()) {
    cin.clear();
    std::string junk;
    getline(cin, junk); // discard rest of this input line
  }
}





// One time initialization of all data related to the computer player
void initializeComputerPlayer()
{
  nGamesWonByComputerPlayer = 0;
}



// One time initialization of all data related to the human player
void initializeHumanPlayer()
{
  nGamesWonByHumanPlayer = 0;
  cout << "Welcome to Chomp!\n"
       << "What is your name? "
       << flush;
  getline (cin, humanPlayerName);

  cout << "OK, " << humanPlayerName << ", let's play." << endl;
}



bool isADangerousMove (int column, int row)
{
  // Always dangerous to eat the poison crumb
  if (column == 0 && row == 0)
    return true;

  // Dangerous to leave only one row or one column unless
  // it has only one element (the poison)
  if (column == 0 && row > 1)
    return true;
  if (row == 0 && column > 1)
    return true;

  // Dangerous to take element (1,1) if the #rows and #cols are equal
  if (row == 1 && column == 1 && numberOfRows == numberOfColumns)
    return true;

  // Dangerous to take element (2,0) if the th remaining two rows
  //   are equal length
  if (row == 2 && column == 0 && cookie[0] == cookie[1])
    return true;

  // Dangerous to take element (2,0) if the the remaining two cols
  //   are equal length
  if (row == 0 && column == 2 && cookie[numberOfRows-1] > 1)
    return true;

  return false;
}





void printRules()
{
  cout << "Chomp is a game played with a rectangular \"cookie\" made\n"
       << "up of square \"crumbs\".\n\n";
  cout << "Taking turns, each player takes a bite from the cookie,\n"
       << "selecting a crumb that is removed from the cookie, together\n"
       << "with all crumbs below and to the right of the selected one.\n\n";
  cout << "The top-left crumb in this cookie is poisoned. The player\n"
       << "who eats the poisoned crumb loses the game.\n" << endl;

}



void printScore()
{
  cout << "Score\tComputer: " << nGamesWonByComputerPlayer
       << "\t" << humanPlayerName << ": " << nGamesWonByHumanPlayer
       << endl;
}


// Get the computer player's next move.
void getMoveByComputerPlayer (int& column, int& row)
{
  // Collect some basic info about the shape of the cookie
  int maxColumns = cookie[0];
  int lastNonEmptyRow = -1;
  for (int r = 0; r < numberOfRows; ++r)
    {
      if (cookie[r] > maxColumns)
	maxColumns = cookie[r];
      if (cookie[r] > 0)
	lastNonEmptyRow = r;
    }

  // If we can force a win, do it.
  if (computerPlayerCanForceAWin(column, row, maxColumns, lastNonEmptyRow)) 
    {
      cout << "You're not going to like this..." << endl;
      return;
    }

  // If we are forced to lose, so be it.
  if (computerPlayerMustLose(column, row, maxColumns, lastNonEmptyRow))
    {
      cout << "Alas!" << endl;
      return;
    }
  
  // Otherwise, choose a random move, but try to find one
  // that is not obviously dangerous;
  cout << "Hmm..." << endl;
  const int LIMIT = 10;
  row = rand() % lastNonEmptyRow;
  column = rand() % cookie[row];
  for (int attempt = 0; attempt < LIMIT && isADangerousMove(column, row); 
       ++attempt)
    {
      row = rand() % lastNonEmptyRow;
      column = rand() % cookie[row];
    }

}


// Start a new game with a cookie of random size
void startAGame()
{

  // Randomply select size of the cookie, between 4 and MAXROWS
  initialNumberOfRows = numberOfRows = 4 + rand() % (MAXROWS - 4);
  numberOfColumns = numberOfRows;
  while (numberOfColumns == numberOfRows)
    numberOfColumns = 4 + rand() % (MAXROWS - 4);
  
  cout << "The cookie has " << numberOfRows << " rows of " 
       << numberOfColumns << " columns" << endl;

  for (int row = 0; row < numberOfRows; ++row)
    cookie[row] = numberOfColumns;
}







// Remove the crumb at the indicated position and
// all crumbs below and to the right of that position.
void takeABite (int column, int row)
{
  for (int r = row; r < numberOfRows; ++r)
    {
      int c = cookie[r];
      if (c > column)
	cookie[r] = column;
    }
  numberOfRows = 0;
  for (int r = 0; r < initialNumberOfRows && cookie[r] > 0; ++r)
    {
      numberOfRows = r + 1;
    }
  numberOfColumns = (numberOfRows > 0) ? cookie[0] : 0;
}



void playAGame()
{
  startAGame();
  while (!gameEnded())
    {
      displayCookie (cout);

      // First, the human player's move
      int xBite = -1;
      int yBite = -1;
      bool legalMove = false;
      while (!legalMove) 
	{
	  getMoveByHumanPlayer (xBite, yBite);
	  legalMove = biteIsLegal (xBite, yBite);
	  if (!legalMove)
	    {
	      cout << "Sorry, but that is not a legal move." << endl;
	    }
	}
      takeABite (xBite, yBite);
      if (gameEnded())
	{
	  ++nGamesWonByComputerPlayer;
	  cout << "You have eaten the poison crumb! You lose." << endl;
	}
      else
	{
	  // Computer player's move
	  displayCookie(cout);
	  getMoveByComputerPlayer (xBite, yBite);
	  cout << "I will chomp at column " << xBite 
	       << ", row " << yBite << "." << endl;
	  takeABite (xBite, yBite);
	  if (gameEnded())
	    {
	      ++nGamesWonByHumanPlayer;
	      cout << "I had to eat the poison crumb. You win!"
		   << endl;
	    }
	}

    }
}

