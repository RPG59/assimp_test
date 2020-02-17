set (project "TestProject")

cmake_minimum_required(VERSION 3.15)
project(project)
set(CMAKE_CXX_STANDARD 20)

#---------------------------------
message("Hello world")
message(STATUS "Hello status")
#message(FATAL_ERROR "Hello fatal error")
message("!!!! Hello not printed")
#------------------------------------------
# cmake -DFIRST=OFF -> FIRST = OFF NOTE: saved to cache!
option(FIRST "Desc first option" ON)
option(SECOND "SECOND option" OFF)

message(STAUTS "FIRST: ${FIRST}")
message(STAUTS "SECOND: ${SECOND}")
message(STATUS "ARCHITECTURE_64: ${TARGET_64}")
#--------------------------------------
add_executable(project main.cpp add.cpp)
include_directories("C:/Users/rpg59/lib/glfw-3.3.2.bin.WIN64/include/GLFW")
include_directories("C:/Users/rpg59/lib/assimp/include")
include_directories("C:/Users/rpg59/lib/glew-2.1.0/include/GL")
include_directories("C:/Users/rpg59/lib/glm/glm")
# STATIC -> .lib, SHARED -> .dll, OBJECT -> obj
#add_library(AddLib STATIC add.cpp)
#target_link_libraries(project AddLib)
#add_library(assimp SHARED C:/Users/rpg59/lib/assimp/bin/Debug/assimp-vc142-mtd.dll)
#set_target_properties(assimp PROPERTIES LINKER_LANGUAGE CXX)

# create library AddLib.lib
target_link_libraries(project C:/Users/rpg59/lib/glfw-3.3.2.bin.WIN64/lib-vc2019/glfw3.lib)
target_link_libraries(project opengl32.lib)
target_link_libraries(project C:/Users/rpg59/lib/assimp/lib/Debug/assimp-vc142-mtd.lib)
target_link_libraries(project C:/Users/rpg59/lib/glew-2.1.0/lib/Release/x64/glew32s.lib)

