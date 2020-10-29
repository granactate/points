#include "HashNode.h"
#include "Data.h"

#include <string>
#include <sstream>
#include <algorithm>
#include <vector>

using namespace std;

HashNode::HashNode(int _key)
{
  key = _key;
  items = vector<Data>();
}

int HashNode::getkey()
{
  return key;
}

void HashNode::addItem(int newValue)
{
  
  for (vector<Data>::iterator it = items.begin(); it != items.end(); it++)
  {
    if (it->getkey() == newValue)
    {
      it->increment();
      return;
    }
  }

  Data newData(newValue);
  items.push_back(newData);
}

string HashNode::toString()
{
  std::stringstream ss;


  ss << "key: " << key << endl;
  for (vector<Data>::iterator it = items.begin(); it != items.end(); ++it)
  {
    ss << it->toString();
  }
  return ss.str();
}

int HashNode::size() {
  return items.size();
}

int HashNode::repetitions() {
  int repetitions = 0;

  for (vector<Data>::iterator it = items.begin(); it != items.end(); ++it)
  {
    repetitions += it->getRepetitions();
  }

  return repetitions;
}