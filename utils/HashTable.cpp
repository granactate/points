#include "HashTable.h"
#include "HashNode.h"

#include <string>
#include <sstream>
#include <algorithm>
#include <vector>

using namespace std;

HashTable::HashTable()
{
  nodes = vector<HashNode>();
}

void HashTable::addTuple(short i, short j)
{
  HashNode *finded = getNodeByKey(i);

  if (finded)
  {
    finded->addItem(j);
  }
  else
  {
    HashNode newNode(i);
    newNode.addItem(j);
    nodes.push_back(newNode);
  }
}

HashNode *HashTable::getNodeByKey(short key)
{

  for (vector<HashNode>::iterator it = nodes.begin(); it != nodes.end(); it++)
  {
    if (it->getkey() == key)
    {
      return &(*it);
    }
  }

  return NULL;
}

string HashTable::toString()
{
  std::stringstream ss;

  for (vector<HashNode>::iterator it = nodes.begin(); it != nodes.end(); ++it)
  {
    ss << it->toString() << endl;
  }
  return ss.str();
}

int HashTable::getUniquenessPercentage() {
  for (vector<HashNode>::iterator it = nodes.begin(); it != nodes.end(); ++it)
  {
    int uniques = it->size();
    int repetitions = it->repetitions();
  }
}