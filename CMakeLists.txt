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
include_directories(${PROJECT_SOURCE_DIR}/dep/include)
# STATIC -> .lib, SHARED -> .dll, OBJECT -> obj
#add_library(AddLib STATIC add.cpp)
#target_link_libraries(project AddLib)
#add_library(assimp SHARED C:/Users/rpg59/lib/assimp/bin/Debug/assimp-vc142-mtd.dll)
#set_target_properties(assimp PROPERTIES LINKER_LANGUAGE CXX)

# create library AddLib.lib

target_link_libraries(project opengl32.lib)
target_link_libraries(project ${PROJECT_SOURCE_DIR}/dep/lib/glfw3.lib)
target_link_libraries(project ${PROJECT_SOURCE_DIR}/dep/lib/assimp-vc142-mtd.lib)
target_link_libraries(project ${PROJECT_SOURCE_DIR}/dep/lib/glew32s.lib)

message(${PROJECT_SOURCE_DIR})

