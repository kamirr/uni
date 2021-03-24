#include <iostream>
typedef float RealNumber;
typedef double OverloadedRealNumber;
int main(void) {
  RealNumber a = 4.5;
  RealNumber b = 3566789.234576;
  OverloadedRealNumber c = 698519801234.38254;
  OverloadedRealNumber d = 3566789.234576;
  cout << "a = " << a << endl;
  cout << "b = " << b << endl;
  cout << "c = " << c << endl;
  cout << "d = " << d << endl;
  return 0;
}
