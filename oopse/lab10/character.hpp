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

  /* only derived classes should use the empty constructor */
  Character() { }

public:
  Character(std::string name, int strength, int dexterity, int endurance, int intelligence, int charisma) {
    this->name = name;
    this->strength = strength;
    this->dexterity = dexterity;
    this->endurance = endurance;
    this->intelligence = intelligence;
    this->charisma = charisma;
  }

  Character(std::istream &is) {
    is >> name
      >> strength
      >> dexterity
      >> endurance
      >> intelligence
      >> charisma;
  }

  void save(std::ostream& os) const {
    os << name << " "
      << strength << " "
      << dexterity << " "
      << endurance << " "
      << intelligence << " "
      << charisma << "\n";
  }

  const std::string& get_name() const {
    return this->name;
  }

  void pretty_print() const {
    std::cout << "Name:       『" << this->name << "』\n"
      << "Strength:     " << this->strength << "\n"
      << "Dexterity:    " << this->dexterity << "\n"
      << "Endurance:    " << this->endurance << "\n"
      << "Intelligence: " << this->intelligence << "\n"
      << "Charisma:     " << this->charisma << std::endl;
  }

  friend class Mage;
  friend class Warrior;
  friend class Berserker;
  friend class Thief;
};

#endif