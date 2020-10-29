#include "Data.h"
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

Data::Data(int _key)
{
  key = _key;
  repetitions = 1;
}

string Data::toString()
{
  std::stringstream ss;

  ss << "{ 'key':" << key << " , ";
  ss << "'repetitions': " << repetitions << "}" << endl;
  return ss.str();
}

void Data::setKey(int newKey)
{
  key = newKey;
}

int Data::getkey()
{
  return key;
}

int Data::getRepetitions()
{
  return repetitions;
}

void Data::increment()
{
  repetitions++;
}
