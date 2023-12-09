if(NOT GLFW_LIB_ENABLE)
    add_library(sound_player OBJECT Sound_Player.cpp)
    target_link_libraries(sound_player PUBLIC mingw32 SDL2_mixer)
endif()

add_library(firework_pipeline OBJECT Firework_Pipeline.cpp)

add_library(pipe_firework_manager OBJECT Pipe_Firework_Manager.cpp)

target_link_libraries(pipe_firework_manager PUBLIC firework_pipeline OpenMP::OpenMP_CXX)

add_library(bloom OBJECT bloom.cpp)

# add_library(firework OBJECT Firework.cpp)

# add_library(firework_manager OBJECT Firework_Manager.cpp)

# target_link_libraries(firework_manager PUBLIC firework)