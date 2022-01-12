/* cross_ref.cpp
 *
 * Generates a cross-reference table for a file, that indicates at which line
 * each word occurs in the file.
 */

#include <algorithm>
#include <cctype>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "split.h"

using std::string; using std::vector; using std::map;
using std::find_if;
using std::istream; using std::cin;
using std::cout; using std::endl;

map<string, vector<int> > cross_ref
(istream & in, vector<string> splitter(const string&) = split) {
  map<string, vector<int> > ref; // stores xref table
  string line; // stores current line
  int line_number = 0;

  // get next line from in
  // invariant: LINE_NUMBER is the number of lines seen so far
  while(getline(in, line)) {
    ++line_number;
    
    // split line into words
    vector<string> words = splitter(line);

    // for each word in line
    for (vector<string>::size_type i = 0; i != words.size(); ++i) {
      // add line number to xref for word
      ref[words[i]].push_back(line_number);
    }
  }

  return ref;
}

int main() {
  // generate cross-ref table
  map<string, vector<int> > table = cross_ref(cin);

  // display results
  for (map<string, vector<int> >::const_iterator i = table.begin();
       i != table.end(); ++i) {
    // write word
    cout << i->first << " occurs on line(s): ";

    // and number of first line it occurs in
    vector<int>::const_iterator line_it = i->second.begin();
    cout << *line_it;

    // followed by remaining line numbers, if any
    while (line_it != i->second.end()) {
      cout << ", " << *line_it;
      ++line_it;
    }

    // newline to separate next word
    cout << endl;
  }

  return 0;
}
