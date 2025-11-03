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

    auto val = ht.get("banana");
    assert(val.has_value() && val.value() == 20);
    std::cout << "banana -> " << val.value() << "\n";

    if (auto v = ht.get("mango"); v)
        std::cout << "mango -> " << v.value() << "\n";
    else
        std::cout << "mango not found\n";

    std::cout << "\nTesting operator[]:\n";
    try {
        size_t& ref = ht["cherry"];
        std::cout << "cherry (before) = " << ref << "\n";
        ref = 99;
        std::cout << "cherry (after) = " << ht.get("cherry").value() << "\n";
    } catch (const std::out_of_range& e) {
        std::cout << e.what() << "\n";
    }

    std::cout << "\nRemoving 'banana'...\n";
    bool removed = ht.remove("banana");
    std::cout << "Removed: " << (removed ? "yes" : "no") << "\n";
    assert(!ht.contains("banana"));

    std::cout << "\nTable after removal:\n";
    std::cout << ht;


    std::cout << "\ncheck more...\n";
    ht.insert("eggplant", 50);
    ht.insert("fig", 60);
    ht.insert("grape", 70);
    ht.insert("honeydew", 80);

    std::cout << "Table after possible rehash:\n";
    std::cout << ht;

    std::cout << "Capacity after rehash: " << ht.capacity() << "\n";
    std::cout << "Keys in table: ";
    for (const auto& k : ht.keys()) std::cout << k << " ";
    std::cout << "\n\n";

    assert(ht.contains("apple"));
    assert(ht.get("apple").value() == 10);
    assert(ht.contains("cherry"));
    assert(ht.get("cherry").value() == 99);
    assert(!ht.contains("banana"));

    std::cout << "All tests passed successfully yayy!! \n";
    return 0;
}

