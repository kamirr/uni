#ifndef heroes_hpp
#define heroes_hpp

#include <string>
#include <random>
#include "character.hpp"

class Monster : public Character {
public:
  Monster() {
    const std::string prefs[] = {"small", "large", "angry", "tenacious", "cute"};
    const std::string sufs[] = {"duck", "piano", "goblin", "dwarf", "spider"};

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<> stat_dist(1, 10), name_dist(0,4);

    this->name = prefs[name_dist(rng)] + "_" + sufs[name_dist(rng)];
    this->strength = stat_dist(rng);
    this->dexterity = stat_dist(rng);
    this->endurance = stat_dist(rng);
    this->intelligence = stat_dist(rng);
    this->charisma = stat_dist(rng);
  }
};

#endif