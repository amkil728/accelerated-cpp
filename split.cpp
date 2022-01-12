/* split.cpp */

#include <algorithm>
#include <string>
#include <vector>

using std::string; using std::vector; using std::find_if;

// true if the char C is whitespace, false otherwise
bool space(char c) {
  return isspace(c);
}

// opposite of space
bool notspace(char c) {
  return !isspace(c);
}

vector<string> split(const string & s) {
  // vector to store result
  vector<string> res;

  // iterators to start and end of a word
  typedef string::const_iterator iter;
  
  iter i = s.begin();

  // while there are characters remaining in s
  while (i != s.end()) {
    // skip blanks
    i = find_if(i, s.end(), notspace);

    // find end of next word
    iter j = find_if(i, s.end(), space);

    // if non whitespace found, substring from i to j
    if (i != s.end()) res.push_back(string(i, j));

    i = j;
  }

  return res;
}
