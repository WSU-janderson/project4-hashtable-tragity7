// I actually did zybook chapter 1.27 so I will use auto

/**
* Sidra Ali 
* CS3100 - Data Structures and Algorithms
* Project 4: Hash Table
*
* HashTable.cpp
* defines the member functions of the HashTable and HashTableBucket classes
*/

#include "HashTable.h"

/* constructor for HashTableBucket.
 *
 * Initializes an empty bucket with key = "" and value = 0,
 * and sets its type to ESS 
 */
HashTableBucket::HashTableBucket() : key(""), value(0), type(ESS) {}

/* Constructs a HashTableBucket with a given key and value.
 * Parameters: k (the key to store) and v (the value to associate with the key)
 */
HashTableBucket::HashTableBucket(const std::string& k, const size_t& v)
    : key(k), value(v), type(NORMAL) {}

/* loads (meaning adds or like "fills the bucket") so now it is assigned NORMAL
* Parameters: k and v
*/
void HashTableBucket::load(const std::string& k, const size_t& v) {
    key = k;
    value = v;
    type = NORMAL;
}

 /** checks if the bucket is empty
* returns true if bucket is not normal
* returns false if bucket is normal
bool HashTableBucket::isEmpty() const {
    return type != NORMAL;
}

/** checks if the bucket has always been empty (ESS)
* returns true if bucket is ESS
* returns false if bucket is not ESS
*/
bool HashTableBucket::isEmptySinceStart() const {
    return type == ESS;
}

/** checks if the bucket is empty but had something in it before (EAR)
* returns true if bucket is EAR
* returns false if bucket is not EAR
*/  
bool HashTableBucket::isEmptyAfterRemove() const {
    return type == EAR;
}

void HashTableBucket::makeNormal() { type = NORMAL; } // assigns bucket as NORMAL
void HashTableBucket::makeESS() { type = ESS; } // assigns bucket as ESS
void HashTableBucket::makeEAR() { type = EAR; } // assigns bucket as EAR

/**
 * overloads the output stream operator for HashTableBucket
 * Parameters: the output stream and the bucket to print
 * Return: the output stream with bucket data formatted as (key, value), [EAR], or [ESS].
 */
std::ostream& operator<<(std::ostream& os, const HashTableBucket& bucket) {
    if (bucket.type == NORMAL)
        os << "(" << bucket.key << ", " << bucket.value << ")";
    else if (bucket.type == EAR)
        os << "[EAR]";
    else
        os << "[ESS]";
    return os;
}

 * constructs a HashTable with the specified initial capacity size_t
 * Parameters: initCapacity (the initial number of buckets to allocate)
 */
HashTable::HashTable(size_t initCapacity)
    : tableData(initCapacity), numElements(0) {
    generateOffsets(initCapacity);
}

/**
 * computes the hash index for a given key
 * Parameters: the key to hash
 * Return: the index of the hash value % table size
 */
size_t HashTable::hashFunction(const std::string& key) const {
    std::hash<std::string> hashFn;
    return hashFn(key) % tableData.size();
}

/**
 * PSEUDO RANDOM PROBING FUNCTION
 * shuffling the offset
 * Paramters: the key to hash
 * Return: the index of the hash value % table size
 */
    void HashTable::generateOffsets(size_t capacity) {
        offsets.clear();
        for (size_t i = 1; i < capacity; ++i)
            offsets.push_back(i);

        // I tried using time as a seed and it wasn't working and in today's class u said we can hardcode random values so that's what I ended up doing
        // 12345, 891011, 101010 can be changed to other values
        unsigned int seed = 12345; 
        auto randomPattern = [&seed]() {
            seed = (891011 * seed + 12345) & 101010;
            return seed;
        };

        // swap to shuffle
        for (size_t i = offsets.size() - 1; i > 0; --i) {
            size_t j = randomPattern() % (i + 1);
            std::swap(offsets[i], offsets[j]);
        }
    }

/**
 * table resizing
 * double the hash table capacity and reinsert existing elements
 * called when the load factor (alpha) exceeds 0.5
 */
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

/**
 * inserts key-value pair into hash table
 * Parameters: the key and its corresponding value
 * Return: True if insertion succeeds, false if key already exists or table is full.
 */
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

/**
 * removes a key-value pair from the table
 * Parameters: the key to remove
 * Return: True if key was found and removed, false if not
 */
bool HashTable::remove(const std::string& key) {
    size_t idx = probeIndex(key);
    if (idx < tableData.size()) {
        tableData[idx].makeEAR();
        numElements--;
        return true;
    }
    return false;
}

/**
 * checks if a specific key exists in the table
 * Parameters: the key u're looking for
 * Return: True if the key is found, false if it isn't.
 */
bool HashTable::contains(const std::string& key) const {
    size_t idx = probeIndex(key);
    return idx < tableData.size();
}

/**
 * retrieves the value associated with a key
 * Paramters: the key to look up
 * Return: the v value associated with the key if found, otherwise std::nullopt.
 */
std::optional<size_t> HashTable::get(const std::string& key) const {
    size_t idx = probeIndex(key);
    if (idx < tableData.size())
        return tableData[idx].getValue();
    return std::nullopt;
}


/** OPERATOR
 * accesses a value by key using the [] operator.
 * Parameter: the key to look up
 * Return: reference to the value if key exists
 * Throws: std::out_of_range if key not found
 */
size_t& HashTable::operator[](const std::string& key) {
    size_t idx = probeIndex(key);
    if (idx < tableData.size())
        return tableData[idx].getValue();
    throw std::out_of_range("Key not found");
}


/**
 * returns a list of all keys currently in the table.
 */
std::vector<std::string> HashTable::keys() const {
    std::vector<std::string> k;
    for (const auto& b : tableData)
        if (!b.isEmpty())
            k.push_back(b.getKey());
    return k;
}


/**
 * ALPHA CALCULATION
 *computes the current load factor (alpha) of the table
 * Return: ratio of number of elements to table capacity
 */
double HashTable::alpha() const {
    return static_cast<double>(numElements) / tableData.size();
}

// returns current capacity
size_t HashTable::capacity() const {
    return tableData.size();
}

// returns the number of key-value pairs currently stored
size_t HashTable::size() const {
    return numElements;
}


/**
 * overloads the output stream operator 
 * Parameters: os (output stream) and ht (the hashtable to print)
 * Return: the output stream containing bucket data
 */
std::ostream& operator<<(std::ostream& os, const HashTable& ht) {
    for (size_t i = 0; i < ht.tableData.size(); ++i) {
        os << "[" << i << "]: " << ht.tableData[i] << "\n";
    }
    return os;
}


