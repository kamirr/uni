#include <fstream>
#include <iostream>
using namespace std;
int main() {
  fstream file;
  file.open("file.txt", ios::in | ios::out);
  if (file.good() == true) {
    cout << "File access granted!" << endl;
    file << "This text will show in the file" << endl;
    string inscr, text;
    text = "this is a string, that will be placed in the file\n";
    file << text;
    cout << "Enter any string, it will be copied into "
         << " the file" << endl;
    getline(cin, inscr);
    file.write(&inscr[0], inscr.length());
    // reading from file
    /// moving the cursor by 3 bytes towards the beginning of the file
    file.seekg(+3, std::ios_base::beg);
    string inscr1, inscr2;
    file >> inscr1;
    cout << "First line:" << endl << inscr1 << endl;
    getline(file, inscr2);
    cout << "Next line from the file: " << endl << inscr2 << endl;
    char temp[10];
    file.read(temp, 10);
    cout << "another line from file: " << endl;
    for (int i = 0; i < 10; i++)
      cout << temp[i];
    cout << endl;
    file.close();
  } else
    cout << "File access forbidden " << endl;
  return (0);
}
