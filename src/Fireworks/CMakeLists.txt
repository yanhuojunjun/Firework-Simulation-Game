add_library(firework_pipeline OBJECT Firework_Pipeline.cpp)

add_library(pipe_firework_manager OBJECT Pipe_Firework_Manager.cpp)

target_link_libraries(pipe_firework_manager PUBLIC firework_pipeline OpenMP::OpenMP_CXX)

# add_library(firework OBJECT Firework.cpp)

# add_library(firework_manager OBJECT Firework_Manager.cpp)

# target_link_libraries(firework_manager PUBLIC firework)