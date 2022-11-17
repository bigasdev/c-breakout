#ifdef __linux__
#include <SDL2/SDL.h>
#endif

#ifdef _WIN32
#include "../srch/include/SDL2/SDL.h"
#endif

#include "../srch/structs.h"
#include "../srch/spawn.h"
#include "../srch/defs.h"
#include "../srch/draw.h"
#include "../srch/hero.h"
#include "../srch/sound.h"
#include <stdio.h>
#include <stdlib.h>

List list;

void initSpawn(){
    list.start = NULL;
    list.tam = 0;

    for (size_t i = 0; i < STUDENTS_AMOUNT; i++)
    {
        /* code */
        addEntity();
    }
    
}

void addEntity(){
    Entity *new = malloc(sizeof(Entity));

    if(new){
        int t = rand() % 6;
        int x = rand() % 835;
        int y = rand() % 235;

        int negativeX = rand() % 2;
        int negativeY = rand() % 2;

        if(negativeX == 0)
            x = -x;
        

        new->next = list.start;
        new->type = t;
        new->x = x;
        new->y = y;
        new->id = list.tam;
        new->texture = loadTexture("resources/sprites/block.png");
        list.start = new;
        list.tam++;
    }else{
        printf("Erro ao alocar memoria! \n");
    }
}

Entity* getEntity(int num){
    Entity *aux = NULL;

    aux = list.start;
    if(aux->id == num){
        return aux;
    }else{
        while(aux->next && aux->next->id != num){
            aux = aux->next;
        }
        if(aux->next->id == num){
            return aux;
        }
    }
    return NULL;
}

