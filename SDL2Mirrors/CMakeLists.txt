# CMakeList.txt: CMake-Projekt für "SDL2BaseVCPKG". Schließen Sie die Quelle ein, und definieren Sie
# projektspezifische Logik hier.
#


#add_library(BorderHitter INTERFACE)
add_library(BorderHitter INTERFACE)
target_include_directories(BorderHitter INTERFACE "include")



# Fügen Sie der ausführbaren Datei dieses Projekts eine Quelle hinzu.
add_executable(SDL2Mirrors "src/SDL2Mirrors.cpp" "src/SDL2Mirrors.h" "src/BorderHit.cpp")


find_package(SDL2 CONFIG REQUIRED)

target_link_libraries(SDL2Mirrors PRIVATE $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
        $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static> BorderHitter)
#target_link_libraries(SDL2Fractals PRIVATE SDL2::SDL2)



if(${TESTING_ENABLED})
	add_subdirectory("Testing")
endif()


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET SDL2Mirrors PROPERTY CXX_STANDARD 20)
else()
  set_property(TARGET SDL2Mirrors PROPERTY CXX_STANDARD 17)
endif()

# TODO: Fügen Sie bei Bedarf Tests hinzu, und installieren Sie Ziele.
