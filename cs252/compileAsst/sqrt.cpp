#include "sqrt.h"
#include <cmath>

using std::abs;

/**
 * Compute the square root of x, with an accuracy of 
 * plus or minus eps*X.
 */
double computeSqrt (double x, double eps)
{
  if (x <= 0.0)
	return x;

  double limit = eps*x;
  double minLimit = 0.00000001*x;
  if (minLimit > limit)
	limit = minLimit;

  double guess = x / 2.0;
  double lastGuess = x + 2.0*limit;
  // Newton Raphson method
  while (abs(guess - lastGuess) > limit)
  {
	lastGuess = guess;
	guess = 0.5 * (guess + x / guess);
  }
  return guess;
}

