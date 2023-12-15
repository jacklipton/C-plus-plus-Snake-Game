//
// Created by Jack on 2023-12-08.
//

#ifndef SNAKEGAMESDL_SNAKEOBJ_HPP
#define SNAKEGAMESDL_SNAKEOBJ_HPP

#include <SDL.h>
#include <SDL_image.h>
#include "iostream"
class SnakeObj {

public:


    enum class Direction
    {
        NONE,
        UP,
        DOWN,
        LEFT,
        RIGHT
    };

    SnakeObj(SDL_Renderer *renderer, int initX, int initY);

    ~SnakeObj() = default;

    //abstract was issue. Cant instantiate properly
    void draw(SDL_Renderer *renderer);

    void update(double delta_time);


    int getXPos() const;
    int getYPos() const;
    void setXPos(int x);
    void setYPos(int y);

    void handle_events(SDL_Event const &event);

    Direction m_direction;

private:
    SDL_Rect imageRect;
    double       m_x;
    double       m_y;
    SDL_Texture* imageTexture;

};


#endif //SNAKEGAMESDL_SNAKEOBJ_HPP
