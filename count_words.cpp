// count_words.cpp

#include <iostream>
#include <map>
#include <string>

using std::string; using std::map;
using std::cin; using std::cout; using std::endl;

int main() {
  string s;
  map<string, int> word_count;

  while (cin >> s) {
    ++word_count[s];
  }

  cout << "word\tcount" << endl;
  
  for (map<string, int>::const_iterator i = word_count.begin();
       i != word_count.end(); ++i) {
    cout << i->first << '\t' << i->second << endl;
  }

  return 0;
}
