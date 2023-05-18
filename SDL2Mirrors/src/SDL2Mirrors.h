// SDL2BaseVCPKG.h: Includedatei für Include-Standardsystemdateien
// oder projektspezifische Includedateien.

#pragma once

#include <iostream>
#include <utility>

#define SDL_MAIN_HANDLED // alternative for linking with visual studio
#include "SDL2/SDL.h"


#include "BorderHit.hpp"



#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/html5.h>
#endif


// TODO: Verweisen Sie hier auf zusätzliche Header, die Ihr Programm erfordert.
