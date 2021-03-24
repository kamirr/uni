#include <iostream>
#include <string>
using namespace std;
main() {
  string text, text1, text2, text3;
  char space = ’ ’;
  cout << "Enter a string " << endl;
  cin >> text1 >> text2 >> text3;
  cout << "\nThis is your string:\t " << text1 << " " << text2 << " " << text3
       << endl; // Connecting strings:
  text = text1 + text2 + text3;
  cout << "\nThis is your string::\t " << text << endl; // adding spaces
  text = text1 + " " + text2 + " " + text3;
  cout << "\nThis is your string:\t " << text << endl;
  text = text1 + space + text2 + space + text3;
  cout << "\nThis is your string:\t " << text
       << endl; // to clear the content of a string
  text2.clear();
  cout << "\nThis is your string after clearing one element"
       << ":\t " << text1 << " " << text2 << " " << text3 << endl;
  return 0;
}
