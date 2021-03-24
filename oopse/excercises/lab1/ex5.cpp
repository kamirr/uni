#include <iostream>
using namespace std;

int main () {
  int wiek=0, lata=0;
  cout << "Ile masz lat? \n";
  cin >> wiek;
  cout << endl;

  while (wiek < 24) {
    wiek++;
    lata++;
  }

  if (wiek < 25) {
    cout << "Teoretycznie za " << lata;
    if (lata == 1)
      cout << " rok";
    else if (lata > 1 && lata < 5)
      cout << " lata";
    else if (lata >= 5 || lata==0)
      cout << " lat";

    cout << " skonczysz studia. \n";
  }
  else
    cout << "taki stary, a jeszcze studiuje... \n";

  return 0;
}
