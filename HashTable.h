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

    void load(const std::string& key, const size_t& value);
    bool isEmpty() const;
    bool isEmptySinceStart() const;
    bool isEmptyAfterRemove() const;

    void makeNormal();
    void makeESS();
    void makeEAR();

    const std::string& getKey() const { return key; }
    size_t& getValue() { return value; }
    const size_t& getValue() const { return value; }
    BucketType getType() const { return type; }

    friend std::ostream& operator<<(std::ostream& os, const HashTableBucket& bucket);
};

class HashTable {
private:
    std::vector<HashTableBucket> tableData;
    std::vector<size_t> offsets;
    size_t numElements;

    size_t hashFunction(const std::string& key) const;
    void generateOffsets(size_t capacity);
    void rehash();
    size_t probeIndex(const std::string& key, bool forInsert = false) const;

public:
// add public variables

    friend std::ostream& operator<<(std::ostream& os, const HashTable& ht);
};

#endif
