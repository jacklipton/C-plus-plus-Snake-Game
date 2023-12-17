//
// Created by Jack on 2023-12-08.
//

#include "application.hpp"

Application::Application(){
    m_window = SDL_CreateWindow("Snake Game",
                                SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED,
                                810, 615,
                                SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if(!m_window)
    {
        std::cout << "Failed to create window\n";
        std::cout << "SDL2 Error: " << SDL_GetError() << "\n";
        return;
    }
}

Application::~Application(){
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}


void Application::loop(){
    Game curGame(m_window);
    bool keep_window_open = true;
    while(keep_window_open)
    {
        if(curGame.getGameState()){
            SDL_Delay(200);
            if(!curGame.resetGame()){
                keep_window_open = false;
                break;
            }
        }
        while(SDL_PollEvent(&m_window_event) > 0)
        {
            switch(m_window_event.type)
            {
                case SDL_QUIT:
                    keep_window_open = false;
                    break;
                case SDL_KEYDOWN:
                    curGame.handle_events(m_window_event);
                case SDL_WINDOWEVENT:
                    if(m_window_event.window.event == SDL_WINDOWEVENT_RESIZED) {
                        curGame.reSize(m_window);
                    }
                    break;
            }

        }
        curGame.update();
        curGame.draw();

    }
}