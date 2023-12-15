//
// Created by Jack on 2023-12-03.
//

#include "game.hpp"
#include "gameOver.hpp"

Game::Game(SDL_Window *m_window) {

    //create the renderer window
    renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        // Handle renderer creation error
        std::cout<< "Renderer Error";
        SDL_DestroyWindow(m_window);
        //SDL_Quit();
        return;
    }


    // Create an SDL_Rect object for the window's border
    this->borderRect.x = 10;  // Adjust the border size as needed
    this->borderRect.y = 10;
    this->borderRect.w = 790; // Adjust the width and height to fit inside the window
    this->borderRect.h = 595;

    // Draw the white border
    SDL_RenderDrawRect(renderer, &borderRect);
    // Present the renderer
    SDL_RenderPresent(renderer);


    gameOverImageData = gameOver_bmp;
    const int imageDataSize = gameOver_bmp_len;
    SDL_RWops* rwops = SDL_RWFromConstMem(gameOverImageData, imageDataSize);
    SDL_Surface* imageSurface = SDL_LoadBMP_RW(rwops, 1);

    gameOverTexture = SDL_CreateTextureFromSurface(renderer, imageSurface);
    SDL_FreeSurface(imageSurface); // Free the surface, as it is no longer needed


    //create the game objects and assign them to the relevant pointer
    foodPiece = new food(renderer);
    body = new std::vector<SnakeObj>;
    body->emplace_back(renderer,20,20);
    snakeTailLen = 0;
    gameOver = false;
}

void Game::draw() {

    // Set the draw color to black
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    // Clear the renderer with black color
    SDL_RenderClear(renderer);
    // Set the draw color to white
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    // Draw the white border
    SDL_RenderDrawRect(renderer, &borderRect);



    foodPiece->draw(renderer);
    for (SnakeObj part: *body) {
        part.draw(renderer);
    }
    SDL_RenderPresent(renderer);
}

void Game::update() {
    for(int i = 1; i < body->size();i++){
        if(body->at(0).getXPos() == body->at(i).getXPos() && body->at(0).getYPos() == body->at(i).getYPos()){
            gameOver = true;
        }
    }

    if(body->at(0).getXPos() > 790 || body->at(0).getYPos() > 595 || body->at(0).getXPos() < 10|| body->at(0).getYPos() < 10){
        gameOver = true;
    }

    if(foodPiece->checkEaten( body->at(0).getXPos(), body->at(0).getYPos())){
        foodPiece->newPos();
        body->emplace_back(renderer,body->back().getXPos()-15,body->back().getYPos());
        snakeTailLen++;

    }
    if(body->size()>1){
        Tail();
    }
    body->at(0).update(3.0);
    SDL_Delay(80);



}

void Game::Tail() {
    int prevX = body->at(1).getXPos();
    int prevY = body->at(1).getYPos();
    int prev2X, prev2Y;
    body->at(1).setXPos(body->at(0).getXPos());
    body->at(1).setYPos(body->at(0).getYPos());

    for (int i = 2; i < body->size(); i++) {
        prev2X = body->at(i).getXPos();
        prev2Y = body->at(i).getYPos();
        body->at(i).setXPos(prevX);
        body->at(i).setYPos(prevY);
        prevX = prev2X;
        prevY = prev2Y;
    }


}

void Game::handle_events(const SDL_Event &event) {
    body->at(0).handle_events(event);//need to find a way so i can access the unique value in each type of subclass at the particular index. Going to the virtual definition in the parent class rn

}
Game::~Game() {
//    // Clean up memory
//    for (auto &obj: *body) {
//        delete obj;
//    }
//    delete body;
    SDL_DestroyRenderer(renderer);
}

bool Game::getGameState() const {
    return gameOver;
}

bool Game::resetGame() {


    // Get the dimensions of the image
    int imageWidth, imageHeight;
    SDL_QueryTexture(gameOverTexture, NULL, NULL, &imageWidth, &imageHeight);
    SDL_Rect gameOverCard;
    gameOverCard.x = 50; // Adjust the position as needed
    gameOverCard.y = 200;
    gameOverCard.w = imageWidth;
    gameOverCard.h = imageHeight;


    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, gameOverTexture, NULL, &gameOverCard);
    SDL_RenderPresent(renderer);

    SDL_Event conPlaying;
    while(true) {
        while (SDL_PollEvent(&conPlaying) > 0) {
            switch (conPlaying.type) {
                case SDL_KEYDOWN:
                    if (conPlaying.key.keysym.sym == SDLK_ESCAPE) {
                        return false;
                    }else if(conPlaying.key.keysym.sym == SDLK_RETURN){
                        SDL_RenderClear(renderer);
                        body->clear();
                        body->emplace_back(renderer,20,20);
                        draw();
                        gameOver = false;
                        return true;
                    }
            }
        }
    }


}

void Game::reSize() {

}





