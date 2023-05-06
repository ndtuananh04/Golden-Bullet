#include "Game.h"
#include <iostream>
#include <cstdlib>
#include <Object.h>
#include<string.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
Game* Game::m_pGame = 0;

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
        if(m_pWindow != 0)
        {
            std::cout << "window creation success\n";
            m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_PRESENTVSYNC);
            if(m_pRenderer != 0)
            {
                std::cout << "renderer creation success\n";
                SDL_SetRenderDrawColor(m_pRenderer,0,0,0,255);}
                else
            {
                std::cout << "renderer init fail\n";
                return false;
            }
        }
        else
        {
            std::cout << "window init fail\n";
            return false;
        }
    }
    else
    {
        std::cout << "SDL init fail\n";
        return false;
    }
    m_bRunning = true;
        TTF_Init();
        gFont = TTF_OpenFont( "OpenSans-Regular.ttf", 28 );
        Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 );
        mmusic = Mix_LoadMUS("assets/HEROICCC.mp3");
        mplay = Mix_LoadMUS("assets/playing.mp3");
        mwin = Mix_LoadMUS("assets/win.mp3");
        mfail = Mix_LoadMUS("assets/fail.mp3");
        Mix_PlayMusic( mmusic, 2 );
        mshot = Mix_LoadWAV("assets/shot.wav");
        mreload = Mix_LoadWAV("assets/reload.wav");
    TheTexture::Instance()->load("Assets/bg.png","01",m_pRenderer);
    TheTexture::Instance()->load("Assets/complete.png","99",m_pRenderer);
    TheTexture::Instance()->load("Assets/failed.png","98",m_pRenderer);
    TheTexture::Instance()->load("Assets/stagecom.png","97",m_pRenderer);
    TheTexture::Instance()->load("Assets/start.png","51",m_pRenderer);
    TheTexture::Instance()->load("Assets/quit.png","52",m_pRenderer);
    TheTexture::Instance()->load("Assets/replay.png","53",m_pRenderer);
    TheTexture::Instance()->load("Assets/nextstagebtn.png","54",m_pRenderer);
    TheTexture::Instance()->load("Assets/menubtn.png","55",m_pRenderer);
    TheTexture::Instance()->load("Assets/phantom.png","71",m_pRenderer);
    TheTexture::Instance()->load("Assets/phantom2.png","72",m_pRenderer);
    TheTexture::Instance()->load("Assets/crosshair.png","03",m_pRenderer);
    TheTexture::Instance()->load("Assets/enemy1.png","31",m_pRenderer);
    TheTexture::Instance()->load("Assets/enemy2.png","32",m_pRenderer);
    TheTexture::Instance()->load("Assets/enemy3.png","33",m_pRenderer);
    TheTexture::Instance()->load("Assets/map1.png","05",m_pRenderer);
    TheTexture::Instance()->load("Assets/map2.png","06",m_pRenderer);
    TheTexture::Instance()->load("Assets/map3.png","07",m_pRenderer);
    TheTexture::Instance()->load("Assets/11.png","11",m_pRenderer);
    TheTexture::Instance()->load("Assets/12.png","12",m_pRenderer);
    TheTexture::Instance()->load("Assets/13.png","13",m_pRenderer);
    TheTexture::Instance()->load("Assets/14.png","14",m_pRenderer);
    TheTexture::Instance()->load("Assets/15.png","15",m_pRenderer);
    TheTexture::Instance()->load("Assets/16.png","16",m_pRenderer);
    TheTexture::Instance()->load("Assets/17.png","17",m_pRenderer);
    TheTexture::Instance()->load("Assets/18.png","18",m_pRenderer);
    TheTexture::Instance()->load("Assets/19.png","19",m_pRenderer);
    TheTexture::Instance()->load("Assets/20.png","20",m_pRenderer);
    TheTexture::Instance()->load("Assets/21.png","21",m_pRenderer);
    TheTexture::Instance()->load("Assets/22.png","22",m_pRenderer);
    TheTexture::Instance()->load("Assets/23.png","23",m_pRenderer);

    wall1 = new Object(200,200,-26,320,"11",175,340,65,130,"31","32","33",10);
    wall2 = new Object(380,278,472,174,"12",414,215,53,106,"31","32","33",10);
    wall3 = new Object(291,193,979,326,"13",909,346,65,130,"31","32","33",10);
    wall4 = new Object(203,204,1040,520,"14",1050,370,122,244,"31","32","33",10);

    wall5 = new Object(100,190,140,433,"15",90,395,95,190,"31","32","33",10);
    wall6 = new Object(32,17,467,284,"16",470,245,28,56,"31","32","33",10);
    wall7 = new Object(103,142,662,206,"17",635,244,42,84,"31","32","33",10);
    wall8 = new Object(24,122,869,326,"18",888,330,45,90,"31","32","33",10);
    wall9 = new Object(20,80,1167,235,"19",1140,237,38,76,"31","32","33",10);

    wall10 = new Object(47,19,348,156,"20",362,113,27,54,"31","32","33",10);
    wall11 = new Object(86,60,313,565,"21",324,480,68,136,"31","32","33",10);
    wall12 = new Object(30,41,682,549,"22",692,490,48,96,"31","32","33",10);
    wall13 = new Object(124,150,1156,570,"23",1129,447,126,252,"31","32","33",10);

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
    }
    if(status==3){
        wall10->update();
        wall11->update();
        wall12->update();
        wall13->update();
        sung.x=640+x1/3;
        sung.y=360+y1/3;
        sung.w=640;
        sung.h=360;
        tam.x=x1-20;
        tam.y=y1-20;
        tam.w=40;
        tam.h=40;
    }
    if(status==4){
        wall5->update();
        wall6->update();
        wall7->update();
        wall8->update();
        wall9->update();
        sung.x=640+x1/3;
        sung.y=360+y1/3;
        sung.w=640;
        sung.h=360;
        tam.x=x1-20;
        tam.y=y1-20;
        tam.w=40;
        tam.h=40;
    }

    if(statusammo==2&&SDL_GetTicks()-timee>2000){
            if(totalammo>=0){
                totalammo-=(20-ammo);
            }
            if(totalammo>=0){
                ammo=20;
            } else{ammo=20+totalammo; totalammo=0;}
            statusammo=1;
    }
}

void Game::render()
{

    if(status==1){ //start
        SDL_RenderClear(m_pRenderer);
        SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 255, 255);
        SDL_RenderCopy(m_pRenderer,TheTexture::Instance()->getTexture("01"),NULL,NULL);
        SDL_RenderCopy(m_pRenderer,TheTexture::Instance()->getTexture("51"),NULL,&st);
        SDL_RenderCopy(m_pRenderer,TheTexture::Instance()->getTexture("52"),NULL,&qu);
        SDL_RenderPresent(m_pRenderer);
        SDL_RenderClear(m_pRenderer);
    }
    if(status==2){ //map1
        SDL_RenderClear(m_pRenderer);
        SDL_RenderCopy(m_pRenderer,TheTexture::Instance()->getTexture("05"),NULL, NULL);
        wall1->render();
        wall2->render();
        wall3->render();
        wall4->render();
        if(statusammo!=2){
            if(ss==false){SDL_RenderCopy(m_pRenderer,TheTexture::Instance()->getTexture("72"),NULL, &sung);}
            else{SDL_RenderCopy(m_pRenderer,TheTexture::Instance()->getTexture("71"),NULL, &sung);}
        }
        SDL_RenderCopy(m_pRenderer,TheTexture::Instance()->getTexture("03"),NULL, &tam);
        SDL_Texture* thp= str_to_texture("HP: "+std::to_string(hp));
        SDL_Texture* tsc= str_to_texture("Score: "+std::to_string(score));
        SDL_Texture* tam= str_to_texture("Ammo: "+std::to_string(ammo)+"/"+std::to_string(totalammo));
        SDL_Rect hpp{5,5,tWidth,tHeight};
        SDL_Rect scc{5,30,tWidth,tHeight};
        SDL_Rect amm{5,55,tWidth,tHeight};
        SDL_RenderCopy(m_pRenderer,thp,NULL,&hpp);
        SDL_RenderCopy(m_pRenderer,tsc,NULL,&scc);
        SDL_RenderCopy(m_pRenderer,tam,NULL,&amm);
        SDL_RenderPresent(m_pRenderer);
    }
    if(status==3){ //map 2
        SDL_RenderClear(m_pRenderer);
        SDL_RenderCopy(m_pRenderer,TheTexture::Instance()->getTexture("06"),NULL, NULL);
        wall10->render();
        wall11->render();
        wall12->render();
        wall13->render();
        if(statusammo!=2){
            if(ss==false){SDL_RenderCopy(m_pRenderer,TheTexture::Instance()->getTexture("72"),NULL, &sung);}
            else{SDL_RenderCopy(m_pRenderer,TheTexture::Instance()->getTexture("71"),NULL, &sung);}
        }
        SDL_RenderCopy(m_pRenderer,TheTexture::Instance()->getTexture("03"),NULL, &tam);
        SDL_Texture* thp= str_to_texture("HP: "+std::to_string(hp));
        SDL_Texture* tsc= str_to_texture("Score: "+std::to_string(score));
        SDL_Texture* tam= str_to_texture("Ammo: "+std::to_string(ammo)+"/"+std::to_string(totalammo));
        SDL_Rect hpp{5,5,tWidth,tHeight};
        SDL_Rect scc{5,30,tWidth,tHeight};
        SDL_Rect amm{5,55,tWidth,tHeight};
        SDL_RenderCopy(m_pRenderer,thp,NULL,&hpp);
        SDL_RenderCopy(m_pRenderer,tsc,NULL,&scc);
        SDL_RenderCopy(m_pRenderer,tam,NULL,&amm);
        SDL_RenderPresent(m_pRenderer);
    }
    if(status==4){ //map 3
        SDL_RenderClear(m_pRenderer);
        SDL_RenderCopy(m_pRenderer,TheTexture::Instance()->getTexture("07"),NULL, NULL);
        wall5->render();
        wall6->render();
        wall7->render();
        wall8->render();
        wall9->render();
        if(statusammo!=2){
            if(ss==false){SDL_RenderCopy(m_pRenderer,TheTexture::Instance()->getTexture("72"),NULL, &sung);}
            else{SDL_RenderCopy(m_pRenderer,TheTexture::Instance()->getTexture("71"),NULL, &sung);}
        }
        SDL_RenderCopy(m_pRenderer,TheTexture::Instance()->getTexture("03"),NULL, &tam);
        SDL_Texture* thp= str_to_texture("HP: "+std::to_string(hp));
        SDL_Texture* tsc= str_to_texture("Score: "+std::to_string(score));
        SDL_Texture* tam= str_to_texture("Ammo: "+std::to_string(ammo)+"/"+std::to_string(totalammo));
        SDL_Rect hpp{5,5,tWidth,tHeight};
        SDL_Rect scc{5,30,tWidth,tHeight};
        SDL_Rect amm{5,55,tWidth,tHeight};
        SDL_RenderCopy(m_pRenderer,thp,NULL,&hpp);
        SDL_RenderCopy(m_pRenderer,tsc,NULL,&scc);
        SDL_RenderCopy(m_pRenderer,tam,NULL,&amm);
        SDL_RenderPresent(m_pRenderer);
    }
    if(status==5){ //complete 1 map
        SDL_RenderClear(m_pRenderer);
        SDL_RenderCopy(m_pRenderer,TheTexture::Instance()->getTexture("97"),NULL, NULL);
        SDL_RenderCopy(m_pRenderer,TheTexture::Instance()->getTexture("54"),NULL, &ne);
        SDL_RenderCopy(m_pRenderer,TheTexture::Instance()->getTexture("55"),NULL, &mn);
        SDL_RenderPresent(m_pRenderer);
    }
    if(status==6){ //failed
        SDL_RenderClear(m_pRenderer);
        SDL_RenderCopy(m_pRenderer,TheTexture::Instance()->getTexture("98"),NULL, NULL);
        SDL_RenderCopy(m_pRenderer,TheTexture::Instance()->getTexture("53"),NULL,&re);
        SDL_RenderCopy(m_pRenderer,TheTexture::Instance()->getTexture("52"),NULL,&qu2);
        SDL_RenderPresent(m_pRenderer);
    }
    if(status==7){ //complete all
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
        if(event.type == SDL_MOUSEBUTTONDOWN){
            if(status==1){
                    if(x1>900&&x1<1100&&y1>390&&y1<465){
                        status=2;
                        Mix_PlayMusic( mplay, -1 );
                    }
                    if(x1>900&&x1<1100&&y1>490&&y1<565){m_bRunning=false;}
            }
            if(status==5){
                    if(x1>950&&x1<1150&&y1>390&&y1<465){
                        status=mapcom+1;
                        Mix_PlayMusic( mplay, -1 );
                    }
            }
            if(status==6){
                    if(x1>540&&x1<740&&y1>395&&y1<470){
                        status=1;
                        hp=100; score=0; ammo=20;
                        Mix_PlayMusic(mmusic,-1);
                    }
                    if(x1>540&&x1<740&&y1>495&&y1<570){m_bRunning=false;}
            }
            if(status==2&&statusammo==1&&SDL_GetTicks()-timebanlt>200){
                    ss=false;
                    trudan();
                    wall1->shooted(x1,y1);
                    wall2->shooted(x1,y1);
                    wall3->shooted(x1,y1);
                    wall4->shooted(x1,y1);
                    Mix_PlayChannel( -1, mshot,0 );
                    timebanlt=SDL_GetTicks();
            }
            if(status==3&&statusammo==1&&SDL_GetTicks()-timebanlt>200){
                    ss=false;
                    trudan();
                    wall10->shooted(x1,y1);
                    wall11->shooted(x1,y1);
                    wall12->shooted(x1,y1);
                    wall13->shooted(x1,y1);
                    Mix_PlayChannel( -1, mshot,0 );
                    timebanlt=SDL_GetTicks();
            }
            if(status==4&&statusammo==1&&SDL_GetTicks()-timebanlt>200){
                    ss=false;
                    trudan();
                    wall5->shooted(x1,y1);
                    wall6->shooted(x1,y1);
                    wall7->shooted(x1,y1);
                    wall8->shooted(x1,y1);
                    wall9->shooted(x1,y1);
                    Mix_PlayChannel( -1, mshot,0 );
                    timebanlt=SDL_GetTicks();
            }
        }
        if(event.type == SDL_MOUSEBUTTONUP){
            ss=true;
        }
        if(event.type == SDL_QUIT)
        {
            m_bRunning=false;
        }
        if(event.type == SDL_KEYDOWN )
                {
                    switch( event.key.keysym.sym )
                    {
                        case SDLK_t:
                                if( Mix_PausedMusic() == 1 )
                                {
                                    Mix_ResumeMusic();
                                }
                                else
                                {
                                    Mix_PauseMusic();
                                }
                            break;

                        case SDLK_y:
                        Mix_HaltMusic();
                        break;

                        case SDLK_r:
                            if(totalammo!=0){
                                statusammo=2;
                                timee=SDL_GetTicks();
                                Mix_PlayChannel( -1, mreload,0 );
                            }
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
    Mix_FreeMusic(mplay);
    mplay = NULL;
    Mix_FreeMusic(mwin);
    mwin =NULL;
    Mix_FreeMusic(mfail);
    mfail = NULL;
    SDL_DestroyWindow(m_pWindow);
    SDL_DestroyRenderer(m_pRenderer);
    IMG_Quit();
    Mix_Quit();
    SDL_Quit();
}
