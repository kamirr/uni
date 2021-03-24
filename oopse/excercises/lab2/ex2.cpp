#include <iostream>
using namespace std;
float earings(float pln, int hours[]);
main() {
  int week[7];
  int i;
  float money, earing;
  cout << "\tWeekly earings calculator.\n"
       << "How much you earn in an hour: ";
  cin >> money;
  cout << endl;
  for (i = 0; i < 7; i++) {
    cout << "How many hours you plan to work on";
    if (i == 0)
      cout << " Monday"if(i == 1) cout << " Tuesday: ";
    if (i == 2)
      cout << " Wednesday: ";
    if (i == 3)
      cout << " Thursday: ";
    if (i == 4)
      cout << " Friday: ";
    if (i == 5)
      cout << " Saturday: ";
    if (i == 6)
      cout << " Sunday: ";
    cin >> week[i];
    cout << endl;
  }
  cout << endl;
  earing = earings(money, week);
  cout << "You are going to earn: " << earing << " PLN\n";
  return 0;
}
float earings(float pln, int hours[]) {
  int lhr = 0, a;
  for (a = 0; a < 7; a++)
    lhr += hours[a];
  return (lhr * pln);
}
