#include <iostream>
using namespace std;
float earnings(float pln, int hours[][4]);
main() {
  int week[7][4];
  int i, j;
  float money, earning;
  cout << "\tMonthly earings calculator.\n"
       << "How much you earn in an hour: ";
  cin >> money;
  cout << endl;
  for (j = 0; j < 4; j++) {
    cout << "Week " << j + 1 << endl;
    for (i = 0; i < 7; i++) {
      cout << "How many hours you plan to work on";
      if (i == 0)
        cout << " Monday: ";
      if (i == 1)
        cout << " Tuesday: ";
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
      cin >> week[i][j];
      cout << endl;
    }
  }
  cout << endl;
  earning = earnings(money, week);
  cout << "You will earn: " << earning << " PLN"
       << " in fourweeks\n";
  return 0;
}
float earnings(float pln, int hours[][4]) {
  int lhr = 0, a, b;
  for (b = 0; b < 4; b++) {
    for (a = 0; a < 7; a++)
      lhr += hours[a][b];
  }
  return (lhr * pln);
}
