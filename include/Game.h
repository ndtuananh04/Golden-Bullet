#ifndef GAME_H
#define GAME_H
#include "SDL.h"
#include <vector>
#include "Texture.h"
#include "Object.h"
#include <SDL_ttf.h>
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
        SDL_Texture* str_to_texture(std::string str)//be careful
        {
        SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, str.c_str(), {255,255,0} );
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(m_pRenderer,textSurface);
        SDL_FreeSurface(textSurface);
        return textTexture;}
        void update();
        void handleEvents();
        void clean();
        bool running(){ return m_bRunning;}
        void truhp(int x){hp-=x;}
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
        SDL_Window* m_pWindow;
        SDL_Renderer* m_pRenderer;
        TTF_Font* gFont;
        bool m_bRunning,ss=true;
        int status=1;
        int hp=100;
        std::string ab="static";

};
typedef Game TheGame;
#endif // GAME_H
