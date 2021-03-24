#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <algorithm>
#include <vector>

class Hero {
//no reason to encapsulate character properties
public:
  std::string name;
  int strength;
  int dexterity;
  int endurance;
  int intelligence;
  int charisma;

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
};

Hero ui_create() {
  std::cout << "Enter space-separated: name, strength, dexterity, endurance, intelligence and charisma\n"
    << "E.g. Pudzian 6 1 5 9 3" << std::endl;
  
  return Hero{std::cin};
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

void ui_save(const std::vector<Hero> &chrs) {
  std::string name;
  auto selected = chrs.end();
  while(selected == chrs.end()) {
    std::cout << "Enter character name: ";
    std::cin >> name;

    selected = std::find_if(chrs.begin(), chrs.end(), [&](const auto &c) { return c.name == name; });
  }

  std::ofstream file{name};
  (*selected).save(file);
}

int main() {
  const std::array<std::string, 3> cmds{{"create", "load", "save"}};
  std::vector<Hero> characters;

  std::string cmd;
  std::cout
    << "create - character creator\n"
    << "load - loads character\n"
    << "save - saves character\n"
    << "Ctrl+D to exit" << std::endl;

  while(std::cout << "$ ", std::cin >> cmd) {
    if(std::find(cmds.begin(), cmds.end(), cmd) == cmds.end()) {
      std::cout << "invalid command: `" << cmd << "`" << std::endl;
      continue;
    }

    if(cmd == "create") {
      characters.push_back(ui_create());
    } else if(cmd == "load") {
      characters.push_back(ui_load());
    } else if(cmd == "save") {
      ui_save(characters);
    }
  }

  std::cout << std::endl;
  return 0;
}
