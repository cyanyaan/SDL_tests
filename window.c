#include <stdio.h>
#include <SDL3/SDL.h>

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

int main(int argc, char* argv[])
{
    SDL_Window* window = NULL;
    SDL_Surface* screenSurface = NULL;

    if (!SDL_Init(SDL_INIT_VIDEO)){
            SDL_Log("SDL couldnt be initialized! SDL Error: %s\n", SDL_GetError());
    }
    else
    {
        window = SDL_CreateWindow("SDL Window", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);
        if (window == NULL){
            SDL_Log("Window couldnt be created, SDL Error: %s\n", SDL_GetError);
        }
        else
        {
            screenSurface = SDL_GetWindowSurface(window);
            SDL_FillSurfaceRect(screenSurface, NULL, SDL_MapSurfaceRGB(screenSurface, 0xFF, 0xFF, 0xFF));
            SDL_UpdateWindowSurface(window);
            
            SDL_Event events;
            bool quit = false;
            while(quit == false){
                while(SDL_PollEvent(&events)){
                    if(events.type == SDL_EVENT_QUIT)
                        quit = true;
                }
            }
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}