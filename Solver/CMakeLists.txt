# CMakeList.txt : CMake project for PuzzleADaySolver/Solver
#

# Add source to this project's executable.
add_library (Solver STATIC "Solver.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.8)
  set_property(TARGET Solver PROPERTY CXX_STANDARD 20)
endif()
