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


