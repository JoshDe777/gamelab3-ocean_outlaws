cmake_minimum_required(VERSION 3.21)
project(code)

set(CMAKE_CXX_STANDARD 17)
cmake_minimum_required(VERSION 3.21)
project(eis-engine)

set(CMAKE_CXX_STANDARD 17)
set(BOX2D_BUILD_TESTBED false)

add_subdirectory(extern/glad)
add_subdirectory(extern/glfw)
add_subdirectory(extern/glm)
add_subdirectory(extern/box2d)
add_subdirectory(extern/tinygltf)
add_subdirectory(extern/soloud)
add_subdirectory(extern/stb)
add_subdirectory(extern/fastnoise)

add_subdirectory(engine)
add_subdirectory(game)
