#ifndef ui_hpp
#define ui_hpp

#include <string>
#include <algorithm>
#include <unordered_map>
#include <vector>

#include "character.hpp"
#include "monster.hpp"
#include "hero.hpp"

Character ui_create() {
  std::string name;
  const std::string stat_names[] = {"strength", "dexterity", "endurance", "intelligence", "charisma"};
  std::unordered_map<std::string, int> stats;
  int stat_sum = 0;

  std::cout << "Name: ";
  std::cin >> name;

  std::cout << "Stats must sum to at most 10 and be in range 0-10" << std::endl;
  while(true) {
    for(const auto &stat: stat_names) {
      int tmp;

      std::cout << stat << ": ";
      std::cin >> tmp;
      while(tmp > 10 || tmp < 0) {
        std::cout << "Not in range 0-10!: ";
        std::cin >> tmp;
      }

      stats[stat] = tmp;
    }

    const auto sum = std::accumulate(
      stats.begin(),
      stats.end(),
      0,
      [](const auto acc, const auto& p) { return acc + p.second; }
    );

    if(sum <= 10) {
      break;
    } else {
      std::cout << "Sum of stats greater than 10: " << sum << "!" << std::endl;
    }
  }

  return Character{name, stats["strength"], stats["dexterity"], stats["endurance"], stats["intelligence"], stats["charisma"], 0};
}

Character ui_load() {
  std::ifstream file;
  std::string name;
  std::cout << "Enter character name: ";
  for(;;) {
    std::cin >> name;
    file.open(name);
    if(!file.good()) {
      std::cout << "Couldn't open character file `" << name << "`" << std::endl;
      file = std::ifstream{};
    } else {
      break;
    }
  }

  return Character{file};
}

void ui_list(const std::vector<Character> &chrs) {
  std::cout << "Characters: " << std::endl;
  for(const auto &chr: chrs) {
    std::cout << "> " << chr.get_name() << std::endl;
  }
}

void ui_show(const std::vector<Character> &chrs) {
  ui_list(chrs);

  std::string name;
  auto selected = chrs.end();
  while(selected == chrs.end()) {
    std::cout << "Enter character name: ";
    std::cin >> name;

    selected = std::find_if(
      chrs.begin(),
      chrs.end(),
      [&](const auto &c) {
        return c.get_name() == name;
      }
    );
  }

  selected->pretty_print();
}

void ui_save(const std::vector<Character> &chrs) {
  ui_list(chrs);

  std::string name;
  auto selected = chrs.end();
  while(selected == chrs.end()) {
    std::cout << "Enter character name: ";
    std::cin >> name;

    selected = std::find_if(
      chrs.begin(),
      chrs.end(),
      [&](const auto &c) {
        return c.get_name() == name;
      }
    );
  }

  std::ofstream file{name};
  selected->save(file);
}

void ui_monsters() {
  /* default constructor randomizes stats */
  const Monster monsters[5];
  std::string ans;

  for(const auto &m: monsters) {
    m.pretty_print();
  }

  std::cout << "Save? [y/n]: ";
  std::cin >> ans;
  while(ans != "y" && ans != "Y" && ans != "n" && ans != "N") {
    std::cout << "[y/n]: ";
    std::cin >> ans;
  }

  if(ans == "y" || ans == "Y") {
    std::ofstream ofile;
    ofile.open("monsters");
    for(const auto &m: monsters) {
      m.save(ofile);
    }
  }
}

#endif