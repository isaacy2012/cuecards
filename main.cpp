#include <iostream>
#include <random>
#include <algorithm>
#include "model.hpp"
#include "example_cards.hpp"

void print_card_outline(std::size_t length, char decoration) {
  for (int i = 0; i < length; ++i) {
    std::cout << decoration;
  }
  std::cout << std::endl;
}

size_t str_visual_length(const std::string& s) {
  if (s.empty()) return 0;
  auto leading_newline_idx = 0;
  char first = s.at(leading_newline_idx);
  while (first == '\n') {
    first = s.at(++leading_newline_idx);
  }

  auto idx = s.find_first_of('\n', leading_newline_idx) - leading_newline_idx;
  return idx == std::string::npos ? s.length() : idx + 1;
}

void show_frontside(const card &c) {
  print_card_outline(str_visual_length(c.q_str), '.');
  std::cout << c.q_str << std::endl;
  print_card_outline(str_visual_length(c.q_str), '.');
}

void show_backside(const card &c) {
  std::cout << c.a_str << std::endl;
}

void await_newline() {
  std::cin.sync();
  std::cin.get();
}

int main() {
  std::random_device rd;
  std::default_random_engine re{rd()};
  std::shuffle(cards.begin(), cards.end(), re);

  int n_correct{0};
  int n_total{0};
  char correct_char{};
  for (auto &qu: cards) {
    show_frontside(qu);
    std::cout << "Press RETURN to flip card" << std::endl;
    await_newline();
    show_backside(qu);

    std::cout << "Correct? (y)es or (n)o" << std::endl;
    std::cin >> correct_char;
    std::cout << "----------------" << std::endl;
    if (correct_char == 'y') {
      ++n_correct;
    }
    ++n_total;
    std::cout << n_correct << " / " << n_total << std::endl;
    std::cout << "================" << std::endl;
  }

  std::cout << "You scored " << n_correct << " / " << n_total << std::endl;
  return 0;
}
