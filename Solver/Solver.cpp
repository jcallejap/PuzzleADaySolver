#include "Solver.h"

#include <iostream>
#include <optional>
#include <vector>

#include "Board.h"
#include "BoardsStack.h"
#include "PieceList.h"

static bool solveWithPieces(BoardsStack& board, PieceList& pieces) {
  const auto [row, col] = board.firstNonMarked();
  const auto num_rem_pieces = pieces.size();
  for (size_t piece_index = 0; piece_index < num_rem_pieces; ++piece_index) {
    const auto piece = pieces.extract(piece_index);
    for (int row_inc = 0; row_inc < 4; ++row_inc) {
      for (int col_inc = 0; col_inc < 4; ++col_inc) {
        for (int rot = 0; rot < 4; ++rot) {
          const auto try_piece_true =
              piece.getTable(row - row_inc, col - col_inc, rot, true);
          if (try_piece_true && try_piece_true->isMarked(row, col) &&
              board.isCompatible(*try_piece_true)) {
            board.pushBoard(*try_piece_true);
            if (num_rem_pieces == 1) {
              return true;
            }
            if (solveWithPieces(board, pieces)) {
              return true;
            } else {
              board.popBoard();
            }
          }
          const auto try_piece_false =
              piece.getTable(row - row_inc, col - col_inc, rot, false);
          if (try_piece_false && try_piece_false->isMarked(row, col) &&
              board.isCompatible(*try_piece_false)) {
            board.pushBoard(*try_piece_false);
            if (num_rem_pieces == 1) {
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
  std::cout << *p.getTable(0, 0, 0, true) << std::endl;
  std::cout << *p.getTable(0, 0, 1, true) << std::endl;
  std::cout << *p.getTable(0, 0, 2, true) << std::endl;
  std::cout << *p.getTable(0, 0, 3, true) << std::endl;
}

void printPieces() {
  PieceList pieces;
  const auto num_rem_pieces = pieces.size();
  for (size_t piece_index = 0; piece_index < num_rem_pieces; ++piece_index) {
    std::cout << *pieces.extract(0).getTable(0, 0, 0, false) << std::endl;
  }
  std::cin.peek();
}
