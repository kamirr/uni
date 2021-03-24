#include <iostream>
using namespace std;
void pizza(int *lpi, float *gotowka);
main() {
  int liczba_pizzy = 0;
  float pln = 134.28;
  cout << "Obecnie posiadasz " << liczba_pizzy << " pizze.\n";
  cout << "Masz przy sobie " << pln << " PLN." << endl;
  cout << "Czas zamowic pizze!" << endl;
  pizza(&liczba_pizzy, &pln);

  cout << "Twoja dostawa nadeszla\n";
  cout << "Teraz posiadasz " << liczba_pizzy << " pizze.\n";
  cout << "Zostalo Ci " << pln << " PLN." << endl;
  return 0;
}
void pizza(int *lpi, float *gotowka) {
  *lpi = 2;
  *gotowka = 62.47;
}
