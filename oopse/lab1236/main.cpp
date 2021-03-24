#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <unordered_map>
#include <variant>
#include <optional>

struct product_t {
  std::string name;
  int in_stock;
  int price_gr;
};

enum class transaction_status_t {
  NORMAL, EXIT
};

enum class special_op_t {
  EXIT, MODIFY_POOL
};

using product_idx_t = std::size_t;
using request_t = std::variant<special_op_t, product_idx_t>;
using money_pool_t = std::unordered_map<int, int>;

constexpr int denominations[] = {1000, 500, 200, 100, 50, 20, 10, 5, 2, 1};
constexpr std::size_t denominations_n = sizeof(denominations) / sizeof(denominations[0]);

bool valid_denomination(int n) {
  return std::find(std::begin(denominations), std::end(denominations), n) != std::end(denominations);
}

std::string str_gr(int money_gr) {
  const auto zl = std::string{} + std::to_string(money_gr/100) + "zl";
  const auto gr = std::string{} + std::to_string(money_gr%100) + "gr";
  if(money_gr < 100) {
    return gr;
  } else if(money_gr % 100 == 0) {
    return zl;
  } else {
    return zl + " " + gr;
  }
}

money_pool_t pool_add(money_pool_t mp1, const money_pool_t &mp2) {
  for(const std::pair<int, int> &p: mp2) {
    mp1[p.first] += p.second;
  }

  return std::move(mp1);
}

int pool_average(const money_pool_t &mp) {
  int total = 0;
  for(const auto den: denominations) {
    int count;
    try {
      count = mp.at(den);
    } catch(...) {
      count = 0;
    }
    total += count;
  }

  return total / denominations_n;
}

money_pool_t excessive_denominations(const money_pool_t &mp) {
  const auto avg = pool_average(mp);
  money_pool_t res;

  for(const auto &p: mp) {
    if(p.second >= avg*2) {
      res[p.first] = p.second - avg;
    }
  }

  return res;
}

std::optional<money_pool_t> calculate_rest(money_pool_t pool, int to_return, bool prioritize_excessive) {
  auto rest = money_pool_t{};

  if(prioritize_excessive) {
    //remove excessive denominations
    //if there's more than 2*average of a given denomination then attempt to
    //return up to (number-average) of them as rest first
    auto excessive = excessive_denominations(pool);
    for(const auto den: denominations) {
      while(to_return >= den && excessive[den] > 0 && pool[den] > 0) {
        to_return -= den;
        excessive[den] -= 1;
        pool[den] -= 1;
        rest[den] += 1;
      }
    }
  }

  //standard greedy rest calculation
  for(const auto den: denominations) {
    while(to_return >= den && pool[den] > 0) {
      pool[den] -= 1;
      rest[den] += 1;
      to_return -= den;
    }
  }

  if(to_return > 0) {
    return std::nullopt;
  }

  return {rest};
}

void export_pool(const money_pool_t &pool) {
  std::ofstream of;
  of.open("money_pool_save.txt");

  if(!of.is_open()) {
    std::cerr << "coudln't open money pool save file" << std::endl;
    std::exit(1);
  }

  for(const auto &p: pool) {
    of << p.second << " * " << str_gr(p.first) << std::endl;
  }
}

class vending_machine_t {
  std::vector<product_t> prods;
  money_pool_t money_pool;

  int find(const std::string &name) const;
  request_t ui_request() const;
  static int ui_num(int in_stock);
  void print() const;
  static money_pool_t parse_payment(std::string s);
  void payment(const int to_pay);
  void modify_pool();
public:
  vending_machine_t(const char* path);
  vending_machine_t() = delete;

  void save(const char* path) const;
  transaction_status_t transaction();
};

vending_machine_t::vending_machine_t(const char* path) {
  std::ifstream file;

  file.open(path);
  if(!file.is_open()) {
    std::cerr << "couldn't open `" << path << "`\n";
    std::exit(1);
  }

  std::string name, replenish;
  int in_stock, price_gr;
  while(file >> name >> in_stock >> price_gr >> replenish) {
    if(replenish == "replenish") {
      in_stock += 10;
    }

    this->prods.push_back({std::move(name), in_stock, price_gr});
  }

  for(const auto den: denominations) {
    this->money_pool[den] = 50;
  }
}

void vending_machine_t::save(const char* path) const {
 std::ofstream file;

  file.open(path);
  if(!file.is_open()) {
    std::cerr << "couldn't open `" << path << "`\n";
    std::exit(1);
  }

  for(const auto &p: this->prods) {
    file << p.name << " " << p.in_stock << " " << p.price_gr << " " << (p.in_stock == 0 ? "replenish" : "ok") << std::endl;
  }
}

int vending_machine_t::find(const std::string &name) const {
  const auto it = std::find_if(
    this->prods.begin(),
    this->prods.end(),
    [&](const auto p) { return p.name == name; }
  );  

  if(it == this->prods.end()) {
    return -1;
  } else {
    return it - this->prods.begin();
  }
}
 
request_t vending_machine_t::ui_request() const {
  std::string name;

  std::cout << "product name: ";
  std::cin >> name;
  while(this->find(name) == -1 && name != "exit" && name != "modify") {
    std::cout << "wrong name!: ";
    std::cin >> name;
  }

  if(name == "exit") {
    return {special_op_t::EXIT};
  } else if(name == "modify") {
    return {special_op_t::MODIFY_POOL};
  } else {
    return {this->find(name)};
  }
}

int vending_machine_t::ui_num(int in_stock) {
  int req;
  std::cout << "how many?: ";
  std::cin >> req;

  while(req > in_stock) {
    printf("not enough in stock!: ");
    std::cin >> req;
  }

  return req;
}

void vending_machine_t::print() const {
  std::cout << "================\n";
  std::cout << "Available products:\n";
  for(std::size_t i = 0; i < this->prods.size(); ++i) {
    if(this->prods[i].in_stock == 0) {
      continue;
    }

    std::cout << i+1 << ") "
              << this->prods[i].name
              << " (" << str_gr(this->prods[i].price_gr) << ")"
              << ": " << this->prods[i].in_stock
              << std::endl;
  }
}

money_pool_t vending_machine_t::parse_payment(std::string s) {
  money_pool_t res;
  int pos = 0;

  while ((pos = s.find(" ")) != std::string::npos) {
    std::string token = s.substr(0, pos);
    s.erase(0, pos + 1);

    const auto tl = token.size();

    if(tl < 2) {
      continue;
    }

    int mult;
    if(token[tl-2] == 'z' && token[tl-1] == 'l') {
      mult = 100;
    } else if(token[tl-2] == 'g' && token[tl-1] == 'r') {
      mult = 1;
    } else {
      std::cout << "invalid token: " << token << std::endl;
      continue;
    }

    token.erase(tl-2, 2);
    const auto val = std::atoi(token.c_str()) * mult;
    if(!valid_denomination(val)) {
      std::cout << "invalid denomination: " << str_gr(val) << std::endl;
      continue;
    }
    res[val] += 1;
  }

  return res;
}

void vending_machine_t::payment(const int to_pay) {
  std::string s;
  std::cin.ignore();
  
  for(;;) {
    std::cout << "Enter payment (e.g. 5zl 1zl 20gr 10gr 1gr to pay 6zl 31gr)" << std::endl;

    std::getline(std::cin, s);
    s = " " + s + " "; //delimiters

    const auto parsed = this->parse_payment(s);
    auto total = 0;
    for(const std::pair<int, int> &p: parsed) {
      total += p.first * p.second;
    }

    std::cout << "inserted " << str_gr(total) << ", required " << str_gr(to_pay) << std::endl;

    if(total < to_pay) {
      std::cout << "Not enough money" << std::endl;
      continue;
    }

    auto with_added = pool_add(this->money_pool, parsed);
    auto to_return = total - to_pay;
    auto maybe_rest = calculate_rest(with_added, to_return, true);
    // prioritizing excessive coins is a suboptimal strategy and may fail to produce a rest even
    // if there are coins to do so. If so, re-attempt the calculation only using the greedy algo.
    if(!maybe_rest.has_value()) {
      maybe_rest = calculate_rest(with_added, to_return, false);
    }
    if(!maybe_rest.has_value()) {
      std::cout << "Couldn't return rest, try inserting the exact price" << std::endl;
      continue;
    }

    auto rest = maybe_rest.value();

    std::cout << "rest: ";
    for(const auto den: denominations) {
      const auto count = rest[den];
      with_added[den] -= count;
      if(count > 0) {
        std::cout << count << "*" << str_gr(den) << " ";
      }
    }
    std::cout << std::endl;
    
    this->money_pool = with_added;
    break;
  }

  export_pool(this->money_pool);
} 

void vending_machine_t::modify_pool() {
  int diff;

  for(const auto den: denominations) {
    std::cout << "currently: " << this->money_pool[den] << "*" << str_gr(den) << std::endl;
    std::cout << "add/sub: ";
    std::cin >> diff;

    this->money_pool[den] += diff;
  }
}

transaction_status_t vending_machine_t::transaction() {
  this->print();
  const auto req = this->ui_request();

  if(std::holds_alternative<special_op_t>(req)) {
    const auto op = std::get<special_op_t>(req);
    if(op == special_op_t::EXIT) {
      return transaction_status_t::EXIT;
    } else if(op == special_op_t::MODIFY_POOL) {
      this->modify_pool();
      return transaction_status_t::NORMAL;
    }
  }

  const int idx = std::get<product_idx_t>(req);
  const int num = this->ui_num(this->prods[idx].in_stock);
  this->prods[idx].in_stock -= num;

  this->payment(this->prods[idx].price_gr * num);

  return transaction_status_t::NORMAL;
}

int main() {
  vending_machine_t vm{"stock.txt"};

  auto status = transaction_status_t::NORMAL;
  while(status != transaction_status_t::EXIT) {
    status = vm.transaction();
    vm.save("stock.txt");
  }

  return 0;
}
