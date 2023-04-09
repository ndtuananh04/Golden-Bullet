#include "Game.h"
#include <iostream>
#include <cstdlib>
#include <Object.h>
#include<string.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
Game* Game::m_pGame = 0;
SDL_Rect sung,tam;
Mix_Chunk *mshot = NULL;
Mix_Chunk *mreload = NULL;
Mix_Music *mmusic = NULL;

 SDL_Texture* Game::str_to_texture(std::string str){
 SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, str.c_str(), {0,0,0} );
 SDL_Texture* textTexture = SDL_CreateTextureFromSurface(m_pRenderer,textSurface);
 tWidth=textSurface->w;
 tHeight =textSurface->h;
 SDL_FreeSurface(textSurface);
 return textTexture;
}
bool Game::init(const char* title, int xpos, int ypos, int width, int height, int flags)
{
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
    std::cout << "SDL init success\n";
    m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
    if(m_pWindow != 0) // window init success
    {
    std::cout << "window creation success\n";
    m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_PRESENTVSYNC);
    if(m_pRenderer != 0) // renderer init success
    {
    std::cout << "renderer creation success\n";
    SDL_SetRenderDrawColor(m_pRenderer,0,0,0,255);}
    else
    {
    std::cout << "renderer init fail\n";
    return false; // renderer init fail
    }
    }
    else
    {
    std::cout << "window init fail\n";
    return false; // window init fail
    }
    }
    else
    {
    std::cout << "SDL init fail\n";
    return false; // SDL init fail
        }

    m_bRunning = true;
        TTF_Init();
        gFont = TTF_OpenFont( "OpenSans-Regular.ttf", 28 );
        Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 );
        mmusic = Mix_LoadMUS("assets/HEROICCC.mp3");
        Mix_PlayMusic( mmusic, -1 );
        mshot = Mix_LoadWAV("assets/shot.wav");
        mreload = Mix_LoadWAV("assets/reload.wav");
    TheTexture::Instance()->load("Assets/bg.png","01",m_pRenderer);
    TheTexture::Instance()->load("Assets/complete.png","99",m_pRenderer);
    TheTexture::Instance()->load("Assets/start.png","51",m_pRenderer);
    TheTexture::Instance()->load("Assets/quit.png","52",m_pRenderer);
    TheTexture::Instance()->load("Assets/phantom.png","02",m_pRenderer);
    TheTexture::Instance()->load("Assets/phantom2.png","22",m_pRenderer);
    TheTexture::Instance()->load("Assets/crosshair.png","03",m_pRenderer);
    TheTexture::Instance()->load("Assets/enemy1.png","31",m_pRenderer);
    TheTexture::Instance()->load("Assets/enemy2.png","32",m_pRenderer);
    TheTexture::Instance()->load("Assets/enemy3.png","33",m_pRenderer);
    TheTexture::Instance()->load("Assets/map1.png","05",m_pRenderer);
    TheTexture::Instance()->load("Assets/11.png","11",m_pRenderer);
    TheTexture::Instance()->load("Assets/12.png","12",m_pRenderer);
    TheTexture::Instance()->load("Assets/13.png","13",m_pRenderer);
    TheTexture::Instance()->load("Assets/14.png","14",m_pRenderer);
    wall1 = new Object(200,200,-26,320,"11",175,340,65,130,"31","32","33",10);
    wall2 = new Object(380,278,472,174,"12",414,215,53,106,"31","32","33",10);
    wall3 = new Object(291,193,979,326,"13",909,346,65,130,"31","32","33",10);
    wall4 = new Object(203,204,1040,520,"14",1050,370,122,244,"31","32","33",10);
    std::cout << "init success\n";
    return true;
}

void Game::update()
{
    SDL_GetMouseState( &x1, &y1 );
    if(status==2){
    wall1->update();
    wall2->update();
    wall3->update();
    wall4->update();

    sung.x=640+x1/3;
    sung.y=360+y1/3;
    sung.w=640;
    sung.h=360;
    tam.x=x1-20;
    tam.y=y1-20;
    tam.w=40;
    tam.h=40;

    if(statusammo==2&&SDL_GetTicks()-timee>2000){
            ammo=20;
            statusammo=1;
    }
}
}

void Game::render()
{

    if(status==1){
        SDL_RenderClear(m_pRenderer);
        SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 255, 255);
        SDL_RenderCopy(m_pRenderer,TheTexture::Instance()->getTexture("01"),NULL,NULL);
        SDL_RenderCopy(m_pRenderer,TheTexture::Instance()->getTexture("51"),NULL,&st);
        SDL_RenderCopy(m_pRenderer,TheTexture::Instance()->getTexture("52"),NULL,&qu);
        /*for( int i = 0; i < BUTTON_SPRITE_TOTAL; ++i )
		{
			gSpriteClips[ i ].x = i*60;
			gSpriteClips[ i ].y = 0;
			gSpriteClips[ i ].w = BUTTON_WIDTH;
			gSpriteClips[ i ].h = BUTTON_HEIGHT;
		}*/
        SDL_RenderPresent(m_pRenderer);
        SDL_RenderClear(m_pRenderer);
    }
    if(status==2){

        SDL_RenderClear(m_pRenderer);
        SDL_RenderCopy(m_pRenderer,TheTexture::Instance()->getTexture("05"),NULL, NULL);
        wall1->render();
        wall2->render();
        wall3->render();
        wall4->render();
        if(statusammo!=2){
            if(ss==false){SDL_RenderCopy(m_pRenderer,TheTexture::Instance()->getTexture("22"),NULL, &sung);}
            else{SDL_RenderCopy(m_pRenderer,TheTexture::Instance()->getTexture("02"),NULL, &sung);}
        }
        SDL_RenderCopy(m_pRenderer,TheTexture::Instance()->getTexture("03"),NULL, &tam);
        SDL_Texture* thp= str_to_texture("HP: "+std::to_string(hp));
        SDL_Texture* tsc= str_to_texture("Score: "+std::to_string(score));
        SDL_Texture* tam= str_to_texture("Ammo: "+std::to_string(ammo)+"/20");
        SDL_Rect hpp{5,5,tWidth,tHeight};
        SDL_Rect scc{5,30,tWidth,tHeight};
        SDL_Rect amm{5,55,tWidth,tHeight};
        SDL_RenderCopy(m_pRenderer,thp,NULL,&hpp);
        SDL_RenderCopy(m_pRenderer,tsc,NULL,&scc);
        SDL_RenderCopy(m_pRenderer,tam,NULL,&amm);
        SDL_RenderPresent(m_pRenderer);
    }
    if(status==3){
        SDL_RenderClear(m_pRenderer);
        SDL_RenderCopy(m_pRenderer,TheTexture::Instance()->getTexture("99"),NULL, NULL);
        SDL_RenderPresent(m_pRenderer);
    }
}

void Game::handleEvents()
{
    SDL_Event event;
    while(SDL_PollEvent(&event)!=0)
        {
        if(event.type == SDL_QUIT)
        {
           m_bRunning=false;
        }
        if(event.type == SDL_MOUSEBUTTONDOWN){
            if(status==2&&statusammo==1){
                ss=false;
                trudan();
                wall1->shooted(x1,y1);
                wall2->shooted(x1,y1);
                wall3->shooted(x1,y1);
                wall4->shooted(x1,y1);
                Mix_PlayChannel( -1, mshot,0 );
            }
            if(x1>900&&x1<1100&&y1>390&&y1<465){status=2;}
            if(x1>900&&x1<1100&&y1>490&&y1<565){m_bRunning=false;}
        }
        if(event.type == SDL_MOUSEBUTTONUP){
            ss=true;
        }
        if(event.type == SDL_KEYDOWN )
                {
                    switch( event.key.keysym.sym )
                    {
                        case SDLK_t:
                            if( Mix_PlayingMusic() == 0 )
                            {
                                Mix_PlayMusic( mmusic, -1 );
                            }
                            else
                            {
                                if( Mix_PausedMusic() == 1 )
                                {
                                    Mix_ResumeMusic();
                                }
                                else
                                {
                                    Mix_PauseMusic();
                                }
                            }
                            break;

                        case SDLK_y:
                        Mix_HaltMusic();
                        break;

                        case SDLK_r:
                            statusammo=2;
                            timee=SDL_GetTicks();
                            Mix_PlayChannel( -1, mreload,0 );
                        break;

                    }
                }
        }
}


void Game::clean()
{
    std::cout<< "cleaning game\n";
    TTF_CloseFont(gFont);
    gFont=NULL;
    Mix_FreeChunk(mreload);
    mreload=NULL;
    Mix_FreeChunk(mshot);
    mshot = NULL;
    Mix_FreeMusic(mmusic);
    mmusic = NULL;
    SDL_DestroyWindow(m_pWindow);
    SDL_DestroyRenderer(m_pRenderer);
    IMG_Quit();
    Mix_Quit();
    SDL_Quit();
}
