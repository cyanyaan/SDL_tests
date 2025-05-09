#include <stdio.h>
#include <SDL3/SDL.h>
#include <string>


const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

bool init();
bool loadMedia();
void close();

SDL_Surface* loadSurface(std::string path);
SDL_Window* window = NULL;
SDL_Surface* screenSurface = NULL;
SDL_Surface* stretchedSurface = NULL;



bool init(){
    bool success = true;
    if(!SDL_Init(SDL_INIT_VIDEO)){
        SDL_Log( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
    }
    else {
        window = SDL_CreateWindow("ok", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);
        if(window == NULL){
            SDL_Log( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
        }
        else{
            screenSurface = SDL_GetWindowSurface(window);
        }
    }
    return success;
}

bool loadMedia(){
    bool success = true;
    stretchedSurface = loadSurface("stretch.bmp");
    if(stretchedSurface == NULL)
    {
        SDL_Log( "Failed to load stretching image!\n" );
		success = false;
    }
    return success;
}

void close(){
    SDL_DestroySurface(stretchedSurface);
    stretchedSurface = NULL;
    SDL_DestroyWindow(window);
    window = NULL;
    SDL_Quit();
}

SDL_Surface* loadSurface(std::string path_to_media){
    SDL_Surface* optimizedSurface = NULL;

    SDL_Surface* loadedSurface = SDL_LoadBMP(path_to_media.c_str());
    if (loadedSurface == NULL){
        SDL_Log("faield to load media. %s\n", SDL_GetError());
    }
    else {
        optimizedSurface = SDL_ConvertSurface(loadedSurface, (*screenSurface).format);
        if( optimizedSurface == NULL )
		{
			SDL_Log( "Unable to optimize image %s! SDL Error: %s\n", path_to_media.c_str(), SDL_GetError() );
		}
        SDL_DestroySurface(loadedSurface);
    }
    return optimizedSurface;
}

int main( int argc, char* args[] )
{
	if( !init() )
	{
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
				SDL_Rect stretchRect;
				stretchRect.x = 0;
				stretchRect.y = 0;
				stretchRect.w = SCREEN_WIDTH;
				stretchRect.h = SCREEN_HEIGHT;
				SDL_BlitSurfaceScaled( stretchedSurface, NULL, screenSurface, &stretchRect, SDL_SCALEMODE_NEAREST );
                SDL_UpdateWindowSurface(window);
			}
		}
	}
	close();
	return 0;
}			