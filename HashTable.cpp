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

