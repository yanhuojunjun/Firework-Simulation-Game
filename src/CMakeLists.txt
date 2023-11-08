# 生成 glad 库, 这是后续可执行文件的依赖
add_library(glad STATIC glad.c)

add_library(stb_image STATIC stb_image.cpp)

add_subdirectory(OpenGLTools)

add_subdirectory(Object)

add_subdirectory(test_demo)
