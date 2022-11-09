#ifdef __linux__
#include <SDL2/SDL.h>
#endif

#ifdef _WIN32
#define SDL_MAIN_HANDLED
#include "../srch/include/SDL2/SDL.h"
#endif
#include "../srch/init.h"
#include "../srch/draw.h"
#include "../srch/spawn.h"
#include "../srch/defs.h"
#include "../srch/splash.h"
#include "../srch/input.h"
#include "../srch/structs.h"
#include "../srch/hero.h"
#include "../srch/sound.h"
#include <stdio.h>
#include <string.h>

Entity storyEntity;
Entity logoEntity;

void cleanup(){

}

void start(){
	memset(&app, 0, sizeof(App));
    memset(&Hero, 0, sizeof(Entity));
	memset(&storyEntity, 0, sizeof(Entity));
	memset(&logoEntity, 0, sizeof(Entity));
#if SPLASH
	memset(&splash, 0, sizeof(UI_Entity));
	splashState = 0;
#endif

	initSDL();
	createHero();
	initSpawn();
	initSound();
	atexit(cleanup);

	logoEntity.texture = loadTexture("resources/logo.png");

	storyEntity.texture = loadTexture("resources/intro.png");
	storyEntity.y = app.w_Y  + 10;
	storyEntity.x = (app.w_X/2)+100;
	storyEntity.moveSpeed = 2;

#if SPLASH
	initSplash();
#endif
}


int main(int argc, char *argv[]){
	start();

	//splash screen loop
#if SPLASH
	playSound(0, 0);
	while(!splashState)
	{
		prepareScene();

		doInput();

		splashInput();

		blit(splash.texture, 4, 0, 0, 1, 1);

		presentScene();

		SDL_Delay(32);
	}
	loadMusic("resources/sounds/intro.ogg");
	playMusic(0);
#endif
	/*int i = 0;
	while(storyEntity.y >= 0){
		prepareScene();

		doInput();

		if(i <= 120){
			blit(logoEntity.texture, 4, logoEntity.x, logoEntity.y, 1, 0);
			i++;
		}

		blit(storyEntity.texture, 4, storyEntity.x, storyEntity.y, 0, 1);
		storyEntity.y -= storyEntity.moveSpeed;

		presentScene();	

		SDL_Delay(64);
	}*/
	
	//main loop
	while (1)
	{
        
		prepareScene();

		doInput();

		playerInputs();

		animatePlayer();
        blit(Hero.texture, 2, Hero.x, Hero.y, 0, 0);

		for (size_t i = 0; i < list.tam; i++)
		{
			/* code */
			Entity* e = getEntity(i);
			if(e){
				if(e->texture != NULL){
					printf("Drawing this entity...");
					blit(e->texture, 2, e->x, e->y, 0, 0);
				}
				if(e->x + 19 >= Hero.x && e->x <= (Hero.x + 22) &&
               		e->y + 23 >= Hero.y && e->y <= (Hero.y + 24))
				{
					e->texture = NULL;
				}
			}
		}
		

		presentScene();


		SDL_Delay(16);
	}

	return 0;
}
