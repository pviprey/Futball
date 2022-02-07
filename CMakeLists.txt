cmake_minimum_required(VERSION 3.10)

project(FOOT
  VERSION 0.1.0
)

include(GNUInstallDirs)

find_package(gf REQUIRED COMPONENTS graphics)

add_executable(FOOT
  Game.cc
  bits/Data.cc
  bits/Terrain.cc
  bits/Ballon.cc
  bits/Equipe.cc
  bits/Joueur.cc
)

target_link_libraries(FOOT
  PRIVATE
    gf::graphics
)

target_compile_options(FOOT
  PRIVATE
    "-Wall" "-Wextra" "-g" "-fpic" "-O2"
)
