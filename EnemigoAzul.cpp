#include "EnemigoAzul.h"

EnemigoAzul::EnemigoAzul(SDL_Renderer* renderer, list<Personaje*> *personajes)
{
    vector<SDL_Texture*>*texturas = new vector<SDL_Texture*>();
    vector<SDL_Texture*>*texturas_left = new vector<SDL_Texture*>();

    texturas->push_back(IMG_LoadTexture(renderer,"EnemigoAzul/standing/1.png"));
    texturas->push_back(IMG_LoadTexture(renderer,"EnemigoAzul/standing/2.png"));
    texturas->push_back(IMG_LoadTexture(renderer,"EnemigoAzul/standing/3.png"));
    texturas->push_back(IMG_LoadTexture(renderer,"EnemigoAzul/standing/4.png"));

    texturas_left->push_back(IMG_LoadTexture(renderer,"EnemigoAzul/standing_left/1.png"));
    texturas_left->push_back(IMG_LoadTexture(renderer,"EnemigoAzul/standing_left/2.png"));
    texturas_left->push_back(IMG_LoadTexture(renderer,"EnemigoAzul/standing_left/3.png"));
    texturas_left->push_back(IMG_LoadTexture(renderer,"EnemigoAzul/standing_left/4.png"));

    mapa_texturas["left"]=texturas_left;
    mapa_texturas["right"]=texturas;

    vector_actual_str = "right";
    rect.x = 350;
    rect.y = 250;

    init(renderer,personajes);
}

EnemigoAzul::~EnemigoAzul()
{
    //dtor
}

void EnemigoAzul::act()
{
    if(rect.x== 750 || rect.y + rect.h == 700)
        move= true;
    else if(rect.x == -50 || rect.y == -50)
        move = false;
    if(move)
    {
        rect.x--;
        rect.y--;
    }

    else
    {
        rect.x++;
        rect.y++;
    }

    if(frame%100==0)
        atacando = true;
    else
        atacando = false;

    attackCheck();
}



