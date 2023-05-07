#ifndef GAME_H
#define GAME_H
#include "SDL.h"
#include <vector>
#include "Texture.h"
#include "Object.h"
#include <SDL_ttf.h>
#include <string.h>
#include <SDL_mixer.h>
class Game
{
    public:
        static Game*Instance()
        {
            if(m_pGame == 0)
            {
                m_pGame = new Game();
            }
            return m_pGame;
        }
        bool init(const char* title, int xpos, int ypos, int width, int height, int flags);
        SDL_Renderer* getRenderer(){return m_pRenderer;}
        void render();
        void update();
        void handleEvents();
        SDL_Texture* str_to_texture(std::string str);//be careful
        void clean();
        bool running(){ return m_bRunning;}
        void truhp(int x){
            hp-=x;
            if(hp==0){status=6; Mix_PlayMusic( mfail, -1 );}
        }
        void tangdiem(int sc){
            score+=sc;
            if(status==2&&score>=100){
                status=5; Mix_PlayMusic( mwin, 3 );
                totalammo=20; ammo=20; hp=100; score=0; ++mapcom;

            }
            if(status==3&&score>=100){
                status=5; Mix_PlayMusic( mwin, 3 );
                totalammo=40; ammo=20; hp=100; score=0; ++mapcom;

            }
            if(status==4&&score>=100){
                status=7; Mix_PlayMusic( mwin, 3 );

            }
        }
        void trudan(){
            ammo-=1;
            if(ammo==0){statusammo=0;}
        }
        int getqtocban(){return qtocban;}
        int gettansuat(){return tansuat;}
        int getstatus(){return status;}
        int getqhp(){return qhp;}
        int getqdame(){return qdame;}
    protected:

    private:
        std::vector<std::vector<int>> maps;
        int x1, y1;
        static Game* m_pGame;
        Game(){};
        ~Game(){};
        Object* wall1;
        Object* wall2;
        Object* wall3;
        Object* wall4;
        Object* wall5;
        Object* wall6;
        Object* wall7;
        Object* wall8;
        Object* wall9;
        Object* wall10;
        Object* wall11;
        Object* wall12;
        Object* wall13;
        SDL_Window* m_pWindow;
        SDL_Renderer* m_pRenderer;
        TTF_Font* gFont;
        bool m_bRunning,ss=true;
        int status=1, qtocban, tansuat, qhp, qdame, totalammo=40, mapcom=2;
        int tWidth, tHeight;
        int hp=100, score=0, ammo=20, statusammo=1;
        SDL_Rect hpp,scc,amm, st{900,390,200,75}, qu{900,490,200,75}, re{540,395,200,75}, qu2{540,495,200,75}, ne{950,390,200,75}, mn{950,490,200,75}, ba{0,0,320,150};
        SDL_Rect sung,tam;
        double timee, timebanlt=0, initban=0;
        std::string lvl;
        Mix_Chunk *mshot = NULL;
        Mix_Chunk *mreload = NULL;
        Mix_Music *mmusic = NULL;
        Mix_Music *mfail = NULL;
        Mix_Music *mplay = NULL;
        Mix_Music *mwin = NULL;
};
typedef Game TheGame;
#endif // GAME_H
