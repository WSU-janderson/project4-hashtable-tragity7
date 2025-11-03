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

        // Simple deterministic pseudo-random shuffle using LCG
        unsigned int seed = 12345; // <-- hardcoded seed
        auto randomPattern = [&seed]() {
            seed = (1103515245 * seed + 12345) & 0x7fffffff;
            return seed;
        };

        for (size_t i = offsets.size() - 1; i > 0; --i) {
            size_t j = randomPattern() % (i + 1);
            std::swap(offsets[i], offsets[j]);
        }
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

bool HashTable::contains(const std::string& key) const {
    size_t idx = probeIndex(key);
    return idx < tableData.size();
}

std::optional<size_t> HashTable::get(const std::string& key) const {
    size_t idx = probeIndex(key);
    if (idx < tableData.size())
        return tableData[idx].getValue();
    return std::nullopt;
}

size_t& HashTable::operator[](const std::string& key) {
    size_t idx = probeIndex(key);
    if (idx < tableData.size())
        return tableData[idx].getValue();
    throw std::out_of_range("Key not found");
}

std::vector<std::string> HashTable::keys() const {
    std::vector<std::string> k;
    for (const auto& b : tableData)
        if (!b.isEmpty())
            k.push_back(b.getKey());
    return k;
}

double HashTable::alpha() const {
    return static_cast<double>(numElements) / tableData.size();
}

size_t HashTable::capacity() const {
    return tableData.size();
}

size_t HashTable::size() const {
    return numElements;
}

std::ostream& operator<<(std::ostream& os, const HashTable& ht) {
    for (size_t i = 0; i < ht.tableData.size(); ++i) {
        os << "[" << i << "]: " << ht.tableData[i] << "\n";
    }
    return os;
}


