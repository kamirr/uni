#include <iostream>
using namespace std;

int main() {
  float marks[5], lp[5];
  float meanval = 0;
  int i;

  marks[0] = 3;
  marks[1] = 5;
  marks[2] = 4;
  marks[3] = 3;
  marks[4] = 2;
  for (i = 0; i < 5; i++)
    meanval += marks[i];
  meanval /= 5;
  for (i = 0; i < 5; i++)
    lp[i] = i + 1;
  cout << "List of marks: " << endl;
  for (i = 0; i < 5; i++) {
    cout << "\t Mark nr. " << lp[i] << ". ";
    cout << marks[i] << endl;
  }
  cout << "Mean value of the marks: " << meanval << endl;
  return 0;
}
