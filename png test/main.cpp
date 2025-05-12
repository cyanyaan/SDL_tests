#include <stdio.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <string>

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

bool init();
bool loadMedia();
void close();

SDL_Window* gWindow = NULL;
SDL_Surface* screenSurface = NULL;
SDL_Surface* loadSurface(std::string path);
SDL_Surface* PNG_Surface = NULL;

SDL_Surface* loadSurface(std::string path){
    SDL_Surface* optimizedSurface = NULL;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if( loadedSurface == NULL )
    {
        SDL_Log( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), SDL_GetError() );
    }
    else{
        optimizedSurface = SDL_ConvertSurface( loadedSurface, screenSurface->format);
        if(optimizedSurface == NULL){
            SDL_Log("Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }
        SDL_DestroySurface(loadedSurface);
    }
    return optimizedSurface;
}


bool init(){
    bool success = true;

    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("SDL couldnt be initialized! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    else{
        gWindow = SDL_CreateWindow("SDL Tut", SCREEN_WIDTH, SCREEN_HEIGHT, 0);
        if( gWindow == NULL )
        {
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        }
        else{
            // int imgFlags = IMG_INIT_PNG;
            // if(!(IMG_Init(imgFlags) & imgFlags))
            // {
            //     printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
            //     success = false;  
            // } 
            //This is deprecated in SDL3
                screenSurface = (SDL_Surface*)SDL_GetWindowSurface(gWindow);
            
        }
    }
    return success;
}

bool loadMedia(){
    bool success = true;
    PNG_Surface = loadSurface("loaded.png");
    if(PNG_Surface == NULL){
		SDL_Log( "Failed to load PNG image!\n" );
		success = false;
    }
    return success;
}

void close(){
    SDL_DestroySurface(PNG_Surface);
    PNG_Surface = NULL;
    SDL_DestroyWindow(gWindow);
    SDL_Quit();
}

int main(){
    if(!init()){
		SDL_Log( "Failed to initialize!\n" );    
    } 
    else
    {
        if(!loadMedia())
        {
			SDL_Log( "Failed to load media!\n" );
        }
        else
        {
            bool quit = false;
            SDL_Event events;
            while(!quit)
            {
                while(SDL_PollEvent(&events) != 0)
                {
                    if(events.type == SDL_EVENT_QUIT){
                        quit = true;
                    }
                }
                SDL_BlitSurface(PNG_Surface, NULL, screenSurface, NULL);
                SDL_UpdateWindowSurface(gWindow);
            }
        }
    } 
    close();
    return 0;
}