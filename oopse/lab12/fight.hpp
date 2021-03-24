template<class T1, class T2>
void fight(T1& char1, T2& char2) {
  if(char1.get_strength() > char2.get_strength()) {
    char1.get_exp() += char2.get_exp();
    if(char2.get_exp() > 0) {
      char2.get_exp() -= 1;
    }
    std::cout << char1.get_name() << " won and earned " << char2.get_exp() << "exp" << std::endl;
  } else if(char1.get_strength() < char2.get_strength()) {
    char2.get_exp() += char1.get_exp();
    if(char1.get_exp() > 0) {
      char1.get_exp() -= 1;
    }
    std::cout << char2.get_name() << " won and earned " << char1.get_exp() << "exp" << std::endl;
  }
}