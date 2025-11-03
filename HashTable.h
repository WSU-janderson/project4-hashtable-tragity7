/**
* Sidra Ali
* CS3100 - Data Structures and Algorithms
* Project 4: Hash Table
*
* HashTable.h
* header file that declares the HashTable and HashTableBucket classes
*/

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <vector>
#include <string>
#include <optional>
#include <random>
#include <algorithm>

// state of bucket
enum BucketType { NORMAL, ESS, EAR };


/**
 * class HashTableBucket - represents a single entry in the hash table
 * each bucket stores a string key, an associated size_t value, and a BucketType (state)
 */
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

/**
 * class HashTable - implements a hash table 
 * the hash table automatically rehashes (doubles capacity) when the load factor exceeds 0.5
 * our collision resolution policy is pseudo random probing
 */
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
    HashTable(size_t initCapacity = 8);

    bool insert(const std::string& key, const size_t& value);
    bool remove(const std::string& key);
    bool contains(const std::string& key) const;
    std::optional<size_t> get(const std::string& key) const;
    size_t& operator[](const std::string& key);

    std::vector<std::string> keys() const;
    double alpha() const;
    size_t capacity() const;
    size_t size() const;

    friend std::ostream& operator<<(std::ostream& os, const HashTable& ht);
};

#endif
