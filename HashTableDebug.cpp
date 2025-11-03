/**
 * HashTableDebug.cpp
 *
 * Write your tests in this file
 */
#include <iostream>

int main() {
    
    HashTable fbnd(4);
    std::cout << "Initial table (capacity = " << fbnd.capacity() << "):\n";
    std::cout << fbnd << "\n";

    // --- Insert Elements ---
    std::cout << "Inserting elements...\n";
    assert(fbnd.insert("apple", 10));
    assert(fbnd.insert("banana", 20));
    assert(fbnd.insert("orange", 30));
    assert(fbnd.insert("lemon", 40));

    std::cout << "\nTable after insertions:\n";
    std::cout << fbnd;

    
    return 0;
}
