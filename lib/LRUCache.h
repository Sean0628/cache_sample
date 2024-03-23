#pragma once

#include <string>
#include <list>

using namespace std;

class LRUCache {
  private:
    static const int MAX_SIZE = 100;

    int mx_size;
    list<pair<int, string> > store;
    unordered_map<int, list<pair<int, string> >::iterator> refs;

  public:
    LRUCache(
        int mx_size = MAX_SIZE
        );
    ~LRUCache();

    string get(int key);
    string set(int key, string val);
};
