// SDL2BaseVCPKG.cpp: Definiert den Einstiegspunkt für die Anwendung.
//

#include "SDL2Mirrors.h"

using CloseProgram = bool;
using ErrorCode = int;

std::pair<ErrorCode,CloseProgram> handleInputEvents() {
    SDL_Event event;
    bool closeProgram(false);
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_MOUSEBUTTONDOWN:
            //mouseEvent = static_cast<SDL_MouseButtonEvent*>(&event);
            SDL_MouseButtonEvent mouseEvent = *(SDL_MouseButtonEvent*)(&event);
            if (mouseEvent.state == SDL_PRESSED && mouseEvent.button == SDL_BUTTON_RIGHT) {
                std::cout << "mouse pressed\n";
            }
            break;
        case SDL_WINDOWEVENT:
            SDL_WindowEvent windowEvent = *(SDL_WindowEvent*)(&event);
            if (windowEvent.event == SDL_WINDOWEVENT_CLOSE) {
                closeProgram = true;
            }
            //std::cout << "window event\n" << (windowEvent.event == SDL_WINDOWEVENT_CLOSE) << " " << windowEvent.event << "\n";
            break;
        default:
            //std::cout << "a new event of type" << event.type;
            break;
        }
    }
    return std::pair(0, closeProgram);
}

int main(int argc, char* argv[])
{
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


    BorderHit::RectangleHitter hitter(0, 0, 640, 480, BorderHit::HitLine2D{ BorderHit::Position2D{320,240}, 0});
    //auto lines = hitter.getLines(17);
    auto line = hitter.getLine(0, 100, 0);
    SDL_RenderDrawLine(mainRenderer, (int)line.startPos.x, (int)line.startPos.y, (int)line.endPos.x, (int)line.endPos.y);
    line = hitter.getLine(1,5,0);
    SDL_RenderDrawLine(mainRenderer, (int)line.startPos.x, (int)line.startPos.y, (int)line.endPos.x, (int)line.endPos.y);
    //for (const auto& line : lines) {
    //    std::cout << "start " << line.startPos << " end " << line.endPos << "\n";
    //    SDL_RenderDrawLine(mainRenderer, (int)line.startPos.x, (int)line.startPos.y, (int)line.endPos.x, (int)line.endPos.y);
    //}
  

    SDL_RenderPresent(mainRenderer);
    while (!closeProgram) {
        auto [retCode, closeReq] = handleInputEvents();
        closeProgram = closeReq;


    }


    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(mainRenderer);
    SDL_Quit();





    return 0;
}
