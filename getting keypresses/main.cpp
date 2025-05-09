#include <stdio.h>
#include <SDL3/SDL.h>
#include <string>

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

enum KeyPressSurfaces
{
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};

SDL_Window* window = NULL;
SDL_Surface* screenSurface = NULL;
SDL_Surface* loadSurface(std::string path);
SDL_Surface* gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];
SDL_Surface* gCurrentSurface = NULL;




bool init();
bool loadMedia();
void close();

bool init(){
    bool success = true;
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        SDL_Log("Unable to initialize video: %s\n", SDL_GetError());
    }
    else{
        window = SDL_CreateWindow("Penis Sucking Machine", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);
        if (window == NULL){
            SDL_Log("Window couldnt be started %s\n", SDL_GetError());
            success = false;
        }
        else{
            screenSurface = SDL_GetWindowSurface(window);
        }
    }
    return success;
}

void close(){
    for (int i = 0; i < KEY_PRESS_SURFACE_TOTAL; ++i)
    {
        if (gKeyPressSurfaces[i] != NULL) {
            SDL_free(gKeyPressSurfaces[i]);  // SDL3 compatible
            gKeyPressSurfaces[i] = NULL;
        }
    }
    screenSurface = NULL;
    SDL_DestroyWindow(window);
    window = NULL;
    SDL_Quit();
}

SDL_Surface* loadSurface(std::string path)
{
    SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
    if(loadedSurface == NULL){
        SDL_Log("Unable to load image %s, SDL Error: %s\n", path.c_str(), SDL_GetError());
    }
    return loadedSurface;
}
bool loadMedia(){
    bool success = true;
    gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] = loadSurface("press.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] == NULL){
        SDL_Log("Failed to load default image!\n");
        success = false;
    }
    
    gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] = loadSurface("up.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] == NULL){
        SDL_Log("Failed to load default image!\n");
        success = false;
    }

    gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = loadSurface("down.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] == NULL){
        SDL_Log("Failed to load default image!\n");
        success = false;
    }
    
    gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = loadSurface("left.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] == NULL){
        SDL_Log("Failed to load default image!\n");
        success = false;
    }

    gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] = loadSurface("right.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] == NULL){
        SDL_Log("Failed to load default image!\n");
        success = false;
    }
    return success;
}

int main(){
    if(!init()){
        SDL_Log("Couldnt be initialized. %s\n", SDL_GetError());
    }
    else{
        if(!loadMedia()){
            SDL_Log("Failed to load media. %s\n",SDL_GetError());
        }
        else{
        bool quit = false;
        SDL_Event events;
        gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];

        while(!quit){
            while(SDL_PollEvent(&events) != 0)
            {
                if (events.type == SDL_EVENT_QUIT){
                    quit = true;
                }
                else if(events.type == SDL_EVENT_KEY_DOWN){
                    switch (events.key.key)
                    {
                    case SDLK_UP:
                        gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_UP];
                        break;

                    case SDLK_DOWN:
                        gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
                        break;
                    
                    case SDLK_LEFT:
                        gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
                        break;
                    case SDLK_RIGHT:
                        gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
                        break;
                    
                    default:
                        gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
                        break;
                    }
                }
                SDL_BlitSurface(gCurrentSurface, NULL, screenSurface, NULL);
                SDL_UpdateWindowSurface(window);
            }
        }

    }
}
close();
return 0;
}