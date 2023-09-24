#ifndef PIECE_LIST_2023_09_10_
#define PIECE_LIST_2023_09_10_

#include "Piece.h"
#include <vector>

class PieceList
{
public: // Constructor
  PieceList() {
    m_free.push_back(Piece{ 1, 0b1100'1100'1100'0000 });
    m_free.push_back(Piece{ 2, 0b1000'1100'1100'0000 });
    m_free.push_back(Piece{ 3, 0b0010'1111'0000'0000 });
    m_free.push_back(Piece{ 4, 0b0011'1110'0000'0000 });
    m_free.push_back(Piece{ 5, 0b1100'1000'1100'0000 });
    m_free.push_back(Piece{ 6, 0b0110'0100'1100'0000 });
    m_free.push_back(Piece{ 7, 0b1000'1000'1000'1100 });
    m_free.push_back(Piece{ 8, 0b1000'1000'1110'0000 });
  }

public: // Operations
  Piece extract(size_t index) {
    const auto piece = m_free[index];
    m_free.erase(m_free.begin() + index);
    m_used.push_back(piece);
    return piece;
  }
  void reinsert(size_t pos) {
    m_free.insert(m_free.begin() + pos, m_used.back());
    m_used.pop_back();
  }
  bool empty() const { return m_free.empty(); }
  size_t size() const { return m_free.size(); }

private:
  std::vector<Piece> m_free;
  std::vector<Piece> m_used;
};

#endif // PIECE_LIST_2023_09_10_
