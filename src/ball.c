#ifdef __linux__
#include <SDL2/SDL.h>
#endif

#ifdef _WIN32
#include "../srch/include/SDL2/SDL.h"
#endif
#include "../srch/draw.h"
#include "../srch/defs.h"
#include <stdio.h>
#include <inttypes.h>
#include "../srch/spawn.h"
#include "../srch/structs.h"
#include "../srch/hero.h"

Entity ball;

int shoot = 0;

int xSpeed = 0, ySpeed = 0;
int defaultSpeed = 4;

void start_ball(){
    shoot = 0;
    ball.x = Hero.x + 29;
    ball.y = Hero.y -16;
}

void create_ball(){
    start_ball();
    ball.texture = loadTexture("resources/sprites/ball.png");
}

void draw_ball(){
    blit(ball.texture, 2, ball.x, ball.y, 0, 0);
}

void shoot_ball(int x, int y){
    shoot = 1;
    xSpeed = x;
    ySpeed = y;
}

int ball_getX(){
    return ball.x;
}
int ball_getY(){
    return ball.y;
}

void move_ball(){
    if(shoot == 0){
        ball.x = Hero.x + 29;
        ball.y = Hero.y -16;
    }else{
        ball.y += (ySpeed*defaultSpeed);
        ball.x += xSpeed;
    }
}

void ball_getBounce(int x, int y){
    int dif = ball.x-x;
    printf("Object Y: %i Ball Y: %i Diff: %i \n", y, ball.y, dif);

    if(dif <= -10)xSpeed = -2;
    if(dif <= 2 && dif > -10)xSpeed = -1;
    if(dif > 2 && dif < 7)xSpeed = 0;
    if(dif >= 7 && dif < 11)xSpeed = 1;
    if(dif >= 12)xSpeed = 2;

    printf("%i \n", xSpeed);

    if(ball.y > y)ySpeed = 2;
    if(ball.y <= y)ySpeed = -2;
}

void ball_bounce(){
    if(ball.x + 18 >= (Hero.x+12) && ball.x <= (Hero.x + 60) &&
       ball.y + 20 >= Hero.y && ball.y <= (Hero.y + 34)){

        int dif = ball.x-Hero.x;
        if(dif <= 20)xSpeed = -2;
        if(dif > 20 && dif < 30)xSpeed = 0;
        if(dif >= 30)xSpeed = 2;
        ySpeed = -2;
        if(shoot == 1)playSound(SND_PLATFORM_BOUNCE, 1);
        return;
    }

    
    if(ball.y <= 0){
        playSound(SND_BORDER_BOUNCE, 1);
        ySpeed = 2;
    }
    if(ball.y >= app.w_Y){
        respawn();
    }
    if(ball.x >= app.w_X-18){
        playSound(SND_BORDER_BOUNCE, 1);
        xSpeed = -2;
    }
    if(ball.x <= 0){
        playSound(SND_BORDER_BOUNCE, 1);
        xSpeed = 2;
    }
}