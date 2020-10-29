#ifndef DATA_H
#define DATA_H

#include <vector>
#include <string>

using namespace std;

class Data
{

private:
  int key;
  int repetitions;

public:
  Data(int _key);
  string toString();

  void setKey(int newKey);
  int getkey();

  int getRepetitions();
  void increment();
};

#endif