#include "Object.h"
#include "Game.h"
#include "Texture.h"
#include "SDL.h"
#include "cstdlib"
void Object::update()
{
    if(SDL_GetTicks()-time>2000&&remain==0&&rand()%500==1){
        quai.x=x;
        quai.y=y;
        quai.w=w;
        quai.h=h;
        remain=1;
        time=SDL_GetTicks();
    }
    if(remain==2&&SDL_GetTicks()-timeb>500){
        remain=0;
    }
    if(remain==1&&SDL_GetTicks()-time>2000){
        remain=3;
        TheGame::Instance()->truhp(dame);
        time=SDL_GetTicks();
    }
    if(remain==3&&SDL_GetTicks()-time>150){
        remain=1;
        time=SDL_GetTicks();
    }
}

void Object::shooted(int m, int n)
{
    if(remain==1){
        if(m>x&&m<x+w&&n>y&&n<y+h){
            insideq=true;
        }
        else insideq=false;
        if(m>enm.x&&m<enm.x+enm.w&&n>enm.y&&n<enm.y+enm.h){
            insidet=true;
        }
        else insidet=false;
        if(insideq==true&&insidet==false){
            timeb=SDL_GetTicks();
            remain=2;
            TheGame::Instance()->tangdiem(5);
        }
    }

}

void Object::render()
{
    if(remain==1){
        SDL_RenderCopy(TheGame::Instance()->getRenderer(),TheTexture::Instance()->getTexture(quaiID),NULL,&quai);
    }
    if(remain==2){
        SDL_RenderCopy(TheGame::Instance()->getRenderer(),TheTexture::Instance()->getTexture(qcID),NULL,&quai);
    }
    if(remain==3){
        SDL_RenderCopy(TheGame::Instance()->getRenderer(),TheTexture::Instance()->getTexture(qbID),NULL,&quai);
    }

    SDL_RenderCopy(TheGame::Instance()->getRenderer(),TheTexture::Instance()->getTexture(m_textureID),NULL,&enm);

}

