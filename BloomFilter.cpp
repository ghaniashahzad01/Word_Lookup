#include "BloomFilter.h"

using namespace std;

// Constructor to initialize the size of the Bloom filter vector
BloomFilter::BloomFilter(size_t size) {
    bitset.resize(size, false);  // Resize vector to the given size, initialize to false
}

// Custom hash function 1
int BloomFilter::customHash1(const string& str) const {
    int hashValue = 0;
    for (char ch : str) {
        hashValue = (hashValue * 31 + ch) % bitset.size();  // Simple hash
    }
    return hashValue;
}

// Custom hash function 2
int BloomFilter::customHash2(const string& str) const {
    int hashValue = 0;
    for (char ch : str) {
        hashValue = (hashValue * 17 + ch) % bitset.size();  // Another simple hash
    }
    return hashValue;
}

// Method to add an element to the Bloom filter
void BloomFilter::add(const string& str) {
    int hash1 = customHash1(str);
    int hash2 = customHash2(str);

    // Set the corresponding bits to true
    bitset[hash1] = true;
    bitset[hash2] = true;
}

// Method to check if an element is in the Bloom filter
bool BloomFilter::contains(const string& str) const {
    int hash1 = customHash1(str);
    int hash2 = customHash2(str);

    // If any bit is false, the element is definitely not in the set
    return bitset[hash1] && bitset[hash2];
}
