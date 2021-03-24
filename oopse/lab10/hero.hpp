#ifndef hero_hpp
#define hero_hpp

#include "character.hpp"

class Hero {
public:
  virtual void inc_stat() = 0;
};

class Mage: public Hero {
  Character &chr;

public:
  Mage(Character& chr)
    :chr{chr}
  { }

  void inc_stat() {
    this->chr.intelligence += 1;
  }
};

class Warrior: public Hero {
  Character &chr;

public:
  Warrior(Character& chr)
    :chr{chr}
  { }

  void inc_stat() {
    this->chr.endurance += 1;
  }
};

class Berserker: public Hero {
  Character &chr;

public:
  Berserker(Character& chr)
    :chr{chr}
  { }

  void inc_stat() {
    this->chr.strength += 1;
  }
};

class Thief: public Hero {
  Character &chr;

public:
  Thief(Character& chr)
    :chr{chr}
  { }

  void inc_stat() {
    this->chr.dexterity += 1;
  }
};

#endif