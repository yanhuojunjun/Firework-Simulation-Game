# 为所有的库链接 glad
link_libraries(glad)

add_library(icamera OBJECT ICamera.cpp)

add_library(shader STATIC Shader.cpp)

add_library(mesh STATIC Mesh.cpp)
target_link_libraries(mesh PUBLIC shader)

add_library(model STATIC Model.cpp)
target_link_libraries(model PUBLIC shader mesh libassimp.dll.a)

if(GLFW_LIB_ENABLE)
    add_library(camera_glfw STATIC Camera_GLFW.cpp)
else()
    add_library(camera_sdl STATIC Camera_SDL.cpp)
    target_link_libraries(camera_sdl PUBLIC mingw32 SDL2main SDL2)
endif()
