//
// Created by Jack on 2023-12-01.
//

#ifndef SNAKEGAMESDL_FOOD_HPP
#define SNAKEGAMESDL_FOOD_HPP

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <memory>
#include <random>


class food {
public:

    explicit food(SDL_Renderer* renderer);
    ~food() = default;

    bool checkEaten(int headXPos, int headYPos);

    void draw(SDL_Renderer* renderer);
    bool getIsEaten();
    void newPos(int W, int H);


private:
    SDL_Texture* imageTexture;
    SDL_Rect imageRect{};
    bool isEaten = false;

};


#endif //SNAKEGAMESDL_FOOD_HPP
