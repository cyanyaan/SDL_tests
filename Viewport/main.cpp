#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <string>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool init();
bool loadMedia();
void close();

SDL_Texture* loadTexture( std::string path );
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Texture* gTexture = NULL;

bool init()
{
	bool success = true;

	if( !SDL_Init( SDL_INIT_VIDEO ) )
	{
		SDL_Log( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		if( !SDL_CreateWindowAndRenderer( "SDL Tutorial", SCREEN_WIDTH, SCREEN_HEIGHT, 0, &gWindow, &gRenderer ) )
		{
			SDL_Log( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
		}
	}

	return success;
}

SDL_Texture* loadTexture( std::string path )
{
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		SDL_Log( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), SDL_GetError() );
	}
	else
	{
		newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			SDL_Log( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		SDL_DestroySurface( loadedSurface );
	}

	return newTexture;
}


bool loadMedia()
{
	bool success = true;

	gTexture = loadTexture( "viewport.png" );
	if( gTexture == NULL )
	{
		SDL_Log( "Failed to load texture image!\n" );
		success = false;
	}
	return success;
}

int main( int argc, char* args[] )
{
	//Start up SDL and create window
	if( !init() )
	{
		SDL_Log( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			SDL_Log( "Failed to load media!\n" );
		}
		else
		{	
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//While application is running
			while( !quit )
			{
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_EVENT_QUIT )
					{
						quit = true;
					}
				}

                SDL_Rect topLeftViewPort;
                topLeftViewPort.x = 0;
                topLeftViewPort.y = 0;
                topLeftViewPort.w = SCREEN_WIDTH/2;
                topLeftViewPort.h = SCREEN_HEIGHT/2;
                SDL_SetRenderViewport(gRenderer, &topLeftViewPort);

                SDL_RenderTexture(gRenderer, gTexture, NULL, NULL);


                SDL_Rect topRightViewport;
                topRightViewport.x = SCREEN_WIDTH/2;
                topRightViewport.y = 0;
                topRightViewport.w = SCREEN_WIDTH/2;
                topRightViewport.h = SCREEN_HEIGHT/2;
                SDL_SetRenderViewport(gRenderer, &topRightViewport);

                SDL_RenderTexture(gRenderer, gTexture, NULL, NULL);
                
                SDL_Rect bottomViewport;
                bottomViewport.x = 0;
                bottomViewport.y = SCREEN_HEIGHT/2;
                bottomViewport.w = SCREEN_WIDTH;
                bottomViewport.h = SCREEN_HEIGHT/2;
                SDL_SetRenderViewport(gRenderer, &bottomViewport);

                SDL_RenderTexture(gRenderer, gTexture, NULL, NULL);

                SDL_RenderPresent(gRenderer);
            }
        }
    }
}