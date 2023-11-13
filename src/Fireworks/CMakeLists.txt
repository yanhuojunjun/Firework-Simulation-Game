add_library(path_generator OBJECT Path_Generator.cpp)

add_library(particle OBJECT particle.cpp)

add_library(circle_firework OBJECT circle_firework.cpp)

target_link_libraries(circle_firework PUBLIC particle path_generator)