#ifndef ITEM_H
#define ITEM_H
#include <string>
#include<iostream>
#include "Texture.h"

class Item
{
    public:
        Item(std::string _m_textureID){
            x=30+rand()%1220;
            y=360+rand()%250;
            m_textureID=_m_textureID;
            remain=0;
            max=2;
        }
        virtual ~Item(){
        };
        void update();
        void render();
        void shooted(int m, int n);
        void setmax(int c){max=c;}
    private:
        int remain;
        double x,y,j=0;
        int max;
        std::string m_textureID;
        SDL_Rect ite;
        double time;
};

#endif // ITEM_H
