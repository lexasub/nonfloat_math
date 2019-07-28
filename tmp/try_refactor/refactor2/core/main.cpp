#include "math.h"
#include <iostream>

using namespace std;

int main()
{
  math t,u;
  (u *= 4)/=9;
  cout << t << endl;
  t += 2;
  cout << t << endl;
  t += 8;
  cout << t << endl;
  t /= 2;
  cout << t << endl << "u:(" << u << endl << ")" << endl;
  cout << (t * u) << endl;
  return 0;
}
