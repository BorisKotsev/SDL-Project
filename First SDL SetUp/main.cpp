#include <iostream>
#include <SDL.h>

#undef main

using namespace std;

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	
	SDL_Window* mainWindow = SDL_CreateWindow("Title", 
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
		1920, 1080, 0);

	SDL_Renderer* mainRenderer = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_PRESENTVSYNC); 
		
	SDL_SetRenderDrawColor(mainRenderer, 17, 242, 47, 255); //Backgorund
	SDL_RenderClear(mainRenderer); //Clear the render

	SDL_SetRenderDrawColor(mainRenderer, 0, 0, 255, 20);// The color of the line
	SDL_RenderDrawLine(mainRenderer, 480, 360, 1200, 720);
	SDL_RenderDrawLine(mainRenderer, 120, 360, 1200, 720);

	SDL_Surface* surface = SDL_LoadBMP("img\\background.bmp");
	SDL_Texture* background = SDL_CreateTextureFromSurface(mainRenderer, surface);
	SDL_FreeSurface(surface);

	surface = SDL_LoadBMP("img\\snimka.bmp");
	SDL_Texture* texture2 = SDL_CreateTextureFromSurface(mainRenderer, surface);
	SDL_FreeSurface(surface);
	
	SDL_RenderCopy(mainRenderer, background, NULL, NULL); 

	SDL_Rect dstRect = {300, 300, 225, 225};
	SDL_RenderCopy(mainRenderer, texture2, NULL, &dstRect);

	SDL_Rect srcRect;

	srcRect.x = 200;
	srcRect.y = 200;
	srcRect.w = 600;
	srcRect.h = 600;

	surface = SDL_LoadBMP("img\\art.bmp");
	SDL_Texture* texture3 = SDL_CreateTextureFromSurface(mainRenderer, surface);
	SDL_FreeSurface(surface);

	SDL_RenderCopy(mainRenderer, texture3, &srcRect, &dstRect);

	SDL_Rect vikingDstRect = { 500, 500, 220, 170};
	SDL_Rect vikingSrcRect = {0, 0, 22, 17};

	surface = SDL_LoadBMP("img\\LEFT.bmp");
	SDL_Texture* viking = SDL_CreateTextureFromSurface(mainRenderer, surface);
	SDL_FreeSurface(surface);

	while(true)
	{ 
		SDL_RenderCopy(mainRenderer, viking, &vikingSrcRect, &vikingDstRect);

		vikingSrcRect.x += 22;
		vikingDstRect.x += 22;

		if (vikingDstRect.x > 1920)
		{
			vikingDstRect.x = 100;
		}

		if (vikingSrcRect.x > 176)
		{
			vikingSrcRect.x = 0;
		}

		SDL_RenderPresent(mainRenderer); // Draw the render

		SDL_RenderClear(mainRenderer); // Clear what you have drawn
		SDL_Delay(70); // Slow the program
	}


	SDL_Delay(10000);

	return 0;
}
