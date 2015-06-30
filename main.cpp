#include <iostream>
#include "HugeInt.h"
using namespace std;

int main(void)
{
  HugeInt x;
  HugeInt y(28825252);
  HugeInt z("314159265258979323846");
  HugeInt result;

  cin >> x;
  result = x + y;
  cout << x << "+" << y << "=" << result << endl;

  result = z - x;
  cout << result << endl;

  return 0;
}

