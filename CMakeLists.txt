cmake_minimum_required(VERSION 2.6)

project (GLSpaceFlight)

set(PROJECT_ROOT_DIR ${CMAKE_SOURCE_DIR})
set(PROJECT_SOURCE_DIR ${PROJECT_ROOT_DIR}/src)
set(PROJECT_DEP_DIR ${PROJECT_ROOT_DIR}/deps)

include_directories(${PROJECT_SOURCE_DIR})

set(PROJECT_SRCS 
  ${PROJECT_SOURCE_DIR}/main.c
  )

add_executable(GLSpaceFlight ${PROJECT_SRCS})

#############################################
# Dependencies
#############################################

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

