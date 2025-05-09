#include <stdio.h>
#include <SDL3/SDL.h>

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

bool init();
bool loadMedia();
void close();

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gHelloWorld = NULL;

bool init()
{
    bool success = true;
    if(!SDL_Init(SDL_INIT_VIDEO)){
        SDL_Log("Erhmm: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        gWindow = SDL_CreateWindow("SDL Tutorial", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);
        if(gWindow == NULL){
            SDL_Log("Erhmm widnow cant be created %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            gScreenSurface = SDL_GetWindowSurface(gWindow);
        }
    }
    return success;
}

bool loadMedia(){
    bool success = true;
    gHelloWorld = SDL_LoadBMP("hello_world.bmp");
    if (gHelloWorld == NULL){
        SDL_Log("Unable to load image: %s\n", SDL_GetError());
        success = false;
    }
    return success;
}

void close(){
    SDL_DestroySurface(gHelloWorld);
    gHelloWorld = NULL;
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    SDL_Quit();
}

int main(){
    if(!init()){
        SDL_Log("Failed to initialize\n");
    }
    else
    {
        if(!loadMedia())
        {
            printf("Failed to load media\n");
        }
        else{
            SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);
            SDL_UpdateWindowSurface(gWindow);

            SDL_Event events;
            bool quit = false; 
            while(!quit)
            { 
                while(SDL_PollEvent(&events))
                { 
                    // if( events.type == SDL_EVENT_QUIT )
                    //     quit = true; 
                    switch (events.type)
                    {
                    case SDL_EVENT_QUIT:
                        quit = true;
                        break;
                    default:
                        break;
                    }
                } 
            }
        }
    }   

    close();
    return 0;
}