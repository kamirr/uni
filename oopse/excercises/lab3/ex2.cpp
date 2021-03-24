#include <iostream>
using namespace std;
main() {
  int masa = 135, *wag, wyb = 0;
  float km = 14.96, *moc;
  void *wsk;
  moc = &km;
  wag = &masa;
  cout << "Dobierz motocykl o pojemnosci do 125cm^3 dla siebie\n"
       << "Jaki parametr jest dla Ciebie najistotniejszy?\n"
       << "\t1. Masa\n"
       << "\t2. Moc silnika\n"
       << "Wprowadz swoj wybor: ";
  cin >> wyb;
  if (wyb == 1) {
    wsk = wag;
    cout << "Motocykl dla Ciebie to: Yamacha Virago 125\n"
         << "Jego masa to: " << *(int *)wsk << "Kg" << endl;
  }
  if (wyb == 2) {
    wsk = moc;
    cout << "Motocykl dla Ciebie to: Honda VT Shadow 125\n"
         << "Jego moc to: " << *(float *)wsk << "KM" << endl;
  }
  return 0;
}
