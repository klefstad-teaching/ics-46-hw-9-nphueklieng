#include <gtest/gtest.h>

#include "dijkstras.h"
#include "ladder.h"

// ------------------- Test Word Ladder ------------------- //

TEST (LadderTest, TestEditDistance) {
    EXPECT_EQ(edit_distance("cat", "cat"), 0);
    EXPECT_EQ(edit_distance("", "abc"), 3);
    EXPECT_EQ(edit_distance("kitten", "sitting"), 3);
    EXPECT_EQ(edit_distance("flaw", "lawn"), 2);
    EXPECT_EQ(edit_distance("cat", "ca"), 1);
    EXPECT_EQ(edit_distance("cat", "cute"), 2);
    EXPECT_EQ(edit_distance("abcd", "efgh"), 4);
}

TEST (LadderTest, TestLadderFound) {
    set<string> word_list = {"hit", "hot", "dot", "dog", "cog"};
    vector<string> ladder = generate_word_ladder("hat", "cog", word_list);
    vector<string> expected = {"hat", "hot", "dot", "dog", "cog"};
    EXPECT_EQ(ladder, expected);

    vector<string> no_ladder = generate_word_ladder("cat", "cog", word_list);
    vector<string> expect_empty = {};
    EXPECT_EQ(no_ladder, expect_empty);
}

// ------------------- Test Dijkstras ------------------- //
