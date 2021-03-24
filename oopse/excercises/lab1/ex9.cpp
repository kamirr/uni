#include <iostream>
using namespace std;

float polekwadratu (float bok1, float bok2);

int main() {
  float a, b, pole;
  cout << "Podaj dlugosc pierwszego boku: ";
  cin >> a;

  cout << endl << "Podaj dlugosc drugiego boku: ";
  cin >> b;
  cout << endl;

  cout << "Twoj prostokat posiada boki o dlugosci: a = " << a;
  cout << ", b = " << b;
  cout << endl;

  pole = polekwadratu(a,b);

  cout << "Pole Twojego prostokata wynosi: " << pole << endl;

  return 0;
}

float polekwadratu (float bok1, float bok2) {
  float wynik;
  wynik = bok1 * bok2;
  cout << "Obliczam pole...\n\n";

  return wynik;
}
