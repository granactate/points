#ifndef HASH_NODE_H
#define HASH_NODE_H

#include "Data.h"
#include <vector>
#include <string>

using namespace std;

class HashNode
{

private:
  int key;
  vector<Data> items;

public:
  HashNode(int _key);
  string toString();

  int getkey();
  void addItem(int value);
  int size();
  int repetitions();
};

#endif