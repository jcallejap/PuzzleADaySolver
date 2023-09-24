#include <SDL2/SDL.h>
#include <stdio.h>

#include <iostream>

#include "../Solver/Solver.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
EM_JS(int, canvas_get_width, (), { return canvas.width; });
EM_JS(int, canvas_get_height, (), { return canvas.height; });
#else
int canvas_get_width() { return 512; }
int canvas_get_height() { return 512; }
#endif

constexpr uint32_t colors[] = {0X000000, 0xFF0000, 0X00FF00, 0X0000FF, 0x770000,
                               0X007700, 0X000077, 0xFF00FF, 0xFFFF00};

void renderBoard(const BoardsStack& board, int width, int height,
                 SDL_Renderer* renderer) {
  const auto square_size = std::min(width, height) / 7;
  const auto square_hor_left = std::max(0, (width - square_size * 7) / 2);

  // Render squares
  for (int row = 0; row < 7; row++) {
    for (int col = 0; col < 7; col++) {
      const auto table_id = board.getBoardThatCovers(row, col);
      const auto color = colors[table_id];
      const auto red = (color >> 16) & 0xFF;
      const auto green = (color >> 8) & 0xFF;
      const auto blue = color & 0xFF;
      SDL_SetRenderDrawColor(renderer, red, green, blue, 255);
      SDL_Rect rect{square_hor_left + square_size * col, square_size * row,
                    square_size, square_size};
      SDL_RenderFillRect(renderer, &rect);
    }
  }

  // Render text
}

extern "C" int solveAndShow(int month, int day) {
  // Prepare board
  BoardsStack board{{month / 6, month % 6}, {2 + day / 7, day % 7}};

  // Solve board
  if (solve(board)) {
    std::cout << "Solution: " << std::endl;
    std::cout << board << std::endl;
  }

  // SDL 2 image info
  int width = canvas_get_width();
  int height = canvas_get_height();

  // Prepare SDL2
  SDL_Init(SDL_INIT_VIDEO);

  // Create SDL2 renderer
  SDL_Window* window;
  SDL_Renderer* renderer;
  SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer);

  // Setup a white background
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderClear(renderer);

  // Draw
  renderBoard(board, width, height, renderer);

  // Show the renderer
  SDL_RenderPresent(renderer);

  // SDL_Quit();
  std::cin.ignore(1, '\n');
  return 0;
}

int main(int argc, char* argv[]) {
  // Check input
  if (argc < 3) {
    std::cout << "Usage " << argv[0] << " month day" << std::endl;
    return 1;
  }

  // Parse arguments
  const auto month = atoi(argv[1]);
  const auto day = atoi(argv[2]);

  // Minimal argument check
  if (month < 1 || month > 12 || day < 1 || day > 31) {
    std::cout << "Invalid arguments\n";
    std::cout << "Usage " << argv[0] << " month day\n";
    return 2;
  }

  // Solve
  return solveAndShow(month - 1, day - 1);  //< Arguments are zero based
}