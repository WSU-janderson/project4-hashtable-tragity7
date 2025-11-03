/**
 * HashTable.h
 */

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <vector>
#include <string>
#include <optional>
#include <random>
#include <algorithm>

enum BucketType { NORMAL, ESS, EAR };

class HashTableBucket {
private:
    std::string key;
    size_t value;
    BucketType type;

public:
    HashTableBucket();
    HashTableBucket(const std::string& key, const size_t& value);

// add functions

    friend std::ostream& operator<<(std::ostream& os, const HashTableBucket& bucket);
};

class HashTable {
private:
// add private variables

public:
// add public variables

    friend std::ostream& operator<<(std::ostream& os, const HashTable& ht);
};

#endif
