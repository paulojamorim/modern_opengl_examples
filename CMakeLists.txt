cmake_minimum_required(VERSION 2.8)
Project (tutorial)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake_scripts/  ${CMAKE_MODULE_PATH})
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11") 
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++") 
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11") 
endif()

# Adicionando Sources
set (SOURCES window.cpp)

# GLEW
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_PATH})

# OpenGL
find_package(OpenGL)
include_directories(${OPENGL_INCLUDE_DIR})

# GLFW
FIND_PACKAGE (glfw REQUIRED)
INCLUDE_DIRECTORIES (${GLFW_INCLUDE_DIR})

# Soil
#FIND_PACKAGE ( SOIL REQUIRED )
#INCLUDE_DIRECTORIES(${SOIL_INCLUDE_DIR})

# GLM
find_package(GLM REQUIRED) 
INCLUDE_DIRECTORIES(${GLM_INCLUDE_DIRS})

# SFML
#find_package(SFML COMPONENTS graphics window system)
#INCLUDE_DIRECTORIES(${SFML_INCLUDE_DIR})

add_executable (window ${SOURCES})
target_link_libraries(textures ${GLEW_LIBRARY} ${GLFW_LIBRARIES} ${OPENGL_LIBRARIES} ${SOIL_LIBRARIES} ${SFML_LIBRARIES})
