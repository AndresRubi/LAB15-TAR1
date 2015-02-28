
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<iostream>
#include<vector>
#include<list>
#include "Sho.h"
#include "EnemigoAzul.h"
#include "EnemigoVerde.h"
#include "EnemigoRojo.h"
#include <SDL2/SDL_mixer.h>


using namespace std;

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Event Event;
SDL_Texture *background,*win_lose, *pause;
SDL_Rect rect_background, rect_win_loose,rect_pause;
Mix_Music *music= NULL;
Mix_Chunk *sound= NULL;

int main( int argc, char* args[] )
{
    //Init SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        return 10;
    }
    //Creates a SDL Window
    if((window = SDL_CreateWindow("Image Loading", 100, 100, 1024/*WIDTH*/, 768/*HEIGHT*/, SDL_WINDOW_RESIZABLE | SDL_RENDERER_PRESENTVSYNC)) == NULL)
    {
        return 20;
    }
    //SDL Renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED );
    if (renderer == NULL)
    {
        std::cout << SDL_GetError() << std::endl;
        return 30;
    }

    //Init textures
    int w=0,h=0;
    background = IMG_LoadTexture(renderer,"fondo.png");
    SDL_QueryTexture(background, NULL, NULL, &w, &h);
    rect_background.x = 0;
    rect_background.y = 0;
    rect_background.w = w;
    rect_background.h = h;

    pause=(IMG_LoadTexture(renderer,"pause.png"));
    SDL_QueryTexture(pause, NULL, NULL, &w, &h);
    rect_pause.x=0;
    rect_pause.y=0;
    rect_pause.w=w;
    rect_pause.h=h;

    win_lose=(IMG_LoadTexture(renderer,"BG.png"));
    rect_win_loose.x=0;
    rect_win_loose.y=0;
    rect_win_loose.w=w;
    rect_win_loose.h=h;




    if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048)<0)
    {
        printf("SDL_mixer Error %s\n", SDL_GetError());
    }
    music=Mix_LoadMUS("Gray Trip.ogg");
    if(music == NULL)
    {
        printf("coulnt load  Error %s\n", Mix_GetError());
    }

    list<Personaje*> personajes;
    personajes.push_back(new Sho(renderer,&personajes));
    personajes.push_back(new EnemigoAzul(renderer,&personajes));
    personajes.push_back(new EnemigoVerde(renderer,&personajes));
    personajes.push_back(new EnemigoRojo(renderer,&personajes));

    bool pausa;
    //Main Loop
    int frame=0;
    int animacion_sho = 0;
    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
    while(true)
    {
        while(SDL_PollEvent(&Event))
        {
            if(Event.type == SDL_QUIT)
            {
                return 0;
            }
        }
        if(currentKeyStates[SDL_SCANCODE_ESCAPE])
        {
            return 0;
        }

        if(currentKeyStates[SDL_SCANCODE_M])
        {
            if(Mix_PlayingMusic()==0)
            {
                Mix_PlayMusic(music,-1);
            }
            else
            {
                if(Mix_PausedMusic()==1)
                {
                    Mix_ResumeMusic();
                }
                else
                {
                    Mix_PauseMusic();
                }
            }
        }
        if(currentKeyStates[SDL_SCANCODE_L])
        {
            if(pausa==false)
                pausa=true;
//            else if(pausa==false)
//                pausa=true;
//            cout<<pausa<<endl;
//            if(pausa)
//            {

                cout<<"hola"<<endl;
//            }else if(pausa==false)
//            {
//                pause==NULL;
//            }


        }

        if(pausa)
            SDL_RenderCopy(renderer, pause, NULL, &rect_pause);



//        if(frame%200==0)
//        {
//            personajes.push_back(new EnemigoAzul(renderer,&personajes));
//        }

        for(list<Personaje*>::iterator p=personajes.begin();
                p!=personajes.end();
                p++)
            (*p)->act();

        SDL_SetRenderDrawColor(renderer, 255, 100, 0, 255);

        // Clear the entire screen to our selected color.
        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, background, NULL, &rect_background);

        for(list<Personaje*>::iterator p=personajes.begin();
                p!=personajes.end();
                p++)
            (*p)->draw(renderer);

        for(list<Personaje*>::iterator p=personajes.begin();
                p!=personajes.end();
                p++)
            if((*p)->muerto)
            {
                personajes.erase(p);
                p--;

            }
        for(list<Personaje*>::iterator p=personajes.begin();
                p!=personajes.end();
                p++)
                {
                    if((*p)->ganastes)
                    {
                        SDL_RenderCopy(renderer, win_lose, NULL, &rect_win_loose);
                    }
                    if((*p)->perdistes)
                    {
                         win_lose=(IMG_LoadTexture(renderer,"derrota.png"));
                        SDL_RenderCopy(renderer, win_lose, NULL, &rect_win_loose);

                    }
                }

        SDL_RenderPresent(renderer);

        frame++;
    }
    Mix_FreeMusic(music);
    music=NULL;


	return 0;
}




