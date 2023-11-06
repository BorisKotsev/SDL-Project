#include <iostream>
#include <SDL.h>
#include <fstream>

#undef main

using namespace std;

SDL_Window* mainWindow = SDL_CreateWindow("Title",
	SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
	1366, 768, 0);

SDL_Renderer* mainRenderer = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_PRESENTVSYNC);

void improveRenderer()
{
	SDL_DisplayMode DM;
	SDL_GetCurrentDisplayMode(0, &DM);

	auto desktopWidth = DM.w;
	auto desktopHeight = DM.h;

	if (SDL_SetWindowFullscreen(mainWindow, SDL_WINDOW_FULLSCREEN_DESKTOP) < 0)
	{
		cout << "SDL Renderer improve failed!" << SDL_GetError();
	}

	SDL_RenderSetLogicalSize(mainRenderer, 1920, 1080);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
}

SDL_Texture* loadTexture(string imgPath)
{
	string tmpImg = "img\\" + imgPath;

	SDL_Surface* loadingSurface = SDL_LoadBMP(tmpImg.c_str());

	SDL_Texture* texture = SDL_CreateTextureFromSurface(mainRenderer, loadingSurface);

	if (texture == nullptr)
	{
		tmpImg = "img\\Null.bmp";

		loadingSurface = SDL_LoadBMP(tmpImg.c_str());

		texture = SDL_CreateTextureFromSurface(mainRenderer, loadingSurface);
	}

	SDL_FreeSurface(loadingSurface);

	return texture;
}

bool isMouseInRect(int mouseX, int mouseY, SDL_Rect rect) //FINISH
{
	return false;
}

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	
	improveRenderer();
	
	//Improve Renderer
	
	SDL_Rect dstRect, srcRect, imageValues;

	string imgName, temp;

	fstream stream;

	stream.open("config\\init.txt"); // Open the file

	stream >> temp >> imgName; //Read the image name
	stream >> temp >> dstRect.x >> dstRect.y >> dstRect.w >> dstRect.h; //Read the dstrect value
	stream >> temp >> srcRect.x >> srcRect.y >> srcRect.w >> srcRect.h; //Read the srcrect value
	stream >> temp >> imageValues.x >> imageValues.y >> imageValues.w >> imageValues.h; //Read the srcrect value
					//width            height           rows             cols 

	stream.close(); //Close the file

	int xMargin = imageValues.x / imageValues.h;
	int yMargin = imageValues.y / imageValues.w;

	SDL_Texture* vikingTexture = loadTexture(imgName);

	SDL_Event sdlEvent;

	bool isRunning = true;

	int escapeCode = 41;

	while (isRunning)
	{
		while (SDL_PollEvent(&sdlEvent))
		{
			switch (sdlEvent.type)
			{
			case SDL_QUIT:
				isRunning = false;
				break;
			case SDL_KEYDOWN:
				if (sdlEvent.key.keysym.scancode == SDL_Scancode(escapeCode))
				{
					SDL_Quit(); // doesnt close the console
					//isRunning = false; //closes everything
				}
				break;
			case SDL_MOUSEMOTION:
				cout << sdlEvent.motion.x << " " << sdlEvent.motion.y << endl;

				SDL_SetRenderDrawColor(mainRenderer, sdlEvent.motion.x, sdlEvent.motion.y, 100, 255);
				break;
			default:
				break;
			}
		}
		SDL_RenderClear(mainRenderer);
		SDL_RenderPresent(mainRenderer);
	}

	/*while(true)
	{ 
		SDL_RenderCopy(mainRenderer, vikingTexture, NULL, &dstRect); 

		SDL_RenderPresent(mainRenderer); // Draw the render
		if (srcRect.y <= yMargin * 2) 
		{
			srcRect.x += xMargin;
		}

		if (srcRect.x > xMargin * 2 && srcRect.y == 0) //Row 1
		{
			srcRect.y += yMargin;
			srcRect.x = 0;
		}

		if (srcRect.x > xMargin * 7 && srcRect.y == yMargin) //Row 2
		{
			srcRect.y += yMargin;
			srcRect.x = 0;
		}
		 
		if (srcRect.x > xMargin * 7 && srcRect.y == yMargin * 2) //Row 3
		{
			srcRect.y += yMargin;
			srcRect.x = 0;
		}

		SDL_RenderClear(mainRenderer); // Clear what you have drawn
		SDL_Delay(100); // Slow the program
	}*/

	return 0;
}
