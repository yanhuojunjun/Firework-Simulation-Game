add_library(emitter OBJECT Emitter.cpp)

add_library(particle_emitter OBJECT Particle_Emitter.cpp)
target_link_libraries(particle_emitter PUBLIC emitter)

add_library(emitter_render OBJECT Emitter_Render.cpp)
target_link_libraries(emitter_render PUBLIC emitter particle_emitter shader icamera)