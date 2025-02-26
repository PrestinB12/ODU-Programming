#include <regex>
#include <string>

#include "testUtilities.h"


using namespace std;


std::string normalizeWhiteSpace (const std::string& s)
{
  std::regex multiSpace ("[[:space:]]+");
  auto flags = std::regex_constants::match_default;
  string result = regex_replace(s, multiSpace, " ", flags);
  return result;
}

bool isomorphic (const node* a, const node* b)
{
  // Two trees are isomorphic if they have the same shape and data
  if (a == NULL)
    return (b == NULL);
  else if (b == NULL)
    return false;
  else if (normalizeWhiteSpace(a->detailText)
		   == normalizeWhiteSpace(b->detailText))
    return isomorphic(a->ifYes, b->ifYes) && isomorphic(a->ifNo, b->ifNo);
  else
    return false;
}
