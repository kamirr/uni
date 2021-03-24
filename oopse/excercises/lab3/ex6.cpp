#include <iostream>
using namespace std;
float srednia(float a, float tab[]);
main() {
  int rozm = 0, i;
  float *wsk, wynik;
  cout << "Program obliczy srednia arytmetyczna kilku liczb\n";
  cout << "Podaj ile liczb chcesz wprowadzic w celu obliczenia"
       << " sredniej: ";
  cin >> rozm;
  wsk = new float[rozm];
  for (i = 0; i < rozm; i++) {
    cout << "Podaj wartosc dla " << i + 1 << " elementu: ";
    cin >> wsk[i];
    cout << endl;
  }
  cout << "Policze srednia dla nastepujacych liczb: ";
  for (i = 0; i < rozm; i++) {
    cout << wsk[i] << ", ";
  }
  cout << endl;
  wynik = srednia(rozm, wsk);
  cout << "Srednia powyzszych liczb wynosi: " << wynik << endl;
  delete wsk;
  wsk = NULL;
  return 0;
}
float srednia(float a, float tab[]) {
  int b;
  float sred;
  for (b = 0; b < a; b++) {
    sred += tab[b];
  }
  sred /= a;
  return sred;
}
