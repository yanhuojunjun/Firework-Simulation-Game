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
    link_libraries(mingw32 SDL2main SDL2 camera_sdl world character)
    # 链接自定义库
    link_libraries(cube vertex_manager)
    # 以下添加可执行文件
    add_executable(demo_sdl sdl_demo/demo_sdl.cpp)
    add_executable(demo_sdl_2 sdl_demo/demo_sdl_2.cpp)
    add_executable(firework_0 sdl_demo/firework_0.cpp)
endif()