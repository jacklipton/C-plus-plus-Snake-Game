//
// Created by Jack on 2023-12-09.
//

#include "food.hpp"
#include "foodImage.hpp"

food::food(SDL_Renderer* renderer){

    const unsigned char* imageData= green_fruit_bmp_file_format_food_bitmap_bmp;
    const int imageDataSize = green_fruit_bmp_file_format_food_bitmap_bmp_len;
    SDL_RWops* rwops = SDL_RWFromConstMem(imageData, imageDataSize);
    SDL_Surface* imageSurface = SDL_LoadBMP_RW(rwops, 1);

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
    imageRect.x = rand() % 775 + 15; // Adjust the position as needed
    imageRect.y = rand() % 580 + 15;
    imageRect.w = imageWidth;
    imageRect.h = imageHeight;


    imageRect.x += (imageRect.x % 15 >= 7.0) ? (15 - imageRect.x % 15) : -(imageRect.x % 15);
    imageRect.y += (imageRect.y % 15 >= 7.0) ? (15 - imageRect.y % 15) : -(imageRect.y % 15);
    // Render the image

}

bool food::checkEaten(int headXPos, int headYPos){
    if(imageRect.x == headXPos && imageRect.y == headYPos){
        return true;
    }else{
        return false;
    }
}

void food::draw(SDL_Renderer* renderer){ SDL_RenderCopy(renderer, imageTexture, NULL, &imageRect);}

bool food::getIsEaten() { return isEaten;}

void food::newPos(int W, int H){
    imageRect.x = rand() % ((W-15) - 15); // Adjust the position as needed. Fix to keep within bounds
    imageRect.y = rand() % ((H-15) - 15);

    imageRect.x += (imageRect.x % 15 >= 7.0) ? (15 - imageRect.x % 15) : -(imageRect.x % 15);
    imageRect.y += (imageRect.y % 15 >= 7.0) ? (15 - imageRect.y % 15) : -(imageRect.y % 15);
}