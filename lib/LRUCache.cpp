#include "LRUCache.h"

using namespace std;

LRUCache::LRUCache(
    int mx_size
    ) {
  this->mx_size = mx_size;
}

LRUCache::~LRUCache() {
}

string LRUCache::set(int key, string val) {
  if (this->refs.find(key) == this->refs.end()) {
    if (this->store.size() == this->mx_size) {
      int key_to_remove = this->store.back().first;
      this->store.pop_back();
      this->refs.erase(key_to_remove);
    }
  } else {
    this->store.erase(this->refs[key]);
  }

  this->store.push_front(make_pair(key, val));
  this->refs[key] = this->store.begin();

  return "OK";
}

string LRUCache::get(int key) {
  if (this->refs.find(key) == this->refs.end()) return "NULL";

  string val = this->refs[key]->second;
  this->store.erase(this->refs[key]);
  this->store.push_front(make_pair(key, val));
  this->refs[key] = this->store.begin();

  return val;
}
