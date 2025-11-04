[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/7RAFczHS)
# Project 4 - HashTable

Time Complexity Analysis:

insert(const std::string& key, const size_t& value)
computing the hash index is O(1), pseudo-random probing finds an empty slot quickly, so insertion is constant-time. If many collisions occur, probing may check nearly every slot so O(n) is the worst case.rehash doubles the table size, but that doesn't happen very often.

remove(const std::string& key)
average case is O(1), pseudo-random probing finds an empty slot quickly, so insertion is constant-time (just like insertion). Clustering would mean a full probe (every slot needs to be checked) is needed. Worst case is O(n).

contains(const std::string& key)
the contains method calls probeIndex(key) which performs pseudo-random probing so it works just like removal and insertion and the average case is O(1) and the worst case is O(n).

get(const std::string& key)
the get method calls probeIndex(key) which performs pseudo-random probing so it works just like remove/insert/contain and the average case is O(1) and the worst case is O(n). returns a value.

operator[](const std::string& key)
the get method calls probeIndex(key) which performs pseudo-random probing so it works just like remove/insert/contain/get and the average case is O(1) and the worst case is O(n). returns a reference. 
