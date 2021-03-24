#include <iostream>
using namespace std;
int area(int a) { return (a * a); }
int area(int a, int b) { return (a * b); }
int main() {
  int sideA = 2;
  int sideB = 4;
  cout << "There is a rectangle in which two squares areinscribed" << endl;
  cout << "The area of the square = " << area(sideA) << endl;
  cout << "The area of the rectangle = " << area(sideA, sideB) << endl;
  return 0;
}
