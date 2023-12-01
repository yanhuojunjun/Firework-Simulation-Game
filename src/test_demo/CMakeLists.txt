# 为所有的库链接 glad
link_libraries(glad stb_image)

link_libraries(shader model icamera)

# 链接自定义库
link_libraries(emitter particle_emitter emitter_render firework_pipeline pipe_firework_manager bloom)

if(GLFW_LIB_ENABLE)
    # 链接库文件
    link_libraries(glfw3 camera_glfw)
else()
    # 链接库文件
    link_libraries(mingw32 SDL2main SDL2 SDL2_mixer firework_viewer sound_player)
endif()

add_executable(firework_demo firework_demo.cpp)

add_executable(video_demo video_demo.cpp)
target_link_libraries(video_demo PUBLIC animation animation_0)

