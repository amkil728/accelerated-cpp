/* generate_sentence.cpp */

#include <cstdlib>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>
#include "split.h"

using std::map; using std::string; using std::vector;
using std::istream; using std::getline; using std::cin;
using std::cout; using std::endl;
using std::domain_error; using std::logic_error;

typedef vector<string> Rule;
typedef vector<Rule> Rule_collection;
typedef map<string, Rule_collection> Grammar;

int nrand(int n) {
  if (n <= 0 || n > RAND_MAX) {
    throw domain_error("Argument to nrand is out of range.");
  }

  const int bucket_size = RAND_MAX / n;
  int r;

  do r = rand() / bucket_size;
  while (r >= n);

  return r;
}

Grammar read_grammar(istream& is) {
  Grammar g;
  string line;

  while (getline(is, line)) {
    // split input into tokens
    vector<string> entry = split(line);

    if (!entry.empty()) {
      g[entry[0]].push_back(Rule(entry.begin() + 1, entry.end()));
    }
  }

  return g;
}

// determine if a string is a category, by checking if it is bracketed
bool is_category(string s) {
  return s.size() > 1 && s[0] == '<' && s[s.size() - 1] == '>';
}

void generate_helper(const Grammar & g,
		     const string & word,
		     vector<string> & sentence) {
  if (!is_category(word)) {
    sentence.push_back(word);
  } else {
    Grammar::const_iterator finder = g.find(word);
    if (finder == g.end()) {
      throw logic_error("undefined rule");
    }

    const Rule_collection rules = finder->second;

    // select a rule at random
    const Rule & r = rules[nrand(rules.size())];

    for (Rule::const_iterator it = r.begin(); it != r.end(); ++it) {
      generate_helper(g, *it, sentence);
    }
  }
}

vector<string> generate_sentence(Grammar g) {
  vector<string> sentence;
  generate_helper(g, "<sentence>", sentence);
  return sentence;
}

int main() {
  // vector<string> sentence = generate_sentence(read_grammar(cin));

  // vector<string>::const_iterator it = sentence.begin();
  // if (!sentence.empty()) {
  //   cout << *it;
  //   ++it;
  // }

  // while (it != sentence.end()) {
  //   cout << ' ' << *it;
  //   ++it;
  // }

  // cout << endl;

  int i = rand();
  cout << i << endl;
  
  return 0;
}
