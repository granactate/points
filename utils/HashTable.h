#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "HashNode.h"

#include <string>
#include <sstream>
#include <algorithm>
#include <vector>

using namespace std;

class HashTable
{

private:
  vector<HashNode> nodes;

public:
  HashTable();
  void addTuple(short i, short j);
  HashNode *getNodeByKey(short key);

  string toString();
  int getUniquenessPercentage();
};

#endif