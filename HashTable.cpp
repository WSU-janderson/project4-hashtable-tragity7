/**
 * HashTable.cpp
 */

#include "HashTable.h"

HashTableBucket::HashTableBucket() : key(""), value(0), type(ESS) {}

HashTableBucket::HashTableBucket(const std::string& k, const size_t& v)
    : key(k), value(v), type(NORMAL) {}

void HashTableBucket::load(const std::string& k, const size_t& v) {
    key = k;
    value = v;
    type = NORMAL;
}

bool HashTableBucket::isEmpty() const {
    return type != NORMAL;
}

bool HashTableBucket::isEmptySinceStart() const {
    return type == ESS;
}

bool HashTableBucket::isEmptyAfterRemove() const {
    return type == EAR;
}

void HashTableBucket::makeNormal() { type = NORMAL; }
void HashTableBucket::makeESS() { type = ESS; }
void HashTableBucket::makeEAR() { type = EAR; }

std::ostream& operator<<(std::ostream& os, const HashTableBucket& bucket) {
    if (bucket.type == NORMAL)
        os << "(" << bucket.key << ", " << bucket.value << ")";
    else if (bucket.type == EAR)
        os << "[EAR]";
    else
        os << "[ESS]";
    return os;
}

HashTable::HashTable(size_t initCapacity)
    : tableData(initCapacity), numElements(0) {
    generateOffsets(initCapacity);
}

size_t HashTable::hashFunction(const std::string& key) const {
    std::hash<std::string> hashFn;
    return hashFn(key) % tableData.size();
}

void HashTable::generateOffsets(size_t capacity) {
    offsets.clear();
    for (size_t i = 1; i < capacity; ++i)
        offsets.push_back(i);

    // function to randomize
}

void HashTable::rehash() {
    size_t newCapacity = tableData.size() * 2;
    std::vector<HashTableBucket> oldData = tableData;

    tableData = std::vector<HashTableBucket>(newCapacity);
    numElements = 0;
    generateOffsets(newCapacity);

    for (const auto& bucket : oldData) {
        if (bucket.getType() == NORMAL)
            insert(bucket.getKey(), bucket.getValue());
    }
}

bool HashTable::insert(const std::string& key, const size_t& value) {
    if (alpha() >= 0.5)
        rehash();

    if (contains(key))
        return false;

    size_t idx = probeIndex(key, true);
    if (idx >= tableData.size())
        return false; // table full

    tableData[idx].load(key, value);
    numElements++;
    return true;
}

bool HashTable::remove(const std::string& key) {
    size_t idx = probeIndex(key);
    if (idx < tableData.size()) {
        tableData[idx].makeEAR();
        numElements--;
        return true;
    }
    return false;
}
