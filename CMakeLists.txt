# CMakeList.txt: CMake-Projektdatei der obersten Ebene. Führen Sie hier die globale Konfiguration aus,
# und schließen Sie Unterprojekte ein.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

message("where does it search the toolchain file ${CMAKE_CURRENT_SOURCE_DIR}")

if (${USE_EMSCRIPTEN})
#set(EMSDK_DIR)
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/myToolchain.cmake")
else()
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/SDL2Mirrors/extern/vcpkg/scripts/buildsystems/vcpkg.cmake")
endif()

set(TESTING_ENABLED FALSE)




project("SDL2Mirrors")

if (${USE_EMSCRIPTEN})
	  # taken from cmakelists minimal_webgl emscripten examle
   macro(append_linker_flags FLAGS)
     set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${FLAGS}")
   endmacro()
   set(CMAKE_EXECUTABLE_SUFFIX ".html")

   append_linker_flags("-sENVIRONMENT=web")
   append_linker_flags("-sMIN_FIREFOX_VERSION=70")
endif()

if(${TESTING_ENABLED})
	include(CTest)
	enable_testing()
endif()


# Schließen Sie Unterprojekte ein.
add_subdirectory("SDL2Mirrors")

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)