#include "Trie.h"
#include<iostream>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

using namespace std;

Trie::Trie() {
    root = new TrieNode();  // Initialize root node
}

void Trie::insert(const string& word) {
    TrieNode* current = root;
    for (char c : word) {
        int index = c - 'a';  // Convert char to index ('a' -> 0, 'b' -> 1, ..., 'z' -> 25)
        if (!current->children[index]) {
            current->children[index] = new TrieNode();
        }
        current = current->children[index];
    }
    current->isEndOfWord = true;  // Mark the end of the word
}

void Trie::getSuggestions(TrieNode* current, string prefix, vector<string>& suggestions) {
    if (current->isEndOfWord) {
        suggestions.push_back(prefix);  // Add word to suggestions
    }

    // Traverse through all possible child nodes
    for (int i = 0; i < 26; i++) {
        if (current->children[i]) {
            getSuggestions(current->children[i], prefix + char(i + 'a'), suggestions);
        }
    }
}

vector<string> Trie::getSuggestionsForPrefix(const string& prefix) {
    TrieNode* current = root;
    vector<string> suggestions;

    // Traverse the trie to the node corresponding to the given prefix
    for (char c : prefix) {
        int index = c - 'a';
        if (!current->children[index]) {
            return suggestions;  // No suggestions if prefix doesn't exist
        }
        current = current->children[index];
    }

    // Recursively gather suggestions from this node
    getSuggestions(current, prefix, suggestions);
    return suggestions;
}
