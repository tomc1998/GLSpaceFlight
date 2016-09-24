cmake_minimum_required(VERSION 3.0)

project (GLSpaceFlight)

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
	)

add_executable(GLSpaceFlight ${PROJECT_SRCS})

target_include_directories(GLSpaceFlight PUBLIC ${PROJECT_SOURCE_DIR})
target_include_directories(GLSpaceFlight PUBLIC ${PROJECT_ROOT_DIR}/include)

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
target_include_directories(glad PUBLIC ${GLAD_SOURCE_DIR}/include)
target_link_libraries(GLSpaceFlight glad)
target_include_directories(GLSpaceFlight PUBLIC ${GLAD_SOURCE_DIR}/include)

# GLFW #############################################
# Make sure GLFW doesn't build examples / tests / docs
set (GLFW_BUILD_EXAMPLES OFF)
set (GLFW_BUILD_TESTS OFF)
set (GLFW_BUILD_DOCS OFF)
# Make sure GLFW doesn't build vulkan
set (GLFW_VULKAN_STATIC OFF)
add_subdirectory(${PROJECT_DEP_DIR}/glfw)
target_link_libraries(GLSpaceFlight glfw)
target_include_directories(GLSpaceFlight PUBLIC ${PROJECT_DEP_DIR}/glfw/include)

####################################################


if ("${CMAKE_C_COMPILER_ID}" STREQUAL "MSVC")
	SET_TARGET_PROPERTIES(GLSpaceFlight
		PROPERTIES COMPILE_FLAGS "/W4 /Wall")
elseif ("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
	SET_TARGET_PROPERTIES(GLSpaceFlight
		PROPERTIES COMPILE_FLAGS "-Wall -Wpedantic -g")
endif()

