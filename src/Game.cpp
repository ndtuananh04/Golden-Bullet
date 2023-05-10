#include "Game.h"
#include <iostream>
#include <cstdlib>
#include <Object.h>
#include<string.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
Game* Game::m_pGame = 0;

 SDL_Texture* Game::str_to_texture(std::string str){
 SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, str.c_str(), {255,215,0} );
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
        mreload = Mix_LoadWAV("assets/reload.mp3");
    Loadmap(1);

    itemammo = new Item("40");
    itemhp = new Item("41");
    itemsp = new Item("42");

    std::cout << "init success\n";
    return true;
}

void Game::Loadmap(int x)
{
    TheTexture::Instance()->clearer();
    if(x==1){ //start
        TheTexture::Instance()->load("Assets/bg.png","01",m_pRenderer);
        TheTexture::Instance()->load("Assets/start.png","51",m_pRenderer);
        TheTexture::Instance()->load("Assets/instrucbtn.png","56",m_pRenderer);
        TheTexture::Instance()->load("Assets/quit.png","52",m_pRenderer);
    }
    if(x==8){ //choose level
        TheTexture::Instance()->load("Assets/levelchoose.png","02",m_pRenderer);

    }
    if(x==2){ //map 1
        TheTexture::Instance()->load("Assets/map1.png","05",m_pRenderer);
        TheTexture::Instance()->load("Assets/11.png","11",m_pRenderer);
        TheTexture::Instance()->load("Assets/12.png","12",m_pRenderer);
        TheTexture::Instance()->load("Assets/13.png","13",m_pRenderer);
        TheTexture::Instance()->load("Assets/14.png","14",m_pRenderer);
        wall1 = new Object(200,200,-26,320,"11",175,340,65,130,"31","32","33");
        wall2 = new Object(380,278,472,174,"12",414,215,53,106,"31","32","33");
        wall3 = new Object(291,193,979,326,"13",909,346,65,130,"31","32","33");
        wall4 = new Object(203,204,1040,520,"14",1050,370,122,244,"31","32","33");
        TheTexture::Instance()->load("Assets/bang.png","80",m_pRenderer);
        TheTexture::Instance()->load("Assets/pausebtn.png","82",m_pRenderer);
        TheTexture::Instance()->load("Assets/phantom.png","71",m_pRenderer);
        TheTexture::Instance()->load("Assets/phantom2.png","72",m_pRenderer);
        TheTexture::Instance()->load("Assets/crosshair.png","03",m_pRenderer);
        TheTexture::Instance()->load("Assets/enemy1.png","31",m_pRenderer);
        TheTexture::Instance()->load("Assets/enemy2.png","32",m_pRenderer);
        TheTexture::Instance()->load("Assets/enemy3.png","33",m_pRenderer);
        TheTexture::Instance()->load("Assets/ammoitem.png","40",m_pRenderer);
        TheTexture::Instance()->load("Assets/hpitem.png","41",m_pRenderer);
        TheTexture::Instance()->load("Assets/spitem.png","42",m_pRenderer);
    }
    if(x==3){ //map 2
        TheTexture::Instance()->load("Assets/map2.png","06",m_pRenderer);
        TheTexture::Instance()->load("Assets/15.png","15",m_pRenderer);
        TheTexture::Instance()->load("Assets/16.png","16",m_pRenderer);
        TheTexture::Instance()->load("Assets/17.png","17",m_pRenderer);
        TheTexture::Instance()->load("Assets/18.png","18",m_pRenderer);
        wall10 = new Object(47,19,348,156,"20",362,113,27,54,"31","32","33");
        wall11 = new Object(86,60,313,565,"21",324,480,68,136,"31","32","33");
        wall12 = new Object(30,41,682,549,"22",692,490,48,96,"31","32","33");
        wall13 = new Object(124,150,1156,570,"23",1129,447,126,252,"31","32","33");
        TheTexture::Instance()->load("Assets/bang.png","80",m_pRenderer);
        TheTexture::Instance()->load("Assets/pausebtn.png","82",m_pRenderer);
        TheTexture::Instance()->load("Assets/phantom.png","71",m_pRenderer);
        TheTexture::Instance()->load("Assets/phantom2.png","72",m_pRenderer);
        TheTexture::Instance()->load("Assets/crosshair.png","03",m_pRenderer);
        TheTexture::Instance()->load("Assets/enemy1.png","31",m_pRenderer);
        TheTexture::Instance()->load("Assets/enemy2.png","32",m_pRenderer);
        TheTexture::Instance()->load("Assets/enemy3.png","33",m_pRenderer);
        TheTexture::Instance()->load("Assets/ammoitem.png","40",m_pRenderer);
        TheTexture::Instance()->load("Assets/hpitem.png","41",m_pRenderer);
        TheTexture::Instance()->load("Assets/spitem.png","42",m_pRenderer);
    }
    if(x==4){ //map 3
        TheTexture::Instance()->load("Assets/map3.png","07",m_pRenderer);
        TheTexture::Instance()->load("Assets/20.png","20",m_pRenderer);
        TheTexture::Instance()->load("Assets/21.png","21",m_pRenderer);
        TheTexture::Instance()->load("Assets/22.png","22",m_pRenderer);
        TheTexture::Instance()->load("Assets/23.png","23",m_pRenderer);
        TheTexture::Instance()->load("Assets/19.png","19",m_pRenderer);
        wall5 = new Object(100,190,140,433,"15",90,395,95,190,"31","32","33");
        wall6 = new Object(32,17,467,284,"16",470,245,28,56,"31","32","33");
        wall7 = new Object(103,142,662,206,"17",635,244,42,84,"31","32","33");
        wall8 = new Object(24,122,869,326,"18",888,330,45,90,"31","32","33");
        wall9 = new Object(20,80,1167,235,"19",1140,237,38,76,"31","32","33");
        TheTexture::Instance()->load("Assets/bang.png","80",m_pRenderer);
        TheTexture::Instance()->load("Assets/pausebtn.png","82",m_pRenderer);
        TheTexture::Instance()->load("Assets/phantom.png","71",m_pRenderer);
        TheTexture::Instance()->load("Assets/phantom2.png","72",m_pRenderer);
        TheTexture::Instance()->load("Assets/crosshair.png","03",m_pRenderer);
        TheTexture::Instance()->load("Assets/enemy1.png","31",m_pRenderer);
        TheTexture::Instance()->load("Assets/enemy2.png","32",m_pRenderer);
        TheTexture::Instance()->load("Assets/enemy3.png","33",m_pRenderer);
        TheTexture::Instance()->load("Assets/ammoitem.png","40",m_pRenderer);
        TheTexture::Instance()->load("Assets/hpitem.png","41",m_pRenderer);
        TheTexture::Instance()->load("Assets/spitem.png","42",m_pRenderer);
    }
    if(x==5){ //complete 1 stage
        TheTexture::Instance()->load("Assets/stagecom.png","97",m_pRenderer);
        TheTexture::Instance()->load("Assets/nextstagebtn.png","54",m_pRenderer);
        TheTexture::Instance()->load("Assets/menubtn.png","55",m_pRenderer);
    }
    if(x==6){ //failed
        TheTexture::Instance()->load("Assets/failed.png","98",m_pRenderer);
        TheTexture::Instance()->load("Assets/replay.png","53",m_pRenderer);
        TheTexture::Instance()->load("Assets/quit.png","52",m_pRenderer);
    }
    if(x==7){ //complete all
        TheTexture::Instance()->load("Assets/complete.png","99",m_pRenderer);
        TheTexture::Instance()->load("Assets/menubtn.png","55",m_pRenderer);
    }
    if(x==9){ //pause
        TheTexture::Instance()->load("Assets/pause.png","81",m_pRenderer);
    }
    if(x==10){ //instruction
        TheTexture::Instance()->load("Assets/instruction.png","84",m_pRenderer);
    }
}

void Game::update()
{
    SDL_GetMouseState( &x1, &y1 );
    if(status==2){ //map 1
        wall1->update();
        wall2->update();
        wall3->update();
        wall4->update();
        sung.x=640+x1/3;
        sung.y=360+y1/3;
        sung.w=640;
        sung.h=360;
        tam.x=x1-15;
        tam.y=y1-15;
        tam.w=30;
        tam.h=30;
        if(SDL_GetTicks()-inittime>=10000){
            itemammo->update();
            itemhp->update();
            itemsp->update();
        }
    }
    if(status==3){ //map 2
        wall10->update();
        wall11->update();
        wall12->update();
        wall13->update();
        sung.x=640+x1/3;
        sung.y=360+y1/3;
        sung.w=640;
        sung.h=360;
        tam.x=x1-15;
        tam.y=y1-15;
        tam.w=30;
        tam.h=30;
        if(SDL_GetTicks()-inittime>=10000){
            itemammo->update();
            itemhp->update();
            itemsp->update();
        }
    }
    if(status==4){ //map 3
        wall5->update();
        wall6->update();
        wall7->update();
        wall8->update();
        wall9->update();
        sung.x=640+x1/3;
        sung.y=360+y1/3;
        sung.w=640;
        sung.h=360;
        tam.x=x1-15;
        tam.y=y1-15;
        tam.w=30;
        tam.h=30;
        if(SDL_GetTicks()-inittime>=10000){ //test
            itemammo->update();
            itemhp->update();
            itemsp->update();
        }
    }
    if(ss==false&&SDL_GetTicks()-initban>150){
        ss=true;
    }
    if(statusammo==2&&SDL_GetTicks()-timee>1000){
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
        SDL_RenderCopy(m_pRenderer,TheTexture::Instance()->getTexture("56"),NULL,&in);
        SDL_RenderCopy(m_pRenderer,TheTexture::Instance()->getTexture("52"),NULL,&qu);
        SDL_RenderPresent(m_pRenderer);
        SDL_RenderClear(m_pRenderer);
    }
    if(status==2){ //map1
        SDL_RenderClear(m_pRenderer);
        SDL_RenderCopy(m_pRenderer,TheTexture::Instance()->getTexture("05"),NULL, NULL);
        SDL_RenderCopy(m_pRenderer,TheTexture::Instance()->getTexture("80"),NULL, &ba);
        SDL_RenderCopy(m_pRenderer,TheTexture::Instance()->getTexture("82"),NULL, &pbt);
        wall1->render();
        wall2->render();
        wall3->render();
        wall4->render();
        itemammo->render();
        itemhp->render();
        itemsp->render();
        if(statusammo!=2){
            if(ss==false){SDL_RenderCopy(m_pRenderer,TheTexture::Instance()->getTexture("72"),NULL, &sung);}
            else{SDL_RenderCopy(m_pRenderer,TheTexture::Instance()->getTexture("71"),NULL, &sung);}
        }
        SDL_RenderCopy(m_pRenderer,TheTexture::Instance()->getTexture("03"),NULL, &tam);
        SDL_Texture* thp= str_to_texture("HP: "+std::to_string(hp));
        SDL_Texture* tsc= str_to_texture("Score: "+std::to_string(score));
        SDL_Texture* tam= str_to_texture("Ammo: "+std::to_string(ammo)+"/"+std::to_string(totalammo));
        SDL_Texture* levelpr= str_to_texture("Level: "+ lvl);
        SDL_Texture* mapp= str_to_texture("Map 1");
        SDL_Texture* sp= str_to_texture(": "+std::to_string(spitem));

        SDL_RenderCopy(m_pRenderer,TheTexture::Instance()->getTexture("42"),NULL, &sph);
        SDL_RenderCopy(m_pRenderer,thp,NULL,&hpp);
        SDL_RenderCopy(m_pRenderer,tsc,NULL,&scc);
        SDL_RenderCopy(m_pRenderer,tam,NULL,&amm);
        SDL_RenderCopy(m_pRenderer,levelpr,NULL,&lv);
        SDL_RenderCopy(m_pRenderer,mapp,NULL,&mp);
        SDL_RenderCopy(m_pRenderer,sp,NULL,&spt);
        SDL_DestroyTexture(thp);
        SDL_DestroyTexture(tsc);
        SDL_DestroyTexture(tam);
        SDL_DestroyTexture(levelpr);
        SDL_DestroyTexture(mapp);
        SDL_DestroyTexture(sp);
        SDL_RenderPresent(m_pRenderer);
    }
    if(status==3){ //map 2
        SDL_RenderClear(m_pRenderer);
        SDL_RenderCopy(m_pRenderer,TheTexture::Instance()->getTexture("06"),NULL, NULL);
        SDL_RenderCopy(m_pRenderer,TheTexture::Instance()->getTexture("80"),NULL, &ba);
        SDL_RenderCopy(m_pRenderer,TheTexture::Instance()->getTexture("82"),NULL, &pbt);
        wall10->render();
        wall11->render();
        wall12->render();
        wall13->render();
        itemammo->render();
        itemhp->render();
        itemsp->render();
        if(statusammo!=2){
            if(ss==false){SDL_RenderCopy(m_pRenderer,TheTexture::Instance()->getTexture("72"),NULL, &sung);}
            else{SDL_RenderCopy(m_pRenderer,TheTexture::Instance()->getTexture("71"),NULL, &sung);}
        }
        SDL_RenderCopy(m_pRenderer,TheTexture::Instance()->getTexture("03"),NULL, &tam);
        SDL_Texture* thp= str_to_texture("HP: "+std::to_string(hp));
        SDL_Texture* tsc= str_to_texture("Score: "+std::to_string(score));
        SDL_Texture* tam= str_to_texture("Ammo: "+std::to_string(ammo)+"/"+std::to_string(totalammo));
        SDL_Texture* levelpr= str_to_texture("Level: "+ lvl);
        SDL_Texture* mapp= str_to_texture("Map 2");
        SDL_Texture* sp= str_to_texture(": "+std::to_string(spitem));

        SDL_RenderCopy(m_pRenderer,TheTexture::Instance()->getTexture("42"),NULL, &sph);
        SDL_RenderCopy(m_pRenderer,thp,NULL,&hpp);
        SDL_RenderCopy(m_pRenderer,tsc,NULL,&scc);
        SDL_RenderCopy(m_pRenderer,tam,NULL,&amm);
        SDL_RenderCopy(m_pRenderer,levelpr,NULL,&lv);
        SDL_RenderCopy(m_pRenderer,mapp,NULL,&mp);
        SDL_RenderCopy(m_pRenderer,sp,NULL,&spt);
        SDL_DestroyTexture(thp);
        SDL_DestroyTexture(tsc);
        SDL_DestroyTexture(tam);
        SDL_DestroyTexture(levelpr);
        SDL_DestroyTexture(mapp);
        SDL_DestroyTexture(sp);
        SDL_RenderPresent(m_pRenderer);
    }
    if(status==4){ //map 3
        SDL_RenderClear(m_pRenderer);
        SDL_RenderCopy(m_pRenderer,TheTexture::Instance()->getTexture("07"),NULL, NULL);
        SDL_RenderCopy(m_pRenderer,TheTexture::Instance()->getTexture("80"),NULL, &ba);
        SDL_RenderCopy(m_pRenderer,TheTexture::Instance()->getTexture("82"),NULL, &pbt);
        wall5->render();
        wall6->render();
        wall7->render();
        wall8->render();
        wall9->render();
        itemammo->render();
        itemhp->render();
        itemsp->render();
        if(statusammo!=2){
            if(ss==false){SDL_RenderCopy(m_pRenderer,TheTexture::Instance()->getTexture("72"),NULL, &sung);}
            else{SDL_RenderCopy(m_pRenderer,TheTexture::Instance()->getTexture("71"),NULL, &sung);}
        }
        SDL_RenderCopy(m_pRenderer,TheTexture::Instance()->getTexture("03"),NULL, &tam);
        SDL_Texture* thp= str_to_texture("HP: "+std::to_string(hp));
        SDL_Texture* tsc= str_to_texture("Score: "+std::to_string(score));
        SDL_Texture* tam= str_to_texture("Ammo: "+std::to_string(ammo)+"/"+std::to_string(totalammo));
        SDL_Texture* levelpr= str_to_texture("Level: "+ lvl);
        SDL_Texture* mapp= str_to_texture("Map 1");
        SDL_Texture* sp= str_to_texture(": "+std::to_string(spitem));

        SDL_RenderCopy(m_pRenderer,TheTexture::Instance()->getTexture("42"),NULL, &sph);
        SDL_RenderCopy(m_pRenderer,thp,NULL,&hpp);
        SDL_RenderCopy(m_pRenderer,tsc,NULL,&scc);
        SDL_RenderCopy(m_pRenderer,tam,NULL,&amm);
        SDL_RenderCopy(m_pRenderer,levelpr,NULL,&lv);
        SDL_RenderCopy(m_pRenderer,mapp,NULL,&mp);
        SDL_RenderCopy(m_pRenderer,sp,NULL,&spt);
        SDL_DestroyTexture(thp);
        SDL_DestroyTexture(tsc);
        SDL_DestroyTexture(tam);
        SDL_DestroyTexture(levelpr);
        SDL_DestroyTexture(mapp);
        SDL_DestroyTexture(sp);
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
        SDL_RenderCopy(m_pRenderer,TheTexture::Instance()->getTexture("55"),NULL, &mn);
        SDL_RenderPresent(m_pRenderer);
    }
    if(status==8){ //choose level
        SDL_RenderClear(m_pRenderer);
        SDL_RenderCopy(m_pRenderer,TheTexture::Instance()->getTexture("02"),NULL, NULL);
        SDL_RenderPresent(m_pRenderer);
    }
    if(status==9){ //pause
        Loadmap(9);
        SDL_RenderClear(m_pRenderer);
        SDL_RenderCopy(m_pRenderer,TheTexture::Instance()->getTexture("81"),NULL, NULL);
        SDL_RenderPresent(m_pRenderer);
    }
    if(status==10){ //instruction
        SDL_RenderClear(m_pRenderer);
        SDL_RenderCopy(m_pRenderer,TheTexture::Instance()->getTexture("84"),NULL, NULL);
        SDL_RenderPresent(m_pRenderer);
    }
}

void Game::handleEvents()
{
    SDL_Event event;
    while(SDL_PollEvent(&event)!=0)
        {
        if(event.type == SDL_MOUSEBUTTONDOWN){
            if(status==1){ //start
                    if(x1>900&&x1<1100&&y1>390&&y1<465){ //choose level
                        status=8;
                        Loadmap(8);
                        Mix_PlayMusic( mplay, -1 );
                    }
                    if(x1>900&&x1<1100&&y1>480&&y1<555){ //instruction
                        status=10; Loadmap(10);
                    }
                    if(x1>900&&x1<1100&&y1>570&&y1<645){m_bRunning=false;} //quit
            }
            if(status==8){ //choose level
                if(x1>482&&x1<818&&y1>275&&y1<335){ //lv easy
                    lvl="Easy";
                    Loadmap(2);
                    qtocban=2500;
                    tansuat=400; qhp=100; qdame=5;
                    status=mapcom;
                    timebanlt=SDL_GetTicks();
                    inittime=SDL_GetTicks();
                }
                if(x1>482&&x1<818&&y1>360&&y1<420){ //lv medium
                    lvl="Medium";
                    Loadmap(2);
                    qtocban=1800;
                    tansuat=350; qhp=120; qdame=7;
                    status=mapcom;
                    timebanlt=SDL_GetTicks();
                    inittime=SDL_GetTicks();
                }
                if(x1>482&&x1<818&&y1>445&&y1<505){ //lv hard
                    lvl="Hard";
                    Loadmap(2);
                    qtocban=1400;
                    tansuat=300; qhp=150; qdame=10;
                    status=mapcom;
                    timebanlt=SDL_GetTicks();
                    inittime=SDL_GetTicks();
                }
            }
            if(status==5){ //complete 1 stage
                    if(x1>950&&x1<1150&&y1>390&&y1<465){ //next stage
                        status=mapcom;
                        Loadmap(mapcom);
                        if(lvl=="Easy"){qtocban-=300;}
                        if(lvl=="Medium"){qtocban-=250;}
                        if(lvl=="Hard"){qtocban-=200;}
                        Mix_PlayMusic( mplay, -1 );
                        timebanlt=SDL_GetTicks();
                        inittime=SDL_GetTicks();
                        itemammo->setmax(2);
                        itemhp->setmax(2);
                        itemsp->setmax(2);
                    }
                    if(x1>950&&x1<1150&&y1>490&&y1<565){ //ve menu
                        status=1; spitem=0;
                        Mix_PlayMusic( mmusic, -1 );
                        statusammo=1;
                    }
            }
            if(status==6){ //failed
                    if(x1>540&&x1<740&&y1>395&&y1<470){ //ve menu
                        status=1;
                        hp=100; score=0; ammo=20; totalammo=40; spitem=0;
                        Mix_PlayMusic(mmusic,-1); statusammo=1;
                        if(mapcom==2){wall1->setqstatus(0);
                        wall2->setqstatus(0);
                        wall3->setqstatus(0);
                        wall4->setqstatus(0);}
                        if(mapcom==4){wall5->setqstatus(0);
                        wall6->setqstatus(0);
                        wall7->setqstatus(0);
                        wall8->setqstatus(0);
                        wall9->setqstatus(0);}
                        if(mapcom==3){wall10->setqstatus(0);
                        wall11->setqstatus(0);
                        wall12->setqstatus(0);
                        wall13->setqstatus(0);}
                        mapcom=2;
                    }
                    if(x1>540&&x1<740&&y1>495&&y1<570){m_bRunning=false;} //quit
            }
            if(status==2){ //map 1
                if(x1>1215&&x1<1260&&y1>15&&y1<60){status=9; Loadmap(9);}
                else if(statusammo==1&&SDL_GetTicks()-timebanlt>200){
                    ss=false;
                    trudan();
                    wall1->shooted(x1,y1);
                    wall2->shooted(x1,y1);
                    wall3->shooted(x1,y1);
                    wall4->shooted(x1,y1);
                    itemammo->shooted(x1,y1);
                    itemhp->shooted(x1,y1);
                    itemsp->shooted(x1,y1);
                    Mix_PlayChannel( -1, mshot,0 );
                    initban=SDL_GetTicks();
                    timebanlt=SDL_GetTicks();
                }
            }
            if(status==3){ //map 2
                if(x1>1215&&x1<1260&&y1>15&&y1<60){status=9; Loadmap(9);}
                else if(statusammo==1&&SDL_GetTicks()-timebanlt>200){
                    ss=false;
                    trudan();
                    wall10->shooted(x1,y1);
                    wall11->shooted(x1,y1);
                    wall12->shooted(x1,y1);
                    wall13->shooted(x1,y1);
                    itemammo->shooted(x1,y1);
                    itemhp->shooted(x1,y1);
                    itemsp->shooted(x1,y1);
                    Mix_PlayChannel( -1, mshot,0 );
                    initban=SDL_GetTicks();
                    timebanlt=SDL_GetTicks();
                }
            }
            if(status==4){ //map 3
                if(x1>1215&&x1<1260&&y1>15&&y1<60){status=9; Loadmap(9);}
                else if(statusammo==1&&SDL_GetTicks()-timebanlt>200){
                    ss=false;
                    trudan();
                    wall5->shooted(x1,y1);
                    wall6->shooted(x1,y1);
                    wall7->shooted(x1,y1);
                    wall8->shooted(x1,y1);
                    wall9->shooted(x1,y1);
                    itemammo->shooted(x1,y1);
                    itemhp->shooted(x1,y1);
                    itemsp->shooted(x1,y1);
                    Mix_PlayChannel( -1, mshot,0 );
                    initban=SDL_GetTicks();
                    timebanlt=SDL_GetTicks();
                }
            }
            if(status==7&&x1>950&&x1<1150&&y1>490&&y1<565){ //complete all
                status=1; Loadmap(1);
                hp=100; score=0; ammo=20; totalammo=20; spitem=0; statusammo=1;
                        Mix_PlayMusic(mmusic,-1);
                        if(mapcom==2){wall1->setqstatus(0);
                        wall2->setqstatus(0);
                        wall3->setqstatus(0);
                        wall4->setqstatus(0);}
                        if(mapcom==4){wall5->setqstatus(0);
                        wall6->setqstatus(0);
                        wall7->setqstatus(0);
                        wall8->setqstatus(0);
                        wall9->setqstatus(0);}
                        if(mapcom==3){wall10->setqstatus(0);
                        wall11->setqstatus(0);
                        wall12->setqstatus(0);
                        wall13->setqstatus(0);}
                        mapcom=2;
            }
            if(status==9){ //pause
                if(x1>495&&x1<777&&y1>285&&y1<356){ //resume
                    status=mapcom;
                }
                if(x1>495&&x1<777&&y1>381&&y1<452){ //ve menu
                    status=1;
                    Loadmap(1);
                    Mix_PlayMusic( mmusic, -1 );
                    hp=100; score=0; ammo=20; totalammo=20; statusammo=1; spitem=0;
                        Mix_PlayMusic(mmusic,-1);
                        if(mapcom==2){wall1->setqstatus(0);
                        wall2->setqstatus(0);
                        wall3->setqstatus(0);
                        wall4->setqstatus(0);}
                        if(mapcom==4){wall5->setqstatus(0);
                        wall6->setqstatus(0);
                        wall7->setqstatus(0);
                        wall8->setqstatus(0);
                        wall9->setqstatus(0);}
                        if(mapcom==3){wall10->setqstatus(0);
                        wall11->setqstatus(0);
                        wall12->setqstatus(0);
                        wall13->setqstatus(0);}
                        mapcom=2;
                }
            }
            if(status==10&&x1>1105&&x1<1155&&y1>74&&y1<124){ //instruction
                status=1; Loadmap(1);
            }
        }
        if(event.type == SDL_MOUSEBUTTONUP){
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

                        case SDLK_f:
                            if(spitem>0){
                                if(status==2){
                                    if(wall1->getqstatus()==1||wall1->getqstatus()==3){wall1->resettimeb();wall1->setqstatus(2);}
                                    if(wall2->getqstatus()==1||wall2->getqstatus()==3){wall2->resettimeb();wall2->setqstatus(2);}
                                    if(wall3->getqstatus()==1||wall3->getqstatus()==3){wall3->resettimeb();wall3->setqstatus(2);}
                                    if(wall4->getqstatus()==1||wall4->getqstatus()==3){wall4->resettimeb();wall4->setqstatus(2);}
                                }
                                if(status==3){
                                    if(wall10->getqstatus()==1||wall10->getqstatus()==3){wall10->resettimeb();wall10->setqstatus(2);}
                                    if(wall11->getqstatus()==1||wall11->getqstatus()==3){wall11->resettimeb();wall11->setqstatus(2);}
                                    if(wall12->getqstatus()==1||wall12->getqstatus()==3){wall12->resettimeb();wall12->setqstatus(2);}
                                    if(wall13->getqstatus()==1||wall13->getqstatus()==3){wall13->resettimeb();wall13->setqstatus(2);}
                                }
                                if(status==4){
                                    if(wall5->getqstatus()==1||wall5->getqstatus()==3){wall5->resettimeb();wall5->setqstatus(2);}
                                    if(wall6->getqstatus()==1||wall6->getqstatus()==3){wall6->resettimeb();wall6->setqstatus(2);}
                                    if(wall7->getqstatus()==1||wall7->getqstatus()==3){wall7->resettimeb();wall7->setqstatus(2);}
                                    if(wall8->getqstatus()==1||wall8->getqstatus()==3){wall8->resettimeb();wall8->setqstatus(2);}
                                    if(wall9->getqstatus()==1||wall9->getqstatus()==3){wall9->resettimeb();wall9->setqstatus(2);}
                                }
                                spitem--;
                            }
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
