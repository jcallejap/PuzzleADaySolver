#ifndef BOARDS_STACK_2023_09_10_
#define BOARDS_STACK_2023_09_10_

#include <algorithm>
#include <vector>

#include "Board.h"

/*
 * This class represents a board stack.
 * The final board is the superposition of every board on the stack.
 * If we convert a piece to a board, we can just use this stack to add pieces to
 * a board and remove them if they are not compatible.
 */

class BoardsStack {
 public:  // Constructor
  BoardsStack(std::initializer_list<std::pair<size_t, size_t>>
                  occupied_squares) noexcept {
    // We add a first board with the known holes
    m_boards.push_back({{0, 6}, {1, 6}, {6, 3}, {6, 4}, {6, 5}, {6, 6}}); 
    for (const auto& pair : occupied_squares) {
      m_boards.back().mark(pair.first, pair.second, true);
    }
  }

 public:
  void pushBoard(const Board& table) { m_boards.push_back(table); }
  void popBoard() noexcept { m_boards.pop_back(); }
  bool isMarked(size_t row, size_t col) const {
    return std::any_of(
        begin(m_boards), end(m_boards),
        [row, col](const Board& table) { return table.isMarked(row, col); });
  }
  size_t getBoardThatCovers(size_t row, size_t col) const {
    for (size_t i = 0; i < m_boards.size(); ++i) {
      if (m_boards[i].isMarked(row, col)) {
        return i;
      }
    }
    return -1;
  }
  bool isCompatible(const Board& table) const {
    for (size_t row = 0; row < 7; ++row) {
      for (size_t col = 0; col < 7; ++col) {
        if (table.isMarked(row, col) && isMarked(row, col)) {
          return false;
        }
      }
    }
    return true;
  }
  std::tuple<size_t, size_t> firstNonMarked() const {
    for (size_t row = 0; row < 7; ++row) {
      for (size_t col = 0; col < 7; ++col) {
        if (!isMarked(row, col)) {
          return {row, col};
        }
      }
    }
    return {7, 7};
  }

 private:
  std::vector<Board> m_boards;
};

template <typename O>
static O& operator<<(O& o, const BoardsStack& board) {
  for (size_t row = 0; row < 7; ++row) {
    for (size_t col = 0; col < 7; ++col) {
      auto index = board.getBoardThatCovers(row, col);
      char txt = static_cast<char>((index < 10 ? ('0' + index) : '-'));
      o << txt;
    }
    o << std::endl;
  }
  return o;
}

#endif  // BOARDS_STACK_2023_09_10_
