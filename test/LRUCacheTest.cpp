#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "LRUCache.cpp"

TEST_CASE("It allows to set a value even after the cache is full", "[LFUCache::set]") {
  LRUCache lru(3);

  REQUIRE(lru.set(1, "a") == "OK");
  REQUIRE(lru.set(2, "b") == "OK");
  REQUIRE(lru.set(3, "c") == "OK");
  REQUIRE(lru.set(4, "d") == "OK");
};

TEST_CASE("It allows to get a value", "[LFUCache::get]") {
  LRUCache lru(3);

  lru.set(1, "a");
  lru.set(2, "b");
  lru.set(3, "c");

  REQUIRE(lru.get(1) == "a");
  REQUIRE(lru.get(2) == "b");
  REQUIRE(lru.get(3) == "c");
};

TEST_CASE("It allows to update a value", "[LFUCache::set]") {
  LRUCache lru(3);

  lru.set(1, "a");
  lru.set(1, "b");
  REQUIRE(lru.get(1) == "b");
};

TEST_CASE("It deletes the least recently used item", "[LFUCache]") {
  LRUCache lru(3);

  lru.set(1, "a");
  lru.set(2, "b");
  lru.set(3, "c");

  // Access the items in the cache
  // 1: 3, 2: 2, 3: 1
  // => 1 is the least recently used item
  lru.get(1);
  lru.get(1);
  lru.get(2);
  lru.get(3);
  lru.get(3);

  // Add a new item (overwriting the least recently used item)
  lru.set(4, "d");

  REQUIRE(lru.get(1) == "NULL");
  REQUIRE(lru.get(2) == "b");
  REQUIRE(lru.get(3) == "c");
  REQUIRE(lru.get(4) == "d");
};
