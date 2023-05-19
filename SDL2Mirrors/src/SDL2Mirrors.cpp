// SDL2BaseVCPKG.cpp: Definiert den Einstiegspunkt für die Anwendung.
//

#include "SDL2Mirrors.h"


using CloseProgram = bool;
using ErrorCode = int;




std::pair<ErrorCode,CloseProgram> handleInputEvents() {
    SDL_Event event;
    bool closeProgram(false);
    SDL_WindowEvent windowEvent;
    SDL_MouseButtonEvent mouseEvent;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_MOUSEBUTTONDOWN:
        {
            //mouseEvent = static_cast<SDL_MouseButtonEvent*>(&event);
            mouseEvent = *(SDL_MouseButtonEvent*)(&event);
            if (mouseEvent.state == SDL_PRESSED && mouseEvent.button == SDL_BUTTON_RIGHT) {
                std::cout << "mouse pressed\n";
            }
            break;
        }
        case SDL_WINDOWEVENT:
        {
            windowEvent = *(SDL_WindowEvent*)(&event);
            if (windowEvent.event == SDL_WINDOWEVENT_CLOSE) {
                closeProgram = true;
            }
            //std::cout << "window event\n" << (windowEvent.event == SDL_WINDOWEVENT_CLOSE) << " " << windowEvent.event << "\n";
            break;
        }
        default:
            //std::cout << "a new event of type" << event.type;
            break;
        }
    }
    return std::pair(0, closeProgram);
}

void delayMethod(int msDelay,int whenMs) {
    return;
}

#ifdef __EMSCRIPTEN__

// Our "main loop" function. This callback receives the current time as
// reported by the browser, and the user data we provide in the call to
// emscripten_request_animation_frame_loop().
EM_BOOL one_iter(double time, void* userData) {
    // Can render to the screen here, etc.
    handleInputEvents();
    // Return true to keep the loop running.
    return EM_TRUE;
}
#endif


int main(int argc, char* argv[])
{
#ifdef __EMSCRIPTEN__
        EM_ASM_INT({
          const context = canvas.getContext("webgl2");

          var options = {};
          options['majorVersion'] = 2;
          options['minorVersion'] = 0;

          const handle = GL.registerContext(context, options);
          GL.makeContextCurrent(handle);
            });
#endif
    bool closeProgram = false;
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("SDL_Init failed: %s\n", SDL_GetError());
        return 1;
    }
    SDL_LogSetAllPriority(SDL_LOG_PRIORITY_WARN);
    SDL_Window* window = SDL_CreateWindow(
        "My SDL2 Window",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        640,
        480,
        SDL_WINDOW_SHOWN
    );

    if (window == NULL)
    {
        printf("SDL_CreateWindow failed: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Rect myRect{ 0,0,100,100 };


    SDL_Renderer* mainRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // draw the background
    SDL_SetRenderDrawColor(mainRenderer, 255, 255, 255, SDL_ALPHA_OPAQUE);


    SDL_Rect viewPort;
    SDL_RenderGetViewport(mainRenderer, &viewPort);
    std::cout << "the render rectangle size height, width, xPos,yPos: " << viewPort.h << " " << viewPort.w << " " << viewPort.x << " " << viewPort.y << "\n";

    //// fill the background with white
    //int succ = SDL_RenderFillRect(mainRenderer, &viewPort);
    //if (succ == 0) {
    //    std::cout << "it was successful viewport drawing\n";
    //}

    SDL_RenderClear(mainRenderer);

    SDL_SetRenderDrawColor(mainRenderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
    //int succ = SDL_RenderFillRect(mainRenderer, &myRect);
    /*if(succ == 0) {
        std::cout << "it was successful\n";

    }*/

    // TODO idea mirror room -> the walls mirror a light line
    int relMouseX(0);
    int relMouseY(0);


    /*SDL_RenderClear(mainRenderer);
    SDL_RenderPresent(mainRenderer);*/


    BorderHit::RectangleHitter hitter(0, 0, 640, 480, BorderHit::HitLine2D{ BorderHit::Position2D{100,-370}, 260},10);
    //BorderHit::RectangleHitter hitter(0, 0, 640, 480, BorderHit::HitLine2D{ BorderHit::Position2D{320,-240}, 35 });
    
    //auto line = hitter.getLine(0, 5, 15);
    //SDL_RenderDrawLine(mainRenderer, (int)line.startPos.x, (int)line.startPos.y, (int)line.endPos.x, (int)line.endPos.y);
    //line = hitter.getLine(0, 30, 45);
    //SDL_RenderDrawLine(mainRenderer, (int)line.startPos.x, (int)line.startPos.y, (int)line.endPos.x, (int)line.endPos.y);
    //line = hitter.getLine(0, 50, 100);
    //SDL_RenderDrawLine(mainRenderer, (int)line.startPos.x, (int)line.startPos.y, (int)line.endPos.x, (int)line.endPos.y);
    //line = hitter.getLine(1, 0, 100);
    //SDL_RenderDrawLine(mainRenderer, (int)line.startPos.x, (int)line.startPos.y, (int)line.endPos.x, (int)line.endPos.y);
    //auto line = hitter.getLine(0, 75, 100);
    //SDL_RenderDrawLine(mainRenderer, (int)line.startPos.x, (int)line.startPos.y, (int)line.endPos.x, (int)line.endPos.y);
    //
    auto line = hitter.getLine(1,0,100);
    SDL_RenderDrawLine(mainRenderer, (int)line.startPos.x, (int)line.startPos.y, (int)line.endPos.x, (int)line.endPos.y);
    //line = hitter.getLine(2,0, 100);
    //SDL_RenderDrawLine(mainRenderer, (int)line.startPos.x, (int)line.startPos.y, (int)line.endPos.x, (int)line.endPos.y);
    //line = hitter.getLine(3,0, 100);
    //SDL_RenderDrawLine(mainRenderer, (int)line.startPos.x, (int)line.startPos.y, (int)line.endPos.x, (int)line.endPos.y);
    //
    //auto lines = hitter.getLines(3);
    //for (const auto& line : lines) {
    //    std::cout << "start " << line.startPos << " end " << line.endPos << "\n";
    //    SDL_RenderDrawLine(mainRenderer, (int)line.startPos.x, (int)line.startPos.y, (int)line.endPos.x, (int)line.endPos.y);
    //}
  
    int fps = 60;
    int millliseconds = std::ceil(1000/60);


    SDL_RenderPresent(mainRenderer);

    
    int percentStep = 5;
    int lineStartPercent = 0;
    int lineEndPercent = percentStep;
    size_t currentLineIndex = 1;
    bool clearScreen = true;

#ifdef __EMSCRIPTEN__ // the main loop has to be handled separatley
    emscripten_request_animation_frame_loop(one_iter, 0);
#else
    while (!closeProgram) {
        auto [retCode, closeReq] = handleInputEvents();
        closeProgram = closeReq;

        line = hitter.getLine(currentLineIndex, lineStartPercent, lineEndPercent);
        SDL_RenderDrawLine(mainRenderer, (int)line.startPos.x, (int)line.startPos.y, (int)line.endPos.x, (int)line.endPos.y);
        //SDL_RenderDrawLine(mainRenderer, (int)line.startPos.x, (int)line.startPos.y, (int)line.endPos.x, (int)line.endPos.y);
        if (lineEndPercent >= 100) {
            // eventually clear the scrren to make it seem like a real reflection;
            if (clearScreen) {
                SDL_SetRenderDrawColor(mainRenderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
                SDL_RenderClear(mainRenderer);
                SDL_SetRenderDrawColor(mainRenderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
            }
            lineStartPercent = 0;
            lineEndPercent = percentStep;
            currentLineIndex += 1;
        }
        else {
            lineStartPercent += percentStep;
            lineEndPercent += percentStep;
        }
        //SDL_GetTicks64()
        SDL_Delay(16); // wait 16 ms to reach 60 fps
        SDL_RenderPresent(mainRenderer);
    }
#endif

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(mainRenderer);
    SDL_Quit();





    return 0;
}
