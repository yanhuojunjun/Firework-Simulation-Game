add_library(animation OBJECT Animation.cpp)

target_link_libraries(animation PUBLIC pipe_firework_manager)

add_library(animation_0 OBJECT Animation_0.cpp)

target_link_libraries(animation_0 PUBLIC animation)