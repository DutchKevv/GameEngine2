cmake_minimum_required(VERSION 3.0.0)
project(game2 VERSION 0.1.0)

# Add .lib files
link_directories(${CMAKE_SOURCE_DIR}/lib)

set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ -static")
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib")
set(SOURCES "${SRC_DIR}/main.cpp")
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

include(CPack)
include(CTest)
enable_testing()

include_directories ("${SRC_DIR}/engine")

# Executable definition and properties
add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC "${SRC_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/src/engine")
target_compile_features(game2 PRIVATE cxx_std_17)

# We need a CMAKE_DIR with some code to find external dependencies
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

# GLFW
set(GLFW_DIR "${LIB_DIR}/glfw-3.3.3")
set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "Build the GLFW example programs")
set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "Build the GLFW test programs")
set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "Build the GLFW documentation")
set(GLFW_INSTALL OFF CACHE INTERNAL "Generate installation target")
find_library(GLFW glfw3 PATHS "${LIB_DIR}/glfw-3.3.3")
add_subdirectory("${GLFW_DIR}")
include_directories("${LIB_DIR}/glfw-3.3.3/include")
target_link_libraries(${PROJECT_NAME} "glfw" "${GLFW_LIBRARIES}")
target_include_directories(${PROJECT_NAME} PRIVATE "${GLFW_DIR}/include")
target_compile_definitions(${PROJECT_NAME} PRIVATE "GLFW_INCLUDE_NONE")

# glad
set(GLAD_DIR "${LIB_DIR}/glad")
add_library("glad" "${GLAD_DIR}/src/glad.c")
include_directories("${GLAD_DIR}/include")
target_link_libraries(${CMAKE_PROJECT_NAME} "glad")

# imgui
# Set where the ImGui files are stored
set(IMGUI_PATH  "${LIB_DIR}/imgui")

# STB Image
set(STB_PATH  "${LIB_DIR}/stb")
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${STB_PATH})

# GLM
set(GLM_PATH  "${LIB_DIR}/glm")
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${GLM_PATH})

# Compile as static library
file(GLOB IMGUI_SOURCES ${IMGUI_PATH}/*.cpp)
set(IMGUI_SOURCES ${IMGUI_SOURCES} "${LIB_DIR}/imgui/backends/imgui_impl_opengl3.h" "${LIB_DIR}/imgui/backends/imgui_impl_opengl3.cpp" "${LIB_DIR}/imgui/backends/imgui_impl_glfw.h"
"${LIB_DIR}/imgui/backends/imgui_impl_glfw.cpp")
add_library("ImGui" STATIC ${IMGUI_SOURCES})
target_include_directories("ImGui" PUBLIC ${IMGUI_PATH})
target_link_libraries(${PROJECT_NAME} ImGui)

# src
target_include_directories(game2 PRIVATE src)

# assimp
find_package(ASSIMP REQUIRED)
message(STATUS "Found ASSIMP in ${ASSIMP_INCLUDE_DIR}")

include_directories(
	"${CMAKE_SOURCE_DIR}/src"
	"${CMAKE_SOURCE_DIR}/src/engine"
	"${CMAKE_SOURCE_DIR}/include"
	"${CMAKE_SOURCE_DIR}/lib"
)

set(ENABLE_BOOST_WORKAROUND ON)
set(BUILD_STATIC_LIB ON)
set(BUILD_ASSIMP_TOOLS  ON)
set(ASSIMP_BUILD_STATIC_LIB ON)
# add_library(assimp "assimp.dll")
# add_subdirectory(${CMAKE_SOURCE_DIR}/lib/assimp-5.0.1/contrib/irrXML)
# add_subdirectory(${CMAKE_SOURCE_DIR}/lib/assimp-5.0.1)

# target_link_libraries(${PROJECT_NAME} "assimp.lib")

# target_link_libraries(${PROJECT_NAME} assimp)

# Copy dlls
# if(WIN32)
# 	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
# 		COMMAND ${CMAKE_COMMAND} -E copy_directory
# 		"${PROJECT_SOURCE_DIR}/dlls"
# 		$<TARGET_FILE_DIR:${PROJECT_NAME}>)
# endif()

add_custom_target(copy-shaders ALL COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/src/shaders ${CMAKE_BINARY_DIR}/shaders DEPENDS ${MY_TARGET})
add_custom_target(copy-textures ALL COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/src/textures ${CMAKE_BINARY_DIR}/textures DEPENDS ${MY_TARGET})
add_custom_target(copy-models ALL COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/src/game/models ${CMAKE_BINARY_DIR}/game/models DEPENDS ${MY_TARGET})