#include <iostream>
#include <string>
using namespace std;

class HugeInt{
  friend ostream & operator<< (ostream & out, const HugeInt & BigNumber);
  friend istream & operator>> (istream & in, HugeInt & BigNumber);
public:
  HugeInt(string a); // default and default string constructor
  HugeInt(int SmallNumber=0); // default integer constructor
  HugeInt(HugeInt & CopyHugeInt); // copy constructor
  HugeInt operator+ (HugeInt & BigNumber);
  void operator= (const HugeInt & BigNumber);
  HugeInt operator- (HugeInt BigNumber);
  int size;
  int *number;
  char sign;
};

