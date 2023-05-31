


#for vcpkg
include("${CMAKE_CURRENT_SOURCE_DIR}/SDL2Mirrors/extern/vcpkg/scripts/buildsystems/vcpkg.cmake")

#for emscripten
#from the github action currently expected path
include("${CMAKE_CURRENT_SOURCE_DIR}/emsdk/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake")

