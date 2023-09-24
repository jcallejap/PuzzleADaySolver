#include "Solver.h"

#include <iostream>
#include <optional>
#include <vector>

#include "Board.h"
#include "BoardsStack.h"
#include "PieceList.h"

/*
 * Recursive method.
 * First, it tries to fill the next free square using every piece available.
 * On success, it call himself to fill the remaining squares.
 * On failure, it returns false.
 * @return true if
 */
static bool solveWithPieces(BoardsStack& board, PieceList& pieces) {
  const auto [row, col] = board.firstNonMarked();
  const auto num_rem_pieces = pieces.size();
  // Check every free piece with every possible rotation and translation
  for (size_t piece_index = 0; piece_index < num_rem_pieces; ++piece_index) {
    const auto piece = pieces.extract(piece_index);
    for (int row_inc = 0; row_inc < 4; ++row_inc) {
      for (int col_inc = 0; col_inc < 4; ++col_inc) {
        for (auto rot : Piece::RotationIterator{}) {
          for (auto mirror : Piece::MirrorIterator{}) {
            const auto try_piece =
                piece.getTable(row - row_inc, col - col_inc, rot, mirror);
            if (try_piece && try_piece->isMarked(row, col) &&
                board.isCompatible(*try_piece)) {
              board.pushBoard(*try_piece);
              if (pieces.empty()) {
                return true;
              }
              if (solveWithPieces(board, pieces)) {
                return true;
              } else {
                board.popBoard();
              }
            }
          }
        }
      }
    }
    pieces.reinsert(piece_index);
  }

  return false;
}

bool solve(BoardsStack& board) {
  PieceList pieces;
  return solveWithPieces(board, pieces);
}

void testPrintPiece() {
  Piece p{0, 0b1000'1100'1100'0000};
  std::cout << *p.getTable(0, 0, Piece::Rotation::Rot_0,
                           Piece::Mirror::Mirrored)
            << std::endl;
  std::cout << *p.getTable(0, 0, Piece::Rotation::Rot_90,
                           Piece::Mirror::Mirrored)
            << std::endl;
  std::cout << *p.getTable(0, 0, Piece::Rotation::Rot_180,
                           Piece::Mirror::Mirrored)
            << std::endl;
  std::cout << *p.getTable(0, 0, Piece::Rotation::Rot_270,
                           Piece::Mirror::Mirrored)
            << std::endl;
}

void printPieces() {
  PieceList pieces;
  const auto num_rem_pieces = pieces.size();
  for (size_t piece_index = 0; piece_index < num_rem_pieces; ++piece_index) {
    std::cout << *pieces.extract(0).getTable(0, 0, Piece::Rotation::Rot_0,
                                             Piece::Mirror::Normal)
              << std::endl;
  }
  std::cin.peek();
}
