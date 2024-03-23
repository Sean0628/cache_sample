#pragma once

#include <string>

using namespace std;

class LFUCache {
  private:
    static const int MAX_SIZE = 100;

    int mx_size;
    int curr_size;
    vector<pair<int, int> > freq;
    unordered_map<int, pair<string, int> > store;

    void swap(pair<int, int> &a, pair<int, int> &b);
    int get_parent_idx(int idx) const;
    int get_left_child_idx(int idx) const;
    int get_right_child_idx(int idx) const;
    void heapify(int idx);
    void increment(int idx);
    void insert(int key, string val);

  public:
    LFUCache(
        int mx_size = MAX_SIZE,
        int curr_size = 0
        );
    ~LFUCache();

    string get(int key);
    string set(int key, string val);
};
