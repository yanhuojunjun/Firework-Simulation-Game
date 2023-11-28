add_library(firework OBJECT Firework.cpp)

target_link_libraries(firework PUBLIC emitter particle_emitter emitter_render shader icamera)

add_library(firework_manager OBJECT Firework_Manager.cpp)

target_link_libraries(firework_manager PUBLIC firework emitter particle_emitter emitter_render shader icamera)