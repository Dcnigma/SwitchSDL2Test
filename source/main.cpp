#include <iostream>
#include <random>

#include <math.h>

#include <switch.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>


#include "main.hpp"

using namespace std;

int main(int argc, char **argv)
{
	// Initialize
        SDL_Init(SDL_INIT_AUDIO);
	Mix_Init(MIX_INIT_MP3);
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);
	TTF_Init();
	romfsInit();

   // Create an SDL window & renderer
    SDL_Window* window = SDL_CreateWindow("Main-Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);


    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096);
    Mix_Music *audio = Mix_LoadMUS("romfs:/resources/Audio/test.mp3");

	// Create bg texture:
	SDL_Surface* bg_surface = IMG_Load("romfs:/resources/images/main.png");			// Read image as surface
	SDL_Texture* bg_texture = SDL_CreateTextureFromSurface(renderer, bg_surface);	// Create texture from surface

	// Create font:
	TTF_Font* font = TTF_OpenFont("romfs:/resources/fonts/small_font.ttf", 48);
	// White color
	SDL_Color color = {255, 255, 255}; 

	// Clear renderer:
	SDL_RenderClear(renderer);
 
	// Copy bg texture to renderer:
	SDL_RenderCopy(renderer, bg_texture, NULL, NULL);

	// Create text texture 1
	SDL_Surface* txt_surface = TTF_RenderText_Solid(font, "Dcnigma's SDL2 Audio and PNG test", color);
	SDL_Texture* txt_texture = SDL_CreateTextureFromSurface(renderer, txt_surface);

	SDL_Rect txt_rect;
	txt_rect.x = 50; 
	txt_rect.y = 80;
	txt_rect.w = txt_surface->w;
	txt_rect.h = txt_surface->h;

	// Create text texture 2
	SDL_Surface* txt_surface2 = TTF_RenderText_Solid(font, "Press A to start the Audio", color);
	SDL_Texture* txt_texture2 = SDL_CreateTextureFromSurface(renderer, txt_surface2);

	SDL_Rect txt_rect2;
	txt_rect2.x = 550; 
	txt_rect2.y = 230;
	txt_rect2.w = txt_surface2->w;
	txt_rect2.h = txt_surface2->h;

	// Create text texture 3
	SDL_Surface* txt_surface3 = TTF_RenderText_Solid(font, "Press + to Exit to Homebrew Menu", color);
	SDL_Texture* txt_texture3 = SDL_CreateTextureFromSurface(renderer, txt_surface3);


	SDL_Rect txt_rect3;
	txt_rect3.x = 600; 
	txt_rect3.y = 1010;
	txt_rect3.w = txt_surface3->w;
	txt_rect3.h = txt_surface3->h;

	// Create image texture 1
	SDL_Surface* icon_surface = IMG_Load("romfs:/resources/images/icon.jpg");		// Read image as surface
	SDL_Texture* icon_texture = SDL_CreateTextureFromSurface(renderer, icon_surface);	// Create texture from surface

	SDL_Rect icon_rect;
	icon_rect.x = 250; 
	icon_rect.y = 450;
	icon_rect.w = icon_surface->w;
	icon_rect.h = icon_surface->h;



	// Create text texture 4
	SDL_Surface* txt_surface4 = TTF_RenderText_Solid(font, "Music by Bartclub - Electragazan", color);
	SDL_Texture* txt_texture4 = SDL_CreateTextureFromSurface(renderer, txt_surface4);


	SDL_Rect txt_rect4;
	txt_rect4.x = 150; 
	txt_rect4.y = 750;
	txt_rect4.w = txt_surface4->w;
	txt_rect4.h = txt_surface4->h;

	// Copy text texture to renderer:
	SDL_RenderCopy(renderer, txt_texture, NULL, &txt_rect);
	SDL_RenderCopy(renderer, txt_texture2, NULL, &txt_rect2);
	SDL_RenderCopy(renderer, txt_texture3, NULL, &txt_rect3);
	SDL_RenderCopy(renderer, txt_texture4, NULL, &txt_rect4);
	// Copy image texture to renderer:
	SDL_RenderCopy(renderer, icon_texture, NULL, &icon_rect);

	// Render
	SDL_RenderPresent(renderer);						// Render renderer

	// Game loop:
	while (appletMainLoop())
	{
		// Get inputs
		hidScanInput();
		u32 controller1_keys = hidKeysDown(CONTROLLER_P1_AUTO);
	        
		if (controller1_keys & KEY_A)
                Mix_PlayMusic(audio, 1); //Play the audio file

		// On controller 1 input...PLUS
		if (controller1_keys & KEY_PLUS)
		{
			break; 	// Break out of main applet loop to exit
		}
	}
	Mix_FreeMusic(audio);
	
	// SDL cleanup
	SDL_DestroyTexture(txt_texture);
  	SDL_DestroyTexture(txt_texture2);
  	SDL_DestroyTexture(txt_texture3);
  	SDL_DestroyTexture(icon_texture);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();				
    	romfsExit();
	// Clean exit to HBMenu
	return EXIT_SUCCESS; 	
}