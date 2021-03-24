#include <iostream>
using namespace std;
int main() {
  enum week { Mo, Tu, We, Th, Fr, Sa = 10, Su };
  enum week today;
  today = We;
  cout << today + 1 << " day" << endl;
  return 0;
}
