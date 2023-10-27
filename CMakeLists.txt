cmake_minimum_required(VERSION 3.20)

project(tictactoe)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

find_package(PkgConfig)
pkg_check_modules(SDL2_GFX SDL2_gfx)
include_directories(${SDL2_GFX_INCLUDE_DIRS})

SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 -Wall -Werror -fdump-rtl-expand")

set(SRCS
  main.c
  logic.c
  render.c
)
set(SRCS_HEADERS
  logic.h
  render.h
  game.h
)

add_executable(tictactoe ${SRCS} ${SRCS_HEADERS})
target_link_libraries(tictactoe ${SDL2_LIBRARIES} ${SDL2_GFX_LIBRARIES})
