#if 0
#include <Windows.h>
#include <iostream>
#include <SDL.h>
//#include <SDL_image.h>
//#include <SDL_ttf.h>
//#include "SDL2_gfxPrimitives.h"

using namespace std;

SDL_Window* window;
SDL_Surface* surface;
SDL_Renderer* renderer;

bool SDL_Exit;
bool SDL_Update;

void SDL_Proc(SDL_Event& Event);

int main(int argc, char* argv[])
{
	//initializing
	SDL_Init(SDL_INIT_VIDEO);
	//TTF_Init();

	//Create Window
	window = SDL_CreateWindow(
		"Untitled",                //title
		SDL_WINDOWPOS_UNDEFINED,   //window position x
		SDL_WINDOWPOS_UNDEFINED,   //window position y
		680, 480,                  //window width, height
		SDL_WINDOW_OPENGL          //flags
	);


	//Event Handler
	while (!SDL_Exit) {
		SDL_Event Event;
		while (SDL_PollEvent(&Event)) {
			SDL_Proc(Event);
		}
		if (SDL_Update) {
			SDL_RenderPresent(renderer);
			SDL_RenderClear(renderer);
		}
		SDL_Update = false;
	}
	//quit
	SDL_Quit();
	//TTF_Quit();
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	return 0;
}

//SDL Event procedure
void SDL_Proc(SDL_Event& Event) {
	switch (Event.type) {
	case SDL_QUIT:
		SDL_Exit = true;
		break;
	}
}
#endif
#if 0
/*This source code copyrighted by Lazy Foo' Productions (2004-2022)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char* args[])
{
	//The window we'll be rendering to
	SDL_Window* window = NULL;

	//The surface contained by the window
	SDL_Surface* screenSurface = NULL;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		//Create window
		window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}
		else
		{
			//Get window surface
			screenSurface = SDL_GetWindowSurface(window);

			//Fill the surface white
			SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

			//Update the surface
			SDL_UpdateWindowSurface(window);

			//Hack to get window to stay up
			SDL_Event e; bool quit = false; while (quit == false) { while (SDL_PollEvent(&e)) { if (e.type == SDL_QUIT) quit = true; } }
		}
	}

	//Destroy window
	SDL_DestroyWindow(window);

	//Quit SDL subsystems
	SDL_Quit();

	return 0;
}
#endif
#if 0
#include <SDL.h>
#include <crtdbg.h>

int main(int argc, char** argv)
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);// | _CRTDBG_CHECK_ALWAYS_DF);
#endif
	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window* window = SDL_CreateWindow("My SDL Empty Window",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

	SDL_Surface* image = SDL_LoadBMP("image.bmp");

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);

	SDL_Rect dstrect = { 5, 5, 320, 240 };
	SDL_RenderCopy(renderer, texture, NULL, &dstrect);
	SDL_RenderPresent(renderer);

	SDL_Delay(3000);

	SDL_DestroyTexture(texture);
	SDL_FreeSurface(image);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();

	return 0;
}
#endif
#if 1
#include <SDL.h>   
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string.h>
#include <tchar.h>

int main(int argc, char** argv)
{
	bool quit = false;
	SDL_Event event;

	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);
	TTF_Init();

	SDL_Window* window = SDL_CreateWindow("SDL2 Displaying Image",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

	//SDL_Surface* surface1 = SDL_LoadBMP("image.bmp");
	SDL_Surface* surface1 = IMG_Load("image.png");
	SDL_Texture* texture1 = SDL_CreateTextureFromSurface(renderer, surface1);

#if 1
	//SDL_Rect dstrect = { 5, 5, 320, 240 };
	//SDL_RenderCopy(renderer, texture, NULL, &dstrect);
	SDL_SetTextureBlendMode(texture1, SDL_BlendMode::SDL_BLENDMODE_BLEND);
	SDL_RenderCopy(renderer, texture1, NULL, NULL);
	SDL_RenderPresent(renderer);
#endif

#if 1
	TTF_Font* font = TTF_OpenFont("c:/Windows/Fonts/gulim.ttc", 20);
	SDL_Color color = { 255, 0, 0 };
	//SDL_Surface* surface2 = TTF_RenderText_Solid(font, "Welcome to Gigi Labs", color);
	//SDL_Surface* surface2 = TTF_RenderUNICODE_Blended(font, (Uint16*)L"¾È³ç Welcome to Gigi Labs", color);
	SDL_Surface* surface2 = TTF_RenderUNICODE_Solid(font, (Uint16*)L"¾È³ç Welcome to Gigi Labs", color);

	SDL_Texture* texture2 = SDL_CreateTextureFromSurface(renderer, surface2);
	int texW = 0;
	int texH = 0;
	SDL_QueryTexture(texture2, NULL, NULL, &texW, &texH);
	SDL_Rect dstrect = { 0, 0, texW, texH };

	//SDL_SetTextureBlendMode(texture2, SDL_BlendMode::SDL_BLENDMODE_BLEND);
	SDL_SetTextureBlendMode(texture2, SDL_BlendMode::SDL_BLENDMODE_NONE);
	SDL_RenderCopy(renderer, texture2, NULL, &dstrect);
	SDL_RenderPresent(renderer);
#endif

#if 1
	SDL_Texture* texture3 = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, 640, 480);
	
	Uint32* pixels = new Uint32[640 * 480];	
	memset(pixels, 255, 640 * 480 * sizeof(Uint32));

	bool leftMouseButtonDown = false;
#endif

	while (!quit)
	{		
		SDL_WaitEvent(&event);

		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		case SDL_MOUSEBUTTONUP:
			if (event.button.button == SDL_BUTTON_LEFT)
				leftMouseButtonDown = false;
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT)
				leftMouseButtonDown = true;
		case SDL_MOUSEMOTION:
			if (leftMouseButtonDown)
			{
				int mouseX = event.motion.x;
				int mouseY = event.motion.y;
				pixels[mouseY * 640 + mouseX] = 0;
			}
			break;
		}		
#if 1
#if 0
		//SDL_Rect dstrect = { 5, 5, 320, 240 };
		//SDL_RenderCopy(renderer, texture, NULL, &dstrect);
		SDL_RenderCopy(renderer, texture1, NULL, NULL);
		SDL_RenderPresent(renderer);
#else
		SDL_UpdateTexture(texture3, NULL, pixels, 640 * sizeof(Uint32));
		SDL_RenderCopy(renderer, texture3, NULL, NULL);
		SDL_RenderCopy(renderer, texture1, NULL, &dstrect);		
		SDL_RenderCopy(renderer, texture2, NULL, &dstrect);
		SDL_RenderPresent(renderer);
#endif
#endif
	}

	TTF_CloseFont(font);

	delete[] pixels;

	SDL_DestroyTexture(texture1);
	SDL_DestroyTexture(texture2);
	SDL_DestroyTexture(texture3);
	SDL_FreeSurface(surface1);
	SDL_FreeSurface(surface2);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	IMG_Quit();
	TTF_Quit();
	SDL_Quit();

	return 0;
}
#endif
#if 0
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <stdbool.h>

SDL_Window* window;
SDL_Surface* windowSurface;

// Window dimensions
static const int width = 800;
static const int height = 600;

static int initAll()
{
	if (SDL_Init(SDL_INIT_EVENTS) != 0)
	{
		fprintf(stderr, "%s\n", (SDL_GetError()));
		return (0);
	}

	window = SDL_CreateWindow("Hello World", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);
	if (window == 0)
	{
		fprintf(stderr, "%s\n", (SDL_GetError()));
		return (0);
	}

	windowSurface = SDL_GetWindowSurface(window);

	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		return (0);
	}

	return (1);
}

static void closeAll()
{
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();
}

SDL_Surface* loadImage(const char* file) {
	SDL_Surface* surface;
	SDL_Surface* optimizedSurface;

	surface = IMG_Load(file);
	if (surface == NULL)
	{
		printf("fail to read %s\n", file);
		return NULL;
	}

	optimizedSurface = SDL_ConvertSurface(surface, windowSurface->format, 0);
	if (optimizedSurface == NULL)
	{
		printf("unable to optimize image %s\n", file);
		return NULL;
	}
	SDL_FreeSurface(surface);

	return optimizedSurface;
}

int main(int argc, char** argv) {
	initAll();

	SDL_Surface* image;
	image = loadImage("image.png");

#if 1
	TTF_Init();

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

	TTF_Font* font = TTF_OpenFont("arial.ttf", 25);
	SDL_Color color = { 255, 0, 0 };
	SDL_Surface* surface2 = TTF_RenderText_Solid(font, "Welcome to Gigi Labs", color);

	SDL_Texture* texture2 = SDL_CreateTextureFromSurface(renderer, surface2);
	int texW = 0;
	int texH = 0;
	SDL_QueryTexture(texture2, NULL, NULL, &texW, &texH);
	SDL_Rect dstrect = { 0, 0, texW, texH };

	SDL_SetTextureBlendMode(texture2, SDL_BlendMode::SDL_BLENDMODE_BLEND);
	//SDL_RenderCopy(renderer, texture2, NULL, &dstrect);
	//SDL_RenderPresent(renderer);
#endif

#if 1
	SDL_Rect Rect;
	Rect.x = width / 2;
	Rect.y = height / 2;
	//SDL_BlitSurface(image, NULL, windowSurface, &Rect);
	SDL_BlitSurface(image, NULL, windowSurface, NULL);
#if 0
	dstrect.x = 100;
	dstrect.y = 100;
	SDL_BlitSurface(surface2, NULL, windowSurface, &dstrect);
#endif
	SDL_UpdateWindowSurface(window);
#endif

	bool quit = false;
	SDL_Event event;
	while (!quit) {
		//SDL_Delay(10);
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				quit = true;
				break;
			}
		}
#if 1
		SDL_Rect Rect;
		Rect.x = width / 2;
		Rect.y = height / 2;
		//SDL_BlitSurface(image, NULL, windowSurface, &Rect);
		SDL_BlitSurface(image, NULL, windowSurface, NULL);
#if 1
		dstrect.x = 100;
		dstrect.y = 100;
		SDL_BlitSurface(surface2, NULL, windowSurface, &dstrect);		
#endif
		SDL_UpdateWindowSurface(window);
#endif
	}

	SDL_FreeSurface(image);

	closeAll();
	return 0;
}
#endif