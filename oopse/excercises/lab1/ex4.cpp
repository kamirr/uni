#include <iostream>

int main(){
  int a=1, b=2, c=3;
  
  if (a)
    std::cout << "Zmienna a jest rozna od 0 a jej wartosc"
              << " to: " << a << "\n";

  if (a > b)
    std::cout << "to sie nie wyswietli\n";
  else
    std::cout << a << " jest mniejsze od " << b << "\n";

  if (c < b)
    std::cout << "to sie nie wyswietli\n";
  else if (b = 2) {
    b++;
    std::cout<< "b = " << b << "\n";
  }

  return 0;
}
