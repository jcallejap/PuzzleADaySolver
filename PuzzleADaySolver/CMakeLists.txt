# CMakeList.txt : CMake project for PuzzleADaySolver/PuzzleADaySolver
#

# Add source to this project's executable.
add_executable (PuzzleADaySolver "main.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET PuzzleADaySolver PROPERTY CXX_STANDARD 20)
endif()

# Solver dependency
target_link_libraries(PuzzleADaySolver PRIVATE Solver)

# Find package SDL (from vcpkg)
find_package(SDL2 CONFIG REQUIRED)
target_link_libraries(PuzzleADaySolver
  PRIVATE
  $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
  $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
)

 