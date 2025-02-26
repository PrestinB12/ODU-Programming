
#include "cookie.h"

using namespace std;

int main (int argc, char** argv)
{
  // Start the random number generator
  int seed = 12371;
  if (argc == 1)
    seed = time(0);
  srand (seed);


  printRules();

  initializeHumanPlayer();
  initializeComputerPlayer();

  bool playAnotherGame = true;
  while (playAnotherGame)
    {
      playAGame();
      printScore();
      cout << "Play again? (Y/N) " << flush;
      string response;
      playAnotherGame = false;
      while (response == "" && cin >> response) 
	{
	  if (response[0] == 'Y' || response[0] == 'y' || 
	      response[0] == 'N' || response[0] == 'n')
	    playAnotherGame = response[0] == 'Y' || response[0] == 'y';
	  else
	    response = "";
	}
    }
  return 0;
}


