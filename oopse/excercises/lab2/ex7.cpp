#include <iostream>
#include <string>
using namespace std;
main() {
  string text;
  cout << "Write a sentence with spaces between words: " << endl;
  getline(cin, text);
  cout << "\nThis is your string:\t " << text << endl;
  return 0;
}
