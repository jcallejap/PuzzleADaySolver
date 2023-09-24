#ifndef BOARD_2023_09_10_
#define BOARD_2023_09_10_

#include <algorithm>
#include <array>
#include <bitset>
#include <iostream>

/*
 * This class represents a 7x7 board where each square can be empty (false) or
 * occupied (true).
 */
class Board {
 public:  // Constructor
  Board() noexcept {
    for_each(begin(m_table), end(m_table), [](auto& row) { row.reset(); });
  }
  Board(std::initializer_list<std::pair<size_t, size_t>>
            occupied_squares) noexcept {
    for_each(begin(m_table), end(m_table), [](auto& row) { row.reset(); });
    for (const auto& square : occupied_squares) {
      m_table[square.first][square.second] = true;
    }
  }

 public:  // Manage squares
  void mark(size_t row, size_t col, bool value) noexcept {
    m_table[row][col] = value;
  }
  bool isMarked(size_t row, size_t col) const noexcept {
    return m_table[row][col];
  }

 private:  // Board squares
  std::array<std::bitset<7>, 7> m_table;
};

template <typename O>
static O& operator<<(O& o, const Board& table) {
  for (int row = 0; row < 7; ++row) {
    for (int col = 0; col < 7; ++col) {
      o << (table.isMarked(row, col) ? 'x' : 'o');
    }
    o << std::endl;
  }
  return o;
}

#endif  // BOARD_2023_09_10_
