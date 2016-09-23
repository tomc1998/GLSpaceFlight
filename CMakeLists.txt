cmake_minimum_required(VERSION 2.6)

project (GLSpaceFlight)

set(PROJECT_ROOT_DIR ${CMAKE_SOURCE_DIR})
set(PROJECT_SOURCE_DIR ${PROJECT_ROOT_DIR}/src)
set(PROJECT_DEP_DIR ${PROJECT_ROOT_DIR}/deps)


include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_ROOT_DIR}/include)

set(PROJECT_SRCS 
	${PROJECT_SOURCE_DIR}/main.c
	${PROJECT_SOURCE_DIR}/game_state.c
	${PROJECT_SOURCE_DIR}/game_renderer.c
	${PROJECT_SOURCE_DIR}/input_handler_glfw.c
	${PROJECT_SOURCE_DIR}/input_state.c
	)

add_executable(GLSpaceFlight ${PROJECT_SRCS})

#############################################
# Dependencies
#############################################

# GLAD #############################################
# Building glad into static lib from src
set(GLAD_SOURCE_DIR ${PROJECT_ROOT_DIR}/glad)
set(GLAD_SRCS
	${GLAD_SOURCE_DIR}/glad.c
	)
add_library(glad STATIC ${GLAD_SRCS})
target_link_libraries(GLSpaceFlight glad)
include_directories(${GLAD_SOURCE_DIR}/include)

# GLFW #############################################
# Make sure GLFW doesn't build examples / tests / docs
set (GLFW_BUILD_EXAMPLES OFF)
set (GLFW_BUILD_TESTS OFF)
set (GLFW_BUILD_DOCS OFF)
# Make sure GLFW doesn't build vulkan
set (GLFW_VULKAN_STATIC OFF)
add_subdirectory(${PROJECT_DEP_DIR}/glfw)
target_link_libraries(GLSpaceFlight glfw)
include_directories(${PROJECT_DEP_DIR}/glfw/include)

####################################################


if ("${CMAKE_C_COMPILER_ID}" STREQUAL "MSVC")
	SET_TARGET_PROPERTIES(GLSpaceFlight
		PROPERTIES COMPILE_FLAGS "/W4 /Wall")
elseif ("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
	SET_TARGET_PROPERTIES(GLSpaceFlight
		PROPERTIES COMPILE_FLAGS "-Wall -Wpedantic -g")
endif()

