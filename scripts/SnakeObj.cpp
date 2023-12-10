//
// Created by Jack on 2023-12-09.
//

#include "SnakeObj.hpp"

SnakeObj::SnakeObj(SDL_Renderer *renderer, const char *path, int initX, int initY) {
    // Load BMP image
    SDL_Surface* imageSurface = IMG_Load(path);//make this dynamic
    if (!imageSurface) {
    // Handle image loading error
    //SDL_DestroyRenderer(renderer);
    //SDL_DestroyWindow(window);
    std::cout << "surface import failed" << std::endl;
    IMG_Quit();
    //SDL_Quit();
    return;
    }

    // Create a texture from the loaded image
    imageTexture = SDL_CreateTextureFromSurface(renderer, imageSurface);
    SDL_FreeSurface(imageSurface); // Free the surface, as it is no longer needed

    if (!imageTexture) {
    // Handle texture creation error
    //        SDL_DestroyRenderer(renderer);
    //        SDL_DestroyWindow(window);
    //        IMG_Quit();
    //        SDL_Quit();
    return;
    }

    // Get the dimensions of the image
    int imageWidth, imageHeight;
    SDL_QueryTexture(imageTexture, NULL, NULL, &imageWidth, &imageHeight);
    // Create an SDL_Rect object for the image
    imageRect.x = initX; // Adjust the position as needed
    imageRect.y = initY;
    imageRect.w = imageWidth;
    imageRect.h = imageHeight;

    m_x = initX;
    m_y = initY;
    m_direction = Direction::NONE;

}


void SnakeObj::draw(SDL_Renderer *renderer) {
    SDL_RenderCopy(renderer, this->imageTexture, NULL, &this->imageRect);
}

void SnakeObj::update(double delta_time){
    switch(m_direction)
    {
        case Direction::NONE:
            m_x += 0.0;
            m_y += 0.0;
            break;
        case Direction::UP:
            m_y = m_y - (5.0 * delta_time);
            break;
        case Direction::DOWN:
            m_y = m_y + (5.0 * delta_time);
            break;
        case Direction::LEFT:
            m_x = m_x - (5.0 * delta_time);
            break;
        case Direction::RIGHT:
            m_x = m_x + (5.0 * delta_time);
            break;
    }

    imageRect.x = m_x;
    imageRect.y = m_y;

    //keep the snake in a track the size of its dimension
    imageRect.x += (imageRect.x % 15 >= 7.0) ? (15 - imageRect.x % 15) : -(imageRect.x % 15);
    imageRect.y += (imageRect.y % 15 >= 7.0) ? (15 - imageRect.y % 15) : -(imageRect.y % 15);
}


int SnakeObj:: getXPos() const  { return imageRect.x;}
int SnakeObj:: getYPos() const  { return imageRect.y;}

void SnakeObj:: handle_events(SDL_Event const &event){
    switch (event.key.keysym.sym) {
        case SDLK_w:
            // Move image up
            m_direction = Direction::UP;
            break;
        case SDLK_s:
            // Move image down
            m_direction = Direction::DOWN;
            break;
        case SDLK_a:
            // Move image left
            m_direction = Direction::LEFT;
            break;
        case SDLK_d:
            // Move image right
            m_direction = Direction::RIGHT;
            break;
            // Add more cases for other keys if needed
    }
}

void SnakeObj::setXPos(int x) {
    imageRect.x=x;
}

void SnakeObj::setYPos(int y) {
    imageRect.y=y;
}




