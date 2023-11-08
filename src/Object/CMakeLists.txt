# 为所有的库链接 glad
link_libraries(glad)

add_library(cube OBJECT Cube.cpp)

add_library(vertex_manager OBJECT Vertex_Manager.cpp)

add_library(world OBJECT World.cpp)

add_library(character OBJECT Character.cpp)