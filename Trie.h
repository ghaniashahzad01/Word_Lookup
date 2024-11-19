#ifndef TRIE_H
#define TRIE_H

#include <string>
#include<iostream>
#include <vector>
using namespace std;

class TrieNode {
public:
    TrieNode* children[26];  // Array for children nodes (26 for 'a' to 'z')
    bool isEndOfWord;  // Flag to mark the end of a word

    TrieNode() {
        isEndOfWord = false;
        for (int i = 0; i < 26; i++) {
            children[i] = nullptr;
        }
    }
};

class Trie {
private:
    TrieNode* root;

public:
    Trie();
    void insert(const string& word);
    vector<string> getSuggestionsForPrefix(const string& prefix);
    void getSuggestions(TrieNode* current, string prefix, vector<string>& suggestions);
};

#endif // TRIE_H
