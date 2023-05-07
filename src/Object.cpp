#include "Object.h"
#include "Game.h"
#include "Texture.h"
#include "SDL.h"
#include "cstdlib"

void Object::update()
{
    if(TheGame::Instance()->getstatus()==1||TheGame::Instance()->getstatus()==5||TheGame::Instance()->getstatus()==6){
        remain=0;
    }
    if(SDL_GetTicks()-time>2000&&remain==0&&rand()%TheGame::Instance()->gettansuat()==1){
        quai.x=x;
        quai.y=y;
        quai.w=w;
        quai.h=h;
        remain=1;
        time=SDL_GetTicks();
    }
    if(remain==2&&SDL_GetTicks()-timeb>300){
        remain=0;
    }
    if(remain==1&&SDL_GetTicks()-time>TheGame::Instance()->getqtocban()){
        remain=3;
        TheGame::Instance()->truhp(TheGame::Instance()->getqdame());
        time=SDL_GetTicks();
    }
    if(remain==3&&SDL_GetTicks()-time>150){
        remain=1;
        time=SDL_GetTicks();
    }
    if(remain==0){qhp=TheGame::Instance()->getqhp();}
}

void Object::shooted(int m, int n)
{
    if(remain==1){
        if(m>x&&m<x+w&&n>y&&n<y+h){
            insideq=true;
        }
        else insideq=false;
        if(m>wal.x&&m<wal.x+wal.w&&n>wal.y&&n<wal.y+wal.h){
            insidet=true;
        }
        else insidet=false;
        if(insideq==true&&insidet==false){
            if(m>=x+w*0.274&&m<=x+w*0.495&&n>=y+h*0.024&&n<=y+h*0.17){
                qhp-=150;
            }
            if(m>=x+w*0.272&&m<=x+w*0.67&&n>=y+h*0.17&&n<=y+h*0.311){
                qhp-=100;
            }
            if((m>=x+w*0.088&&m<=x+w*0.272&&n>=y+h*0.222&&n<=y+h*0.442)||
               (m>=x+w*0.272&&m<=x+w*0.591&&n>=y+h*0.311&&n<=y+h*0.442)||
               (m>=x+w*0.088&&m<=x+w*0.541&&n>=y+h*0.442&&n<=y+h*0.568)||
               (m>=x+w*0.541&&m<=x+w*0.68&&n>=y+h*0.469&&n<=y+h*0.568)){
                qhp-=100;
            }
            if((m>=x+w*0.061&&m<=x+w*0.236&&n>=y+h*0.568&&n<=y+h*0.955)||
               (m>=x+w*0.541&&m<=x+w*0.747&&n>=y+h*0.568&&n<=y+h*0.698)||
               (m>=x+w*0.644&&m<=x+w*0.852&&n>=y+h*0.698&&n<=y+h*0.766)||
               (m>=x+w*0.748&&m<=x+w*0.915&&n>=y+h*0.766&&n<=y+h*0.854)||
               (m>=x+w*0.836&&m<=x+w&&n>=y+h*0.854&&n<=y+h)){
                qhp-=60;
            }
            if(qhp<=0){
                timeb=SDL_GetTicks();
                remain=2;
                TheGame::Instance()->tangdiem(5);
            }
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

    SDL_RenderCopy(TheGame::Instance()->getRenderer(),TheTexture::Instance()->getTexture(m_textureID),NULL,&wal);

}

