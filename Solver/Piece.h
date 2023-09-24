#ifndef PIECE_2023_09_10_
#define PIECE_2023_09_10_

#include <bitset>
#include <optional>

#include "EnumClassIterator.h"

/*
 * This object represent a 4x4 piece.
 * It can be converted to a board after some modifications:
 *  - reverse: the horizontal form is mirrored.
 *  - rotation: the piece can be rotated 0º, 90º, 80º or 270º
 */
class Piece {
 public:  // Constructor
  Piece(int index, const std::bitset<16>& piece) : m_index{index} {
    for (size_t row = 0; row < 4; ++row) {
      for (size_t col = 0; col < 4; ++col) {
        m_piece.set(4 * row + col, piece.test(4 * col + row));
      }
    }
  }

 public:  // Piece rotation management
  enum class Rotation : int { Rot_0, Rot_90, Rot_180, Rot_270, RotationLast };
  using RotationIterator =
      EnumClassIterator<Rotation, Rotation::Rot_0, Rotation::RotationLast>;

 public:  // Mirroring management
  enum class Mirror : int { Normal, Mirrored, MirrorLast };
  using MirrorIterator =
      EnumClassIterator<Mirror, Mirror::Normal, Mirror::MirrorLast>;

 public:
  // Convert this piece to a board,
  // given a top-left position, a rotation and if it is reversed.
  // If the piece lays outside the board, it returns an empty optional.
  std::optional<Board> getTable(int row_inc, int col_inc, Rotation rotation,
                                Mirror mirror) const {
    const auto getPieceRowCol = [this, rotation, mirror](int row,
                                                         int col) -> bool {
      const auto real_row = (mirror == Mirror::Mirrored) ? (3 - row) : row;
      const auto real_col = col;
      switch (rotation) {
        case Rotation::Rot_0:
          return isMarked(real_row, real_col);
          break;
        case Rotation::Rot_90:
          return isMarked(3 - real_col, real_row);
          break;
        case Rotation::Rot_180:
          return isMarked(3 - real_row, 3 - real_col);
          break;
        case Rotation::Rot_270:
        default:
          return isMarked(real_col, 3 - real_row);
          break;
      }
    };

    // Check the 4x4 to see where it lays inside the board
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
