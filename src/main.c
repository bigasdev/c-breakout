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
#include "../srch/ball.h"
#include "../srch/sound.h"
#include "../srch/hud.h"
#include <stdio.h>
#include <string.h>

Entity storyEntity;
Entity logoEntity;
SDL_Texture *background;

void cleanup(){

}

void bg_draw(){

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
	create_ball();
	initSpawn();
	initSound();
	hud_init();

	atexit(cleanup);

	logoEntity.texture = loadTexture("resources/logo.png");
	background = loadTexture("resources/sprites/background.png");

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
	reset();

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
		move_ball();
		ball_bounce();

		animatePlayer();
		blit(background, 1, 0, 0, 0, 0);

        blit(Hero.texture, 2, Hero.x, Hero.y, 0, 0);

		for (size_t i = 0; i < list.tam; i++)
		{
			/* code */
			Entity* e = getEntity(i, list);
			if(e){
				if(e->texture != NULL){
					blit(e->texture, 2, e->x, e->y, 0, 0);
				}
				if(e->work == true)continue;
				if(e->x + 24 >= ball_getX() && e->x <= (ball_getX() + 23) &&
               		e->y + 20 >= ball_getY() && e->y <= (ball_getY() + 16))
				{
					ball_getBounce(e->x, e->y);
					e->health += 2;
					if(e->health >= 4){
						e->work = true;
					}
					playSound(SND_BLOCK_BOUNCE, 1);
					e->texture = textures[e->health];
				}
			}
		}
		for (size_t i = 0; i < wallList.tam; i++)
		{
			/* code */
			Entity* e = getEntity(i, wallList);
			if(e){
				if(e->texture != NULL){
					blit(e->texture, 2, e->x, e->y, 0, 0);
				}
				if(e->x + 24 >= ball_getX() && e->x <= (ball_getX() + 23) &&
               		e->y + 20 >= ball_getY() && e->y <= (ball_getY() + 16))
				{
					playSound(SND_WALL_BOUNCE, 1);
					ball_getBounce(e->x, e->y);
				}
			}
		}

		draw_ball();
		hud_draw();
		

		presentScene();


		SDL_Delay(16);
	}

	return 0;
}
