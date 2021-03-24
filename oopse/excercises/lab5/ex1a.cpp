#include <iostream>
using namespace std;
int main() {
  enum week { Mo, Tu, We, Th, Fr, Sa = 10, Su } WeekDay;
  WeekDay = Mo;
  cout << "Value for Monday = " << WeekDay << endl;
  WeekDay = Tu;
  cout << "Value for Tuesday = " << WeekDay << endl;
  WeekDay = We;
  cout << "Value for Wednesday = " << WeekDay << endl;
  WeekDay = Th;
  cout << "Value for Thursday = " << WeekDay << endl;
  WeekDay = Fr;
  cout << "Value for Fiday = " << WeekDay << endl;
  WeekDay = Sa;
  cout << "Value for Saturday = " << WeekDay << endl;
  WeekDay = Su;
  cout << "Value for Sunday = " << WeekDay << endl;
  return 0;
}
