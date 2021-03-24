#include <iostream>
using namespace std;

int main() {
  int i = 3;

  switch(i) {
    case 1: cout << "Wartosc jest rowna 1 \n"; break;
    case 2: cout << "Wartosc jest rowna 2 \n"; break;
    case 3: cout << "Wartosc jest rowna 3 \n"; break;
    case 4: cout << "wartosc jest rowna 4 \n"; break;
    default: cout << "wartosc jest inna niz 1,2,3,4 \n";
  }

  return 0;
}
