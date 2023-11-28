# 为所有的库链接 glad
link_libraries(glad stb_image)

link_libraries(shader icamera)

if(GLFW_LIB_ENABLE)
    # 链接库文件
    link_libraries(glfw3 camera_glfw)
    # 链接自定义库
    link_libraries(cube vertex_manager)
    # 以下添加可执行文件
    add_executable(demo_glfw glfw_demo/demo_glfw.cpp)

else()
    # 链接库文件
    link_libraries(mingw32 SDL2main SDL2 SDL2_mixer)
    # 链接自定义库
    link_libraries(camera_sdl world character firework_viewer cube vertex_manager emitter particle_emitter emitter_render firework firework_manager)
    # 以下添加可执行文件
    add_executable(firework_demo sdl_demo/firework_demo.cpp)
endif()