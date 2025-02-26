#include "palindrome.h"
#include "unittest.h"

using namespace std;


UnitTest(testShortStrings) {
    assertTrue (isAPalindrome(""));
    assertTrue (isAPalindrome("A"));
    assertTrue (isAPalindrome("x"));
    assertTrue (isAPalindrome("!"));
    assertTrue (isAPalindrome("22"));
    assertTrue (isAPalindrome("aA"));
    assertFalse (isAPalindrome("Ab"));
}

UnitTest(testLongerStrings) {
    assertTrue (isAPalindrome("civic"));
    assertFalse (isAPalindrome("civil"));
    assertFalse (isAPalindrome("reader"));
    assertTrue (isAPalindrome("evil olive"));
    assertTrue (isAPalindrome("Step on no pets."));
    assertFalse (isAPalindrome("Step on no pots."));
    assertTrue (isAPalindrome("Able was I ere I saw elba."));
    assertTrue (isAPalindrome("A man, a plan, a canal: Panama!"));
}

UnitTest(testPreprocess) {
    assertThat (preprocess("Hello world!"), is("helloworld"));
    assertThat (preprocess("Abc123"), is("abc"));
}