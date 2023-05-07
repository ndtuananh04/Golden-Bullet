#ifndef OBJECT_H
#define OBJECT_H
#include <string>
#include<iostream>
#include "Texture.h"
class Object
{
    public:
        Object(int _m_width, int _m_height, int _m_PosX, int _m_PosY,std::string _m_textureID, float _x, float _y, float _w, float _h, std::string _quaiID, std::string _qbID, std::string _qcID)
        :wal{_m_PosX,_m_PosY,_m_width,_m_height}
        {   remain=0;
            time=SDL_GetTicks();
            x=_x;
            y=_y;
            w=_w;
            h=_h;
            m_textureID=_m_textureID;
            quaiID=_quaiID;
            qbID=_qbID;
            qcID=_qcID;
        }
        ~Object(){}
        void update();
        void check(int m, int n);
        void render();
        void shooted(int m, int n);
        void setqstatus(int r){
            remain=r;
        }
    private:
        float x,y,w,h;
        int remain;
        int qhp;
        SDL_Rect wal,quai;
        double time,timeb;
        float att;
        std::string m_textureID, quaiID, qbID, qcID;
        SDL_Event* e;
		bool insidet=false, insideq=false;

};

#endif // OBJECT_H
