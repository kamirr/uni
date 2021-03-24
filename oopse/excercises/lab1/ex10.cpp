#include <iostream>
using namespace std;

void zer (int wart, int &ref);
void nzer (int wart, int ref);

int main () {
  int a = 44, b = 77;

  cout << "Przed wywolaniem funkcji nzer:\n";
  cout << "a = " << a << ", b = " << b << endl;

  nzer (a,b);

  cout << "Po powrocie z funkcji nzer:\n";
  cout << "a = " << a << ", b = " << b << endl;

  cout << "Przed wywolaniem funkcji zer:\n";
  cout << "a = " << a << ", b = " << b << endl;
  
  zer (a,b);

  cout << "Po powrocie z funkcji zer:\n";
  cout << "a = " << a << ", b = " << b << endl;

  return 0;
}

void zer (int wart, int &ref) {
  cout << "\tW funkcji zer przed zerowaniem: \n";
  cout << "\twart = " << wart << ", ref = " << ref << endl;
  wart = 0;
  ref = 0;

  cout << "\tW funkcji zer po zerowaniu: \n";
  cout << "\twart = " << wart << ", ref = "<< ref << endl;
}

void nzer (int wart, int ref) {
  cout << "\tW funkcji nzer przed zerowaniem: \n";
  cout << "\twart = " << wart << ", ref = " << ref << endl;
  wart = 0;
  ref = 0;

  cout << "\tW funkcji nzer po zerowaniu: \n";
  cout << "\twart = " << wart << ", ref = "<< ref << endl;
}
