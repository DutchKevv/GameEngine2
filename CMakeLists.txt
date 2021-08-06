cmake_minimum_required(VERSION 3.0.0)
project(game2 VERSION 0.1.0)

set(CMAKE_TOOLCHAIN_FILE "C:/vcpkg/scripts/buildsystems/vcpkg.cmake")

# Add .lib files
link_directories(${CMAKE_SOURCE_DIR}/lib)

set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib")
set(SOURCES "${SRC_DIR}/main.cpp" 
	"${SRC_DIR}/game/game.cpp" 
	"${SRC_DIR}/engine/engine.cpp" 
	"${SRC_DIR}/engine/engine.h" 
	"${SRC_DIR}/game/scenes/world.h" 
	"${SRC_DIR}/game/scenes/world.cpp" 
	"${SRC_DIR}/engine/baseObject.cpp" 
	"${SRC_DIR}/engine/baseObject.h" 
	"${SRC_DIR}/engine/renderObject.cpp" 
	"${SRC_DIR}/engine/renderObject.h" 
	"${SRC_DIR}/shape/cube.cpp" 
	"${SRC_DIR}/shape/cube.h" 
	"${SRC_DIR}/shape/plane.h" 
	"${SRC_DIR}/shape/plane.cpp" 
	"${SRC_DIR}/engine/resourceManager.cpp" 
	"${SRC_DIR}/engine/resourceManager.h" 
	"${SRC_DIR}/engine/model.cpp" 
	"${SRC_DIR}/engine/model.h" 
	"${SRC_DIR}/engine/scene.cpp" 
	"${SRC_DIR}/engine/camera.h" 
	"${SRC_DIR}/engine/editor/editor.cpp" 
	"${SRC_DIR}/engine/editor/editor.h" 
	"${SRC_DIR}/engine/scene.cpp" 
	"${SRC_DIR}/engine/scene.h" 
	"${SRC_DIR}/engine/logger.cpp" 
	"${SRC_DIR}/engine/logger.h" 
	"${SRC_DIR}/engine/skybox.cpp" 
	"${SRC_DIR}/engine/skybox.h" 
	"${SRC_DIR}/engine/context.cpp" 
	"${SRC_DIR}/engine/context.h" 
	"${SRC_DIR}/engine/texture.cpp" 
	"${SRC_DIR}/engine/texture.h" 
	"${SRC_DIR}/engine/display.cpp" 
	"${SRC_DIR}/engine/display.h" 
	"${SRC_DIR}/engine/modules/gui/gui.cpp" 
	"${SRC_DIR}/engine/modules/gui/gui.h" 
	"${SRC_DIR}/engine/editor/panels/gui_panel_world.h" 
	"${SRC_DIR}/engine/editor/panels/gui_panel_world.cpp"
)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})


message(STATUS ${CMAKE_BUILD_TYPE})
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	message(STATUS  "DEBUG!!!!!!!")
endif()

# include(CPack)
# include(CTest)
# enable_testing()

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

include_directories(
	"${CMAKE_SOURCE_DIR}/src"
	"${CMAKE_SOURCE_DIR}/src/engine"
	# "${CMAKE_SOURCE_DIR}/lib/assimp-5.0.1/include/"
)

# set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${CMAKE_SOURCE_DIR}/lib/assimp-5.0.1)

# find_package(assimp REQUIRED)
# set_target_properties(assimp::assimp PROPERTIES MAP_IMPORTED_CONFIG_DEBUG Debug)

set(ASSIMP_ENABLE_BOOST_WORKAROUND ON)
set(BUILD_STATIC_LIB ON)
set(BUILD_ASSIMP_TOOLS OFF)
set(ASSIMP_NO_EXPORT ON)
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF)
set(ASSIMP_BUILD_STATIC_LIB ON)
set(ASSIMP_BUILD_TESTS OFF)
set(BUILD_SHARED_LIBS OFF)
# # set(ASSIMP_BUILD_ALL_IMPORTERS_BY_DEFAULT OFF)
# # set(ASSIMP_BUILD_FBX_IMPORTER ON)
# # set(ASSIMP_BUILD_BLEND_IMPORTER ON)
# # set(ASSIMP_BUILD_OBJ_IMPORTER ON)
# add_subdirectory(lib/assimp-5.0.1)

# # add_library(assimp "lib/assimp-5.0.1/assimp.dll")
# # add_subdirectory(${CMAKE_SOURCE_DIR}/lib/assimp-5.0.1/contrib/irrXML)
# # add_subdirectory(${CMAKE_SOURCE_DIR}/lib/assimp-5.0.1/contrib/zlib)
# # add_subdirectory(${CMAKE_SOURCE_DIR}/lib/assimp-5.0.1)

# target_link_libraries(${PROJECT_NAME} assimp)


find_package(assimp REQUIRED)
if (assimp_FOUND)
    set(ASSIMP_LIBRARY "assimp")
    add_library(${ASSIMP_LIBRARY} SHARED IMPORTED)
    set_target_properties(${ASSIMP_LIBRARY} PROPERTIES IMPORTED_LOCATION "${ASSIMP_LIBRARY_DIRS}/libassimp.so")
endif(assimp_FOUND)

target_link_libraries(${PROJECT_NAME} ${ASSIMP_LIBRARIES})

# add_custom_target(TARGET1 ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/src/shaders $<TARGET_FILE_DIR:${PROJECT_NAME}>/shaders)
# add_custom_target(TARGET2 ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/src/textures $<TARGET_FILE_DIR:${PROJECT_NAME}>/textures)
# add_custom_target(TARGET3 ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/src/game/models $<TARGET_FILE_DIR:${PROJECT_NAME}>/game/models)


file(COPY src/shaders DESTINATION .)
file(COPY src/textures DESTINATION .)
file(COPY src/game/models DESTINATION ./game)

# add_custom_target(copy-shaders ALL COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/src/shaders ${CMAKE_BINARY_DIR}/shaders DEPENDS ${MY_TARGET})
# add_custom_target(copy-textures ALL COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/src/textures ${CMAKE_BINARY_DIR}/textures DEPENDS ${MY_TARGET})
# add_custom_target(copy-models ALL COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/src/game/models ${CMAKE_BINARY_DIR}/game/models DEPENDS ${MY_TARGET})