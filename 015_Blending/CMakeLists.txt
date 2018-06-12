cmake_minimum_required (VERSION 2.8)
project (Application)
include_directories(../glad/include/)
include_directories(../glfw/build/include/)
include_directories(../glm/)
include_directories(../Assimp/include)
include_directories(../imgui/imgui)
include_directories(app/include/)
link_directories(${CMAKE_SOURCE_DIR}/../glfw/build/lib)
link_directories(${CMAKE_SOURCE_DIR}/../Assimp/lib)
file(GLOB app_src
    "app/src/*.cpp"
	"app/src/Engine/*.cpp"
	"app/src/Engine/Assets/*.cpp"
	"app/src/Engine/Camera/*.cpp"
	"app/src/Engine/Light/*.cpp"
	"app/src/Engine/Model/*.cpp"
	"app/src/Engine/Shader/*.cpp"
	"app/src/Engine/Texture/*.cpp"
	"app/src/imgui/*.cpp"
	"app/src/Lib/glad.c"
)
add_executable(Application ${app_src})
target_link_libraries(Application opengl32)
target_link_libraries(Application glfw3)
target_link_libraries(Application assimp)