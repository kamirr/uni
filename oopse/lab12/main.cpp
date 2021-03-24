#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <algorithm>
#include <vector>

#include "ui.hpp"
#include "character.hpp"
#include "hero.hpp"

int main() {
  const std::array<std::string, 6> cmds = {"create", "list", "show", "load", "save", "monsters"};
  std::vector<Character> characters;

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
      std::cout << "Created character:" << std::endl;
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
      ui_monsters(characters);
    }
  }

  std::cout << std::endl;
  return 0;
}
