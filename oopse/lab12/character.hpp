#ifndef character_hpp
#define character_hpp

#include <string>
#include <ostream>

class Mage;
class Warrior;
class Berserker;
class Thief;

class Character {
protected:
  std::string name;
  int strength;
  int dexterity;
  int endurance;
  int intelligence;
  int charisma;
  int experience;

  /* only derived classes should use the empty constructor */
  Character() { }

public:
  Character(std::string name, int strength, int dexterity, int endurance, int intelligence, int charisma, int exp) {
    this->name = name;
    this->strength = strength;
    this->dexterity = dexterity;
    this->endurance = endurance;
    this->intelligence = intelligence;
    this->charisma = charisma;
    this->experience = exp;
  }

  Character(std::istream &is) {
    is >> name
      >> strength
      >> dexterity
      >> endurance
      >> intelligence
      >> charisma
      >> experience;
  }

  void save(std::ostream& os) const {
    os << name << " "
      << strength << " "
      << dexterity << " "
      << endurance << " "
      << intelligence << " "
      << charisma << " "
      << experience << "\n";
  }

  const std::string& get_name() const {
    return this->name;
  }

  int get_strength() const {
    return this->strength;
  }

  int& get_exp() {
    return this->experience;
  }

  void pretty_print() const {
    std::cout << "Name:       『" << this->name << "』\n"
      << "Strength:     " << this->strength << "\n"
      << "Dexterity:    " << this->dexterity << "\n"
      << "Endurance:    " << this->endurance << "\n"
      << "Intelligence: " << this->intelligence << "\n"
      << "Charisma:     " << this->charisma << "\n"
      << "Experience:   " << this->experience << std::endl;
  }

  friend class Mage;
  friend class Warrior;
  friend class Berserker;
  friend class Thief;
};

#endif