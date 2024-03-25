# C++ LRU and LFU Cache Implementations
This repository contains C++ implementations for Least Recently Used (LRU) and Least Frequently Used (LFU) cache. This is only a demonstration and should not be used in production.

## LRU Cache
The LRU cache is implemented using a doubly linked list and a hash map. The doubly linked list is used to store the key-value pairs, and the hash map is used to store the references to the corresponding nodes in the linked list.

### `get(key: int) -> string` O(1)
Get the value of the key if the key exists in the cache, otherwise return "NULL".

### `set(key: int, value: string) -> string` O(1)
Set or insert the value if the key is not already present. When the cache reaches its capacity, it should invalidate the least recently used item before inserting a new item.

```cpp
LRUCache lru(3);

lru.set(1, "a");
lru.set(2, "b");
lru.set(3, "c");

lru.get(1);
lru.get(1);
lru.get(2);
lru.get(3);
lru.get(3);

// Add a new item (overwriting the least recently used item)
lru.set(4, "d");

lru.get(1); // => "NULL"
lru.get(2); // => "b"
lru.get(3); // => "c"
lru.get(4); // => "d"
```

## LFU Cache
The LFU cache is implemented using a vector and a hash map. The vector is used to store the frequency of access for each key-value pair, and the hash map is used to store the key-value pairs along with their corresponding frequence indices. The implementation uses a min heap to keep track of the least frequently used items.

### `get(key: int) -> string` O(log n)
Get the value of the key if the key exists in the cache, otherwise return "NULL".

### `set(key: int, value: string) -> string` O(log n)
Set or insert the value if the key is not already present. When the cache reaches its capacity, it should invalidate the least frequently used item before inserting a new item.

```cpp
LFUCache lfu(3);

lfu.set(1, "a");
lfu.set(2, "b");
lfu.set(3, "c");

lfu.get(1);
lfu.get(1);
lfu.get(2);
lfu.get(3);
lfu.get(3);

// Add a new item (overwriting the least frequently used item)
lfu.set(4, "d");

lfu.get(1) // => "a"
lfu.get(2) // => "NULL"
lfu.get(3) // => "c"
lfu.get(4) // => "d"
```
