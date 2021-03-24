#ifndef hero_hpp
#define hero_hpp

#include "character.hpp"

#include <cmath>

class Hero {
protected:
  Character &chr;
  int level;

  Hero(Character chr)
    : chr{chr},
      level{0}
  {}

public:
  virtual void inc_stat() = 0;

  void update() {
    this->level = log2(chr.get_exp() + 1) + 1;
  }
};

class Mage: public Hero {
public:
  Mage(Character& chr)
    :Hero{chr}
  { }

  void inc_stat() {
    this->chr.intelligence += 1;
  }
};

class Warrior: public Hero {
public:
  Warrior(Character& chr)
    :Hero{chr}
  { }

  void inc_stat() {
    this->chr.endurance += 1;
  }
};

class Berserker: public Hero {
public:
  Berserker(Character& chr)
    :Hero{chr}
  { }

  void inc_stat() {
    this->chr.strength += 1;
  }
};

class Thief: public Hero {
public:
  Thief(Character& chr)
    :Hero{chr}
  { }

  void inc_stat() {
    this->chr.dexterity += 1;
  }
};

#endif