#ifndef PIECE_2023_09_10_
#define PIECE_2023_09_10_

#include <bitset>
#include <optional>

/*
 *This object represent a 4x4 piece
 */
class Piece {
 public:
  Piece(int index, const std::bitset<16>& piece) : m_index{index} {
    for (size_t row = 0; row < 4; ++row) {
      for (size_t col = 0; col < 4; ++col) {
        m_piece.set(4 * row + col, piece.test(4 * col + row));
      }
    }
  }

 public:
  // Convert this piece to a board, given a top-left position, a rotation and
  // if it is reversed
  std::optional<Board> getTable(int row_inc, int col_inc, int rotation,
                                bool reverse) const {
    const auto getPieceRowCol = [this, rotation, reverse](int row,
                                                          int col) -> bool {
      const auto real_row = reverse ? (3 - row) : row;
      const auto real_col = col;
      switch (rotation) {
        case 0:
          return isMarked(real_row, real_col);
          break;
        case 1:
          return isMarked(3 - real_col, real_row);
          break;
        case 2:
          return isMarked(3 - real_row, 3 - real_col);
          break;
        case 3:
        default:
          return isMarked(real_col, 3 - real_row);
          break;
      }
    };
    Board table;
    for (int row = 0; row < 4; ++row) {
      for (int col = 0; col < 4; ++col) {
        const auto is_piece = getPieceRowCol(row, col);
        if (is_piece) {
          if (row + row_inc < 0 || row + row_inc > 6 || col + col_inc < 0 ||
              col + col_inc > 6) {
            return {};
          }
          table.mark(row + row_inc, col + col_inc, true);
        }
      }
    }
    return table;
  }
  bool isMarked(size_t row, size_t col) const {
    return m_piece.test(4 * row + col);
  }

 private:
  int m_index;
  std::bitset<16> m_piece;
};

#endif  // PIECE_2023_09_10_
