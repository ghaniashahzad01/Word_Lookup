#ifndef BLOOMFILTER_H
#define BLOOMFILTER_H

#include <string>
#include <vector>
#include <iostream>
using namespace std;

class BloomFilter {
private:
    vector<bool> bitset;  // Vector for Bloom filter (instead of bitset)

    // Custom hash functions
    int customHash1(const string& str) const;
    int customHash2(const string& str) const;

public:
    // Constructor to initialize bitset size
    BloomFilter(size_t size = 1000);

    // Method to add an element
    void add(const string& str);

    // Method to check if an element is in the set
    bool contains(const string& str) const;
};

#endif // BLOOMFILTER_H
