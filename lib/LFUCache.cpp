#include "LFUCache.h"

using namespace std;

LFUCache::LFUCache(
    int mx_size,
    int curr_size
    ) {
  this->mx_size = mx_size;
  this->curr_size = curr_size;
  this->freq = vector<pair<int, int> >(mx_size);
  this->store = unordered_map<int, pair<string, int> >();
}

LFUCache::~LFUCache() {
}

void LFUCache::swap(pair<int, int> &a, pair<int, int> &b) {
  pair<int, int> temp = a;
  a = b;
  b = temp;
}

int LFUCache::get_parent_idx(int idx) const {
  return (idx - 1) / 2;
}

int LFUCache::get_left_child_idx(int idx) const {
  return 2 * idx + 1;
}

int LFUCache::get_right_child_idx(int idx) const {
  return 2 * idx + 2;
}

void LFUCache::heapify(int idx) {
  int left = get_left_child_idx(idx);
  int right = get_right_child_idx(idx);
  int smallest = idx;

  if (left < this->curr_size && this->freq[left].second < this->freq[smallest].second) smallest = left;
  if (right < this->curr_size && this->freq[right].second < this->freq[smallest].second) smallest = right;

  if (smallest != idx) {
    this->store[this->freq[smallest].first].second = idx;
    this->store[this->freq[idx].first].second = smallest;
    swap(this->freq[idx], this->freq[smallest]);
    heapify(smallest);
  }
}

void LFUCache::increment(int idx) {
  this->freq[idx].second++;
  heapify(idx);
}

void LFUCache::insert(int key, string val) {
  if (this->curr_size == this->mx_size) {
    this->store.erase(this->freq[0].first);
    this->curr_size--;
    this->freq[0] = this->freq[this->curr_size];
    this->store[this->freq[0].first].second = 0;
    heapify(0);
  }

  int idx = this->curr_size;
  this->freq[idx] = make_pair(key, 1);
  this->store[key] = make_pair(val, idx);
  this->curr_size++;

  int parent_idx = get_parent_idx(idx);
  while (idx > 0 && this->freq[parent_idx].second > this->freq[idx].second) {
    this->store[this->freq[parent_idx].first].second = idx;
    this->store[this->freq[idx].first].second = get_parent_idx(idx);
    swap(this->freq[idx], this->freq[parent_idx]);

    idx = parent_idx;
    parent_idx = get_parent_idx(idx);
  }
}

string LFUCache::set(int key, string val) {
  if (this->store.find(key) == this->store.end() || this->store[key].first != val)
    insert(key, val);
  else increment(this->store[key].second);

  return "OK";
}

string LFUCache::get(int key) {
  if (this->store.find(key) == this->store.end()) return "NULL";

  increment(this->store[key].second);
  return this->store[key].first;
}
