if(NOT GLFW_LIB_ENABLE)
add_library(sound_player OBJECT Sound_Player.cpp)
target_link_libraries(sound_player PUBLIC mingw32 SDL2_mixer)
endif()