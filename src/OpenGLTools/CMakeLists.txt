# 为所有的库链接 glad
link_libraries(glad)

add_library(icamera OBJECT ICamera.cpp)

add_library(shader STATIC Shader.cpp)

add_library(mesh STATIC Mesh.cpp)
target_link_libraries(mesh PUBLIC shader)

add_library(model STATIC Model.cpp)
target_link_libraries(model PUBLIC shader mesh assimp)

if(GLFW_LIB_ENABLE)
    add_library(camera_glfw STATIC Camera_GLFW.cpp)
else()
    add_library(firework_viewer STATIC Firework_Viewer.cpp)
    target_link_libraries(firework_viewer PUBLIC mingw32 SDL2main SDL2 icamera)

endif()
