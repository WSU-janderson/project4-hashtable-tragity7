/**
 * HashTableDebug.cpp
 *
 * Write your tests in this file
 */
#include <iostream>

int main() {
    
    HashTable ht(4);
    std::cout << "Initial table (capacity = " << ht.capacity() << "):\n";
    std::cout << ht << "\n";

    std::cout << "Inserting elements...\n";
    assert(ht.insert("apple", 10));
    assert(ht.insert("banana", 20));
    assert(ht.insert("orange", 30));
    assert(ht.insert("lemon", 40));

    std::cout << "\nTable after insertions:\n";
    std::cout << ht;

    std::cout << "Size: " << ht.size() << ", Alpha: " << ht.alpha() << "\n\n";

    std::cout << "Trying to insert duplicate key 'apple'...\n";
    bool dupInsert = ht.insert("apple", 99);
    std::cout << "Insert result: " << (dupInsert ? "success" : "failed (duplicate)") << "\n\n";

    std::cout << "Testing contains/get:\n";
    assert(ht.contains("banana"));
    assert(!ht.contains("mango"));
    
    return 0;
}
