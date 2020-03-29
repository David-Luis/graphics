cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
project (Application)
include_directories(../../glad/include/)
include_directories(../../glfw/build/include/)
include_directories(../../glm/)
include_directories(../../Assimp/include)
include_directories(../../imgui/imgui)
include_directories(app/include/)
link_directories(${CMAKE_SOURCE_DIR}/../../../glfw/build/lib)
link_directories(${CMAKE_SOURCE_DIR}/../../../Assimp/lib)
file(GLOB app_src
    "app/src/*.cpp"
	"app/src/Engine/*.cpp"
	"app/src/Engine/Assets/*.cpp"
	"app/src/Engine/Camera/*.cpp"
	"app/src/Engine/Light/*.cpp"
	"app/src/Engine/Model/*.cpp"
	"app/src/Engine/Shader/*.cpp"
	"app/src/Engine/Texture/*.cpp"
	"app/src/Engine/Scene/*.cpp"
	"app/src/imgui/*.cpp"
	"app/src/Lib/glad.c"
)

set(CMAKE_EXECUTABLE_SUFFIX ".html")
add_executable(Application ${app_src})
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Application)
set_target_properties(Application PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

target_link_libraries(Application opengl32)
target_link_libraries(Application glfw3)
target_link_libraries(Application assimp)