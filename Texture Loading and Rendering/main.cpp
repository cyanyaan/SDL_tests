#include <stdio.h>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <string>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool init();
bool loadMedia();
void close();

SDL_Texture* loadTexture(const std::string& path);
SDL_Window* window = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Texture* gTexture = NULL;

bool init(){
    bool success = true;
    if(!SDL_Init(SDL_INIT_VIDEO)){
        SDL_Log( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
    }
    else
    {
        if(!SDL_CreateWindowAndRenderer("SDL Tuts", SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &gRenderer))
        {
            SDL_Log( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
        }
        else
        {
            SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        }
    }
    return success;
}

SDL_Texture* loadTexture(const std::string& path){
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL){
		SDL_Log( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), SDL_GetError() );        
    }
    else{
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if( newTexture == NULL )
		{
			SDL_Log( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
        SDL_DestroySurface(loadedSurface);
    }
    return newTexture;
}

bool loadMedia()
{
    bool success = true;
    gTexture = loadTexture("texture.png");
    if (gTexture == NULL){
        SDL_Log( "Failed to load texture image!\n" );
		success = false;
    }
    return success;
}

void close(){
    SDL_DestroyTexture(gTexture);
    gTexture = NULL;
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(window);
    window = NULL;
    gRenderer = NULL;
    SDL_Quit();
}

int main(){
    if(!init()){
        SDL_Log( "Failed to initialize!\n" );
    }
    else
    {
        if(!loadMedia()){
			SDL_Log( "Failed to load media!\n" );            
        }
        else
        {
            bool quit = false;
            SDL_Event events;
            while(!quit)
            {
                while(SDL_PollEvent(&events) != 0){
                    if(events.type == SDL_EVENT_QUIT){
                        quit = true;
                    }
                }
                SDL_RenderClear(gRenderer);
                SDL_RenderTexture(gRenderer, gTexture, NULL, NULL);
                SDL_RenderPresent(gRenderer);
                
            }
        }
    }
    close();
    return 0;
}