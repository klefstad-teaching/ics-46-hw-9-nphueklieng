#ifndef LADDER
#define LADDER

#include <iostream>
#include <fstream>
#include <queue>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

void error(string word1, string word2, string msg);

int edit_distance (const string & str1 , const string & str2);
bool edit_distance_within(const std::string& str1, const std::string& str2, int d);
bool is_adjacent(const string& word1, const string& word2);
bool not_visited (const set<string> & visited , const string & word);
set<string> get_patterns (const string & word, const set<string> & word_list);
vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list);

void load_words(set<string> & word_list, const string& file_name);
void print_word_ladder(const vector<string>& ladder);

# define myassert(e) { cout << #e << ((e) ? " passed": " failed") << endl ; }
void verify_word_ladder();

#endif