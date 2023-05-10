#include "Item.h"
#include "Game.h"
#include "Texture.h"
#include "SDL.h"
#include "cstdlib"

void Item::update()
{
    if(remain==0&&max>0&&rand()%9000==1){ //test
        remain=1;
        ite.x=x;
        ite.w=45;
        ite.h=45;
    }
}

void Item::render()
{
    if(remain==1){
        if(j<500){
            ite.y=j;
            SDL_RenderCopy(TheGame::Instance()->getRenderer(),TheTexture::Instance()->getTexture(m_textureID),NULL,&ite);
            j+=1.8;
            time=SDL_GetTicks();
        } else if(SDL_GetTicks()-time<1500){
            SDL_RenderCopy(TheGame::Instance()->getRenderer(),TheTexture::Instance()->getTexture(m_textureID),NULL,&ite);
        } else {
            remain=0; j=0; max--;
            x=30+rand()%1220;
            y=360+rand()%250;
        }

    }
}

void Item::shooted(int m, int n)
{
    if(remain==1){
        if(m>ite.x&&m<ite.x+ite.w&&n>ite.y&&n<ite.y+ite.h){
            if(m_textureID=="40"){
                TheGame::Instance()->tangdan();
            }
            if(m_textureID=="41"){
                TheGame::Instance()->tanghp();
            }
            if(m_textureID=="42"){
                TheGame::Instance()->tangsp();
            }
            remain=0; j=0;
            max--;
        }
    }
}
