#include "ladder.h"
#include <cstdlib>
#include <fstream>
#include <queue>
#include <set>
#include <string>
#include <unordered_set>
#include <vector>

void error(string word1, string word2, string msg) {
  cerr << word1 << ", " << word2 << ": " << msg << '\n';
}

bool edit_distance_within(const string &word1, const string &word2, int d) {
  if (abs((int)word1.size() - (int)word2.size()) > 1)
    return false;

  for (int i = 0, j = 0; i < word1.size() && j < word2.size(); i++, j++) {
    if (word1[i] != word2[j]) {
      if (--d)
        return false;
      if (word1.size() > word2.size())
        --j;
      else if (word1.size() < word2.size())
        --i;
    }
  }
  return true;
}

bool is_adjacent(const string &word1, const string &word2) {
  return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string &begin_word,
                                    const string &end_word,
                                    const set<string> &word_list) {
  queue<vector<string>> ladder_queue{};
  ladder_queue.push({begin_word});
  unordered_set<string> visited{};
  visited.insert(begin_word);

  while (!ladder_queue.empty()) {
    vector<string> ladder = ladder_queue.front();
    ladder_queue.pop();

    for (const string &word : word_list) {
      if (visited.find(word) == visited.end() && word != ladder.back() &&
          is_adjacent(ladder.back(), word)) {
        vector<string> new_ladder = ladder;
        new_ladder.push_back(word);
        if (word == end_word)
          return new_ladder;
        visited.insert(word);
        ladder_queue.push(new_ladder);
      }
    }
  }

  return {};
}

void load_words(set<string> &word_list, const string &file_name) {
  ifstream fs{file_name};
  for (string word; fs >> word;)
    word_list.insert(word);
}

void print_word_ladder(const vector<string> &ladder) {
  if (ladder.empty()) {
    cout << "No word ladder found.\n";
    return;
  }
  cout << "Word ladder found: ";
  for (string word : ladder)
    cout << word << ' ';
  cout << '\n';
}

void verify_word_ladder() {
  set<string> word_list;
  load_words(word_list, "src/words.txt");

#define ASSERT(E) (cout << #E << ((E) ? " passed" : " failed") << '\n')
  ASSERT(generate_word_ladder("cat", "dog", word_list).size() == 4);
  ASSERT(generate_word_ladder("marty", "curls", word_list).size() == 6);
  ASSERT(generate_word_ladder("code", "data", word_list).size() == 6);
  ASSERT(generate_word_ladder("work", "play", word_list).size() == 6);
  ASSERT(generate_word_ladder("sleep", "awake", word_list).size() == 8);
  ASSERT(generate_word_ladder("car", "cheat", word_list).size() == 4);
}
