#include <iostream>
using namespace std;
main() {
  int board[10][10];
  int i, j;
  for (i = 0; i < 10; i++)
    for (j = 0; j < 10; j++)
      board[i][j] = 0;
  board[3][6] = 1;
  board[8][3] = 1;
  board[2][5] = 1;
  for (i = 0; i < 10; i++)
    for (j = 0; j < 10; j++)
      if (board[i][j])
        cout << "Ships are on following fields: [" << i << "]"
             << "[" << j << "]" << endl;
  return 0;
}
