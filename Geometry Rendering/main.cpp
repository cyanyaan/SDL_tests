#include <stdio.h>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <string>
#include <cmath>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool init();
bool loadMedia();
void close();

SDL_Window* window = NULL;
SDL_Texture* loadTexture(std::string& path);
SDL_Renderer* renderer = NULL;

bool init(){
    bool success = true;

    if(!SDL_InitSubSystem(SDL_INIT_VIDEO) != 0 ){
		SDL_Log( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
    }
    else
    {
        if(!SDL_CreateWindowAndRenderer("SDL Tuts", SCREEN_WIDTH, SCREEN_HEIGHT, NULL, &window, &renderer))
    {
        	SDL_Log( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
    }
    else
    {
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    }
    }
    return success;
}

bool loadMedia(){
    bool success = true;
    return success;
}

SDL_Texture* loadTexture(std::string& path){
    SDL_Texture* newTexture = NULL;
    SDL_Surface* textureSurface = IMG_Load(path.c_str());
    if(textureSurface == NULL){
		SDL_Log( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), SDL_GetError() );
    }
    else
    {
        newTexture = SDL_CreateTextureFromSurface(renderer, textureSurface);
    }
    if (newTexture == NULL){
		SDL_Log( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), SDL_GetError() );
    }
    else{
        SDL_DestroySurface(textureSurface);
    }
    return newTexture;

}

void close(){
    SDL_DestroyRenderer(renderer);
    renderer = NULL;
    SDL_DestroyWindow(window);
    window = NULL;
    SDL_Quit();
}

int main(){
    if(!init()){
		SDL_Log( "Failed to initialize!\n" );
    }
else
	{
		if( !loadMedia() )
		{
			SDL_Log( "Failed to load media!\n" );
		}
		else
		{	
			bool quit = false;

			SDL_Event e;

			while( !quit )
			{
				while( SDL_PollEvent( &e ) != 0 )
				{
					if( e.type == SDL_EVENT_QUIT )
					{
						quit = true;
					}
				}

                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(renderer);
                
                SDL_FRect fillRect = { SCREEN_WIDTH / 4, SCREEN_HEIGHT/4, SCREEN_WIDTH/2, SCREEN_HEIGHT/2};
                SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
                SDL_RenderFillRect(renderer, &fillRect);

                SDL_FRect outlineRect = { SCREEN_WIDTH/6, SCREEN_HEIGHT/6, SCREEN_WIDTH*2/3, SCREEN_HEIGHT*2/3};
                SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
                SDL_RenderRect(renderer, &outlineRect);

				SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0xFF, 0xFF );		
				SDL_RenderLine( renderer, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2 );

                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0x00, 0xFF);
                for(int i = 0; i < SCREEN_HEIGHT; i += 4){
                    SDL_RenderPoint(renderer, SCREEN_WIDTH/2, i);
                }

				SDL_RenderPresent( renderer );
            }
        }
    }
}