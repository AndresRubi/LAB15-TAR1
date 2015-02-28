#include "Sho.h"

Sho::Sho(SDL_Renderer* renderer,list<Personaje*> *personajes)
{
    mapa_texturas["left"] = new vector<SDL_Texture*>();
    mapa_texturas["right"] = new vector<SDL_Texture*>();
    mapa_texturas["walk_right"] = new vector<SDL_Texture*>();
    mapa_texturas["walk_left"] = new vector<SDL_Texture*>();

    mapa_texturas["right"]->push_back(IMG_LoadTexture(renderer,"Sho/standing/1.png"));
    mapa_texturas["right"]->push_back(IMG_LoadTexture(renderer,"Sho/standing/2.png"));
    mapa_texturas["right"]->push_back(IMG_LoadTexture(renderer,"Sho/standing/3.png"));
    mapa_texturas["right"]->push_back(IMG_LoadTexture(renderer,"Sho/standing/4.png"));

    mapa_texturas["left"]->push_back(IMG_LoadTexture(renderer,"Sho/standing_left/1.png"));
    mapa_texturas["left"]->push_back(IMG_LoadTexture(renderer,"Sho/standing_left/2.png"));
    mapa_texturas["left"]->push_back(IMG_LoadTexture(renderer,"Sho/standing_left/3.png"));
    mapa_texturas["left"]->push_back(IMG_LoadTexture(renderer,"Sho/standing_left/4.png"));

    mapa_texturas["walk_right"]->push_back(IMG_LoadTexture(renderer,"Sho/walk/1.png"));
    mapa_texturas["walk_right"]->push_back(IMG_LoadTexture(renderer,"Sho/walk/2.png"));
    mapa_texturas["walk_right"]->push_back(IMG_LoadTexture(renderer,"Sho/walk/3.png"));
    mapa_texturas["walk_right"]->push_back(IMG_LoadTexture(renderer,"Sho/walk/4.png"));
    mapa_texturas["walk_right"]->push_back(IMG_LoadTexture(renderer,"Sho/walk/5.png"));

    mapa_texturas["walk_left"]->push_back(IMG_LoadTexture(renderer,"Sho/walk_left/1.png"));
    mapa_texturas["walk_left"]->push_back(IMG_LoadTexture(renderer,"Sho/walk_left/2.png"));
    mapa_texturas["walk_left"]->push_back(IMG_LoadTexture(renderer,"Sho/walk_left/3.png"));
    mapa_texturas["walk_left"]->push_back(IMG_LoadTexture(renderer,"Sho/walk_left/4.png"));
    mapa_texturas["walk_left"]->push_back(IMG_LoadTexture(renderer,"Sho/walk_left/5.png"));


    vector_actual_str = "right";
    perdistes=false;
    rect.x = 0;
    rect.y = 0;
    id="player";
    vida=4;
    init(renderer,personajes);
}

void Sho::act()
{

    if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048)<0)
    {
        printf("SDL_mixer Error %s\n", SDL_GetError());
    }
    kick=Mix_LoadWAV("kick.wav");
    if(kick ==  NULL)
    {
        printf("coulnt load  Error %s\n", Mix_GetError());
    }


    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

    atacando = currentKeyStates[SDL_SCANCODE_SPACE];
    if(currentKeyStates[SDL_SCANCODE_SPACE])
    {
        Mix_PlayChannel(-1,kick,0);
    }

    if(currentKeyStates[SDL_SCANCODE_W])
    {
        if(rect.y>0)
            rect.y--;
    }
    else if(currentKeyStates[SDL_SCANCODE_S])
    {
        if(rect.y<220)
            rect.y++;
    }

    if(currentKeyStates[SDL_SCANCODE_D])
    {
        if(rect.x<800)
            rect.x++;
        setAnimacion("walk_right");
    }
    else if(currentKeyStates[SDL_SCANCODE_Z])
    {
        if(rect.x>0)
            rect.x--;
        setAnimacion("walk_left");
    }
    else
    {
        if(vector_actual_str == "walk_right")
            vector_actual_str = "right";

        if(vector_actual_str == "walk_left")
            vector_actual_str = "left";
    }
//    cout<<perdistes<<endl;
    attackCheck();
    if(attackCheck())
    {
        pentaKill+=1;
        cout<<"llevas : "<<pentaKill<<"/3 para ganar"<<endl;
        if(pentaKill== 3)
            ganastes=true;
    }
    if(muerto)
        perdistes=true;

//    if(pentaKill==3)
//        {
//            cout<<"Ganastes"<<pentaKill<<endl;
//        }
}

Sho::~Sho()
{
    //dtor
}
