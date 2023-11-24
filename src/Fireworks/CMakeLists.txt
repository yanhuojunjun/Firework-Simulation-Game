add_library(firework OBJECT Firework.cpp)

add_library(firework_manager OBJECT Firework_Manager.cpp)

target_link_libraries(firework_manager PUBLIC firework)