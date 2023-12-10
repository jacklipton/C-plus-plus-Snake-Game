#pragma once

#include <SDL.h>
#include <iostream>
#include "game.hpp"

class Application
{

public:

    Application();
    ~Application();

    void loop();


private:

    SDL_Window  *m_window;
    SDL_Event    m_window_event;

};