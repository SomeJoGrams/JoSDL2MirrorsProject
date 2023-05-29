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


    int screenXSize = 640;
    int screenYSize = 480;

    BorderHit::RectangleHitter hitter(0, 0, screenXSize,screenYSize, BorderHit::HitLine2D{ BorderHit::Position2D{100,-370}, 75},1);
    //BorderHit::SimpleRectangleHitter simpleHitter(hitter);
    
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
    // draw some percent lines
    //auto line = hitter.getLine(1,0,100);
    //SDL_RenderDrawLine(mainRenderer, (int)line.startPos.x, (int)line.startPos.y, (int)line.endPos.x, (int)line.endPos.y);
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
    int millliseconds = std::ceil<int>(1000/60);


    SDL_RenderPresent(mainRenderer);

    
    int percentStep = 5;
    int lineStartPercent = 0;
    int lineEndPercent = percentStep;
    size_t currentLineIndex = 1;
    bool clearScreen = true;

    
    //double speed = 10;
    // TODO uneven speed like 10.8
    double speed = std::sqrt(screenXSize * screenXSize + screenYSize * screenYSize) * (double)0.01; // the diagonal is used to calculate the speed;
    //double speed = std::sqrt(screenXSize * screenXSize + screenYSize * screenYSize) * 0.01; // one percent of the diagonal

    int time = 0;

#ifdef __EMSCRIPTEN__ // the main loop has to be handled separatley
    emscripten_request_animation_frame_loop(one_iter, 0);
#else
    while (!closeProgram) {
        auto [retCode, closeReq] = handleInputEvents();
        closeProgram = closeReq;

        //line = hitter.getLine(currentLineIndex, lineStartPercent, lineEndPercent);
        //std::vector<BorderHit::SimpleLine2D> lines = hitter.getLinesWithSpeed(currentLineIndex, speed, time); // always draw a fixed distance if a line gets finished the next lines also have to be drawn
        //std::pair<std::vector<BorderHit::SimpleLine2D>, BorderHit::TraveledLine>
        
        
        //SDL_RenderDrawLine(mainRenderer, (int)line.startPos.x, (int)line.startPos.y, (int)line.endPos.x, (int)line.endPos.y);
        //if (lineEndPercent >= 100) {
        //    // eventually clear the scrren to make it seem like a real reflection;
        //    if (clearScreen) {
        //        SDL_SetRenderDrawColor(mainRenderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        //        SDL_RenderClear(mainRenderer);
        //        SDL_SetRenderDrawColor(mainRenderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
        //    }
        //    lineStartPercent = 0;
        //    lineEndPercent = percentStep;
        //    currentLineIndex += 1;
        //}
        //else {
        //    lineStartPercent += percentStep;
        //    lineEndPercent += percentStep;
        //}
        //SDL_GetTicks64()
        //auto [lines, traveledLine] = hitter.getLinesWithSpeedWithTrailTime(currentLineIndex,speed,time,30); // always draw a fixed distance if a line gets finished the next lines also have to be drawn
        // test for index sequqence
        //std::index_sequence seq = std::index_sequence<30>{}
        //for (size_t i : std::to_array<size_t>({ 1,2,3,4,5,6,7,8,9,10,11,12 })) {
        ////for (size_t i = 0; i <= 300; i++){
        ////    auto [lines, traveledLine] = hitter.getLinesWithSpeedWithTrailTime(currentLineIndex, speed, i, 30); // always draw a fixed distance if a line gets finished the next lines also have to be drawn
        ////    for (const auto& curLine : lines) {
        ////        SDL_RenderDrawLine(mainRenderer, (int)curLine.startPos.x, (int)curLine.startPos.y, (int)curLine.endPos.x, (int)curLine.endPos.y);
        ////        SDL_RenderPresent(mainRenderer);
        ////        
        ////    }
        ////    SDL_Delay(200);
        ////    SDL_SetRenderDrawColor(mainRenderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        ////    SDL_RenderClear(mainRenderer);
        ////    SDL_SetRenderDrawColor(mainRenderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
        ////    std::cout << "drawing" << i << "\n";
        ////}
        ////std::cout << "finished\n";
        ////SDL_Delay(1000);
        ////SDL_DestroyWindow(window);
        ////SDL_DestroyRenderer(mainRenderer);
        ////SDL_Quit();
        ////return 0;
        //auto [lines, traveledLine] = hitter.getLinesWithSpeedWithTrailTime(currentLineIndex, speed, time, 15); // always draw a fixed distance if a line gets finished the next lines also have to be drawn
        ////auto [lines, traveledLine] = hitter.getLinesWithSpeedWithTrailLength(currentLineIndex, speed, time, 15); // always draw a fixed distance if a line gets finished the next lines also have to be drawn
        //currentLineIndex = traveledLine.lineIndex;
        //time = traveledLine.traveledDistance / speed ; // v = s / t <=> s = v * t <=> t = s / v 
        //auto lines = simpleHitter.linesTrailTime(speed, 15, 1);
        //auto lines = simpleHitter.linesTrailLength(speed, 200, 1);
        auto [lines, traveledLine] = hitter.getLinesWithSpeedWithTrailTime(currentLineIndex, speed, time, 3); // always draw a fixed distance if a line gets finished the next lines also have to be drawn
        currentLineIndex = traveledLine.lineIndex;
        time = traveledLine.traveledDistance / speed; // v = s / t <=> s = v * t <=> t = s / v 
        time += 1;
        for (const auto& curLine : lines) {
            SDL_RenderDrawLine(mainRenderer, std::round<int>(curLine.startPos.x), std::round<int>(curLine.startPos.y), std::round<int>(curLine.endPos.x), std::round<int>(curLine.endPos.y));
        }
        //SDL_RenderDrawLine(mainRenderer, (int)line.startPos.x, (int)line.startPos.y, (int)line.endPos.x, (int)line.endPos.y);
        SDL_RenderPresent(mainRenderer);
        SDL_Delay(16); // wait 16 ms to reach 60 fps
        SDL_SetRenderDrawColor(mainRenderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(mainRenderer);
        SDL_SetRenderDrawColor(mainRenderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
    }
#endif

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(mainRenderer);
    SDL_Quit();





    return 0;
}
