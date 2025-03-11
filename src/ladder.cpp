#include "ladder.h"

// ------------------- Global Functions ---------------------- //

void error (string word1, string word2, string msg) {
    // Error Message: Output to standard error stream
    cerr << "[ERROR] " << msg << endl;
    cerr << "   --> " << word1 << endl;
    cerr << "   --> " << word2 << endl;
}

// ------------------- Adjacency / Edit Distance ------------------- //

int edit_distance (const string & str1, const string & str2) {
    // Calculates the edit distance between two strings (insertions / deletions / substitutions)
    
    int m = str1.size(), n = str2.size();

    // Base case: If s1 is empty string, it needs n insertions to match s2
    vector<int> curr(n + 1, 0);
    for (int i = 0 ; i <= n; ++ i)
        curr [i] = i;

    // Iterate over str1
    for (int i = 1 ; i <= m ; ++i) {
        int prev = curr[0];
        curr[0] = i;

        for (int j = 1; j <= n ; ++ j) {
            int temp = curr[j];

            // Character match or mismatch
            if (str1[i - 1] == str2[j - 1])
                curr[j] = prev;
            else
                // Calculate the min distance with 3 possible edits: insertion, deletion, substitution
                curr[j] = min({curr[j - 1], prev, curr[j]}) + 1;
            
            prev = temp;   
        }    
    }

    // Return the final min edit distance
    return curr[n];
}

bool edit_distance_within (const string & str1 , const string & str2, int d) {
    // Check str1 & str2 is within d edit distance
    return edit_distance(str1 , str2) <= d;
}

bool is_adjacent (const string & word1, const string & word2) {
    // Check edit distance is within 1
    return edit_distance(word1, word2) == 1;
}

bool not_visited (const set<string> & visited , const string & word) {
    // Check if the word is in the set of visited words
    return visited.find(word) == visited.end();
}

vector<string> generate_word_ladder (const string & begin_word, const string & end_word, const set<string> & word_list) {
    // Find minimum-length ladder using BFS

    // Check start & end (Prevent infinite loop)
    if (begin_word == end_word) {
        error (begin_word , end_word, "Start and End words are equivalent");
        return {};
    }

    vector<string> ladder;
    queue< vector<string> > q;  // Use Queue to store partial ladders: possibilities to explore (Each partial ladder is a stack => Queue of stacks)
    q.push({begin_word});
    set<string> visited;
    visited.insert(begin_word);

    // BFS
    while(!q.empty()) {
        ladder = q.front();
        q.pop();
        string last_word = ladder.back();

        // Examine valid ladders: in the dictionary, adjacent, and not visited
        for (auto & word: word_list)
            if (is_adjacent(last_word, word) && not_visited(visited, word) ) {
                visited.insert(word);
                vector<string> new_ladder = ladder;
                new_ladder.push_back(word);

                if (word == end_word)
                    return new_ladder;

                q.push(new_ladder);
            }
    }

    // No ladder found
    error (begin_word, end_word, "No ladder was found.");
    return {};
}

// ------------------- Word Ladder Verification ------------------- //

void load_words(set<string> & word_list, const string& file_name) {
    // Load the words from the file into the word_list set
    ifstream in(file_name);

    string word;
    while (in >> word)
        word_list.insert(word);
}

void print_word_ladder(const vector<string>& ladder) {

}

void verify_word_ladder () {
    // Verify word ladder program
    set<string> word_list;
    load_words (word_list, "src/words.txt");

    myassert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    myassert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    myassert(generate_word_ladder("code", "data", word_list).size() == 6);
    myassert(generate_word_ladder("work", "play", word_list).size() == 6);
    myassert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    myassert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}