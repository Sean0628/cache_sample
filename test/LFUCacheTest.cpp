#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "LFUCache.cpp"

TEST_CASE("It allows to set a value even after the cache is full", "[LFUCache::set]") {
  LFUCache lfu(3);

  REQUIRE(lfu.set(1, "a") == "OK");
  REQUIRE(lfu.set(2, "b") == "OK");
  REQUIRE(lfu.set(3, "c") == "OK");
  REQUIRE(lfu.set(4, "d") == "OK");
};

TEST_CASE("It allows to update a value", "[LFUCache::set]") {
  LFUCache lfu(3);

  lfu.set(1, "a");
  lfu.set(1, "b");
  REQUIRE(lfu.get(1) == "b");
};

TEST_CASE("It allows to get a value", "[LFUCache::get]") {
  LFUCache lfu(3);

  lfu.set(1, "a");
  lfu.set(2, "b");
  lfu.set(3, "c");

  REQUIRE(lfu.get(1) == "a");
  REQUIRE(lfu.get(2) == "b");
  REQUIRE(lfu.get(3) == "c");
};

TEST_CASE("It deletes the least frequently used item", "[LFUCache]") {
  LFUCache lfu(3);

  lfu.set(1, "a");
  lfu.set(2, "b");
  lfu.set(3, "c");

  // Access the items in the cache
  // 1: 2, 2: 2, 3: 3
  // => 2 is the least frequently used item
  lfu.get(1);
  lfu.get(1);
  lfu.get(2);
  lfu.get(3);
  lfu.get(3);

  // Add a new item (overwriting the least frequently used item)
  lfu.set(4, "d");

  REQUIRE(lfu.get(1) == "a");
  REQUIRE(lfu.get(2) == "NULL");
  REQUIRE(lfu.get(3) == "c");
  REQUIRE(lfu.get(4) == "d");
};
