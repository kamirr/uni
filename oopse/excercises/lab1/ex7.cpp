#include <iostream>
using namespace std;

int main() {
  int i=0, ile=0;
  cout << "Wprowadz liczbe podsystemow: ";
  cin >> ile;
  cout << endl;

  cout << "Rozpoczynam skanowanie podsystemow" << endl;
  for (i = 1; i <= ile; i++) {
    cout << "Podsystem " << i << " przeskanowany" << endl;
  }

  cout << "Operacja zakonczona pomyslnie \n";

  return 0;
}
