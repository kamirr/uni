#include <iostream>

int main() {
  std::cout << "Obliczmy pole kwadratu\n"
            << "W tym celu bedziemy potrzebowac dlugosci boku a\n"
            << "niestety program nie posiada jeszcze zadnej zmiennej.\n"
            << "Podaj dlugosc boku kwadratu: ";

  int dlugosc;
  std::cin >> dlugosc;
  std::cout << "\n";

  int p;
  p = dlugosc * dlugosc;

  std::cout << "Pole kwadratu wynosi: " << p << "\n";

  return 0;
}
