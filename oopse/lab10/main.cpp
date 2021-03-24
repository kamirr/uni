#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <algorithm>
#include <vector>
#include <random>
#include <unordered_map>

class Mage;
class Warrior;
class Berserker;
class Thief;

class Hero {
protected:
  std::string name;
  int strength;
  int dexterity;
  int endurance;
  int intelligence;
  int charisma;

  /* only derived classes should use the empty constructor */
  Hero() { }

public:
  Hero(std::string name, int strength, int dexterity, int endurance, int intelligence, int charisma) {
    this->name = name;
    this->strength = strength;
    this->dexterity = dexterity;
    this->endurance = endurance;
    this->intelligence = intelligence;
    this->charisma = charisma;
  }

  Hero(std::istream &is) {
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

class Mage {
  Hero &chr;

public:
  Mage(Hero& chr)
    :chr{chr}
  { }

  void inc_intelligence() {
    this->chr.intelligence += 1;
  }
};

class Warrior {
  Hero &chr;

public:
  Warrior(Hero& chr)
    :chr{chr}
  { }

  void inc_endurance() {
    this->chr.endurance += 1;
  }
};

class Berserker {
  Hero &chr;

public:
  Berserker(Hero& chr)
    :chr{chr}
  { }

  void inc_strength() {
    this->chr.strength += 1;
  }
};

class Thief {
  Hero &chr;

public:
  Thief(Hero& chr)
    :chr{chr}
  { }

  void inc_dexterity() {
    this->chr.dexterity += 1;
  }
};

class Monster : public Hero {
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

Hero ui_create() {
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

  return Hero{name, stats["strength"], stats["dexterity"], stats["endurance"], stats["intelligence"], stats["charisma"]};
}

Hero ui_load() {
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

  return Hero{file};
}

void ui_list(const std::vector<Hero> &chrs) {
  std::cout << "Characters: " << std::endl;
  for(const auto &chr: chrs) {
    std::cout << "> " << chr.get_name() << std::endl;
  }
}

void ui_show(const std::vector<Hero> &chrs) {
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

void ui_save(const std::vector<Hero> &chrs) {
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

int main() {
  const std::array<std::string, 6> cmds = {"create", "list", "show", "load", "save", "monsters"};
  std::vector<Hero> characters;

  std::string cmd;
  std::cout
    << "create - character creator\n"
    << "list - lists characters\n"
    << "show - shows character details\n"
    << "load - loads character\n"
    << "save - saves character\n"
    << "monsters - monster randomizer\n"
    << "Ctrl+D to exit" << std::endl;

  while(std::cout << "$ ", std::cin >> cmd) {
    if(std::find(cmds.begin(), cmds.end(), cmd) == cmds.end()) {
      std::cout << "invalid command: `" << cmd << "`" << std::endl;
      continue;
    }

    if(cmd == "create") {
      const auto new_chr = ui_create();
      std::cout << "Created Hero:" << std::endl;
      new_chr.pretty_print();
      characters.push_back(new_chr);
    } else if(cmd == "list") {
      ui_list(characters);
    } else if(cmd == "show") {
      ui_show(characters);
    } else if(cmd == "load") {
      characters.push_back(ui_load());
    } else if(cmd == "save") {
      ui_save(characters);
    } else if(cmd == "monsters") {
      ui_monsters();
    }
  }

  std::cout << std::endl;
  return 0;
}
