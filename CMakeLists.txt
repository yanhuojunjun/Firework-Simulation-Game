# cmake 最低版本
cmake_minimum_required(VERSION 3.27)
# 项目名称
project(opengl)

# 定义路径
get_filename_component(PROJECT_DIR ${CMAKE_CURRENT_LIST_FILE} DIRECTORY)
set(INCLUDE_DIR ${PROJECT_DIR}/include)
set(RUN_DIR ${PROJECT_DIR}/run)
# 源文件路径
set(PROJECT_SOURCE_DIR ${PROJECT_DIR}/src)
# 可执行文件输出位置
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${RUN_DIR}/bin)
# 动态库输出位置
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${RUN_DIR}/bin)
# 静态库输出位置
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${RUN_DIR}/lib)

# 声明有关项目的选项

# 设置选项
# 第二个参数 如果为 ON 则使用GLFW库作为窗口及控制库 为 OFF 则使用SDL2库 
set(GLFW_LIB_ENABLE OFF CACHE BOOL "whether use glfw or sdl2" FORCE)

if(GLFW_LIB_ENABLE)
    message(STATUS "using glfw")
else()
    message(STATUS "using SDL2")
endif()

# 指明所有头文件路径
include_directories(${INCLUDE_DIR}/Lib_Include
                    ${INCLUDE_DIR}/Lib_Include/SDL2
                    ${INCLUDE_DIR}/Lib_Include/glad
                    ${INCLUDE_DIR}/Lib_Include/GLFW
                    ${INCLUDE_DIR}/Lib_Include/KHR
                    ${INCLUDE_DIR}/Lib_Include/STB_IMAGE
                    ${INCLUDE_DIR}/Lib_Include/glm
                    ${INCLUDE_DIR}/OpenGLTools
                    ${INCLUDE_DIR}/Object
                    ${INCLUDE_DIR}/Fireworks
                    ${INCLUDE_DIR}/Lib_Include/assimp)
# 链接库文件
link_directories(${RUN_DIR}/lib
                 ${RUN_DIR}/bin
                 ${RUN_DIR}/Lib_Lib/sdl2_lib
                 ${RUN_DIR}/Lib_Lib/glfw
                 ${RUN_DIR}/Lib_Lib/stb_image
                 ${RUN_DIR}/Lib_Lib/assimp_lib)

add_subdirectory(src)