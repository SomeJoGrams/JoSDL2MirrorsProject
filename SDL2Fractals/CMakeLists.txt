# CMakeList.txt: CMake-Projekt für "SDL2BaseVCPKG". Schließen Sie die Quelle ein, und definieren Sie
# projektspezifische Logik hier.
#



# Fügen Sie der ausführbaren Datei dieses Projekts eine Quelle hinzu.
add_executable (SDL2BaseVCPKG "SDL2Fractals.cpp" "SDL2Fractals.h")
#target_link_libraries(SDL2BaseVCPKG PRIVATE $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
        #$<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>)

find_package(SDL2 CONFIG REQUIRED)
target_link_libraries(SDL2Fractals PRIVATE SDL2::SDL2)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET SDL2Fractals PROPERTY CXX_STANDARD 20)
endif()

# TODO: Fügen Sie bei Bedarf Tests hinzu, und installieren Sie Ziele.
