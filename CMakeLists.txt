cmake_minimum_required(VERSION 3.0)

project (GLSpaceFlight)

cmake_policy(SET CMP0058 NEW)
cmake_policy(SET CMP0054 NEW)

set(PROJECT_ROOT_DIR ${CMAKE_SOURCE_DIR})
set(PROJECT_SOURCE_DIR ${PROJECT_ROOT_DIR}/src)
set(PROJECT_DEP_DIR ${PROJECT_ROOT_DIR}/deps)

set(PROJECT_SRCS 
	${PROJECT_SOURCE_DIR}/main.c
	${PROJECT_SOURCE_DIR}/game_state.c
	${PROJECT_SOURCE_DIR}/game_renderer.c
	${PROJECT_SOURCE_DIR}/input_handler_glfw.c
	${PROJECT_SOURCE_DIR}/input_state.c
	${PROJECT_SOURCE_DIR}/file.c
	${PROJECT_SOURCE_DIR}/shader.c
	${PROJECT_SOURCE_DIR}/matrix.c
	${PROJECT_SOURCE_DIR}/vector.c
	${PROJECT_SOURCE_DIR}/mesh.c
	)

add_executable(GLSpaceFlight ${PROJECT_SRCS})

target_include_directories(GLSpaceFlight PUBLIC ${PROJECT_SOURCE_DIR})
target_include_directories(GLSpaceFlight SYSTEM PUBLIC ${PROJECT_ROOT_DIR}/include)

#############################################
# Dependencies
#############################################

# GLAD #############################################
# Building glad into static lib from src
set(GLAD_SOURCE_DIR ${PROJECT_ROOT_DIR}/glad)
set(GLAD_SRCS
	${GLAD_SOURCE_DIR}/glad.c
	)
add_library(glad ${GLAD_SRCS})
target_include_directories(glad PUBLIC ${GLAD_SOURCE_DIR}/include)
target_link_libraries(GLSpaceFlight glad)
target_include_directories(GLSpaceFlight SYSTEM PUBLIC ${GLAD_SOURCE_DIR}/include)

# ASSIMP ###########################################
set(ENABLE_BOOST_WORKAROUND ON)
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF)
set(BUILD_ASSIMP_TOOLS OFF)
set(BUILD_SHARED_LIBS OFF)
add_subdirectory(${PROJECT_ROOT_DIR}/assimp)
target_link_libraries(GLSpaceFlight assimp)
target_include_directories(GLSpaceFlight SYSTEM PUBLIC ${PROJECT_ROOT_DIR}/assimp/include)

# GLFW #############################################
# Make sure GLFW doesn't build examples / tests / docs
set (GLFW_BUILD_EXAMPLES OFF)
set (GLFW_BUILD_TESTS OFF)
set (GLFW_BUILD_DOCS OFF)
# Make sure GLFW doesn't build vulkan
set (GLFW_VULKAN_STATIC OFF)
add_subdirectory(${PROJECT_DEP_DIR}/glfw)
target_link_libraries(GLSpaceFlight glfw)
target_include_directories(GLSpaceFlight SYSTEM PUBLIC ${PROJECT_DEP_DIR}/glfw/include)
####################################################

if (${CMAKE_C_COMPILER_ID} STREQUAL "MSVC")
	SET_TARGET_PROPERTIES(GLSpaceFlight
		PROPERTIES COMPILE_FLAGS "/W4 /Wall")
  target_link_libraries(GLSpaceFlight opengl32 gdi32 user32 kernel32 shell32)
elseif (${CMAKE_C_COMPILER_ID} STREQUAL "GNU")
  SET_TARGET_PROPERTIES(GLSpaceFlight
    PROPERTIES COMPILE_FLAGS "-Wall -Wpedantic -g")
  # Link maths lib
  target_link_libraries(GLSpaceFlight m)
endif()

