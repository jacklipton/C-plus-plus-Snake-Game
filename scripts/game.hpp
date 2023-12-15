//
// Created by Jack on 2023-12-03.
//

#ifndef SNAKEGAMESDL_GAME_HPP
#define SNAKEGAMESDL_GAME_HPP

#include "SDL_image.h"
#include "SDL.h"
#include "SDL_ttf.h"
#include "food.hpp"
#include "SnakeObj.hpp"

#include <vector>


class Game {
public:

    explicit Game(SDL_Window *m_window);
    ~Game();

    void draw();
    void update();
    void Tail();
    void handle_events(SDL_Event const &event);
    bool getGameState() const;
    bool resetGame();
    void reSize();


private:

    SDL_Renderer* renderer;
    SDL_Rect borderRect{};
    std::vector<SnakeObj>* body;
    food* foodPiece;
    int snakeTailLen;
    bool gameOver;

    SDL_Texture* gameOverTexture;

    const unsigned char* squareImageData;
    const unsigned char* circleImageData;
    const unsigned char* foodImageData;
    const unsigned char* gameOverImageData;



};


#endif //SNAKEGAMESDL_GAME_HPP
