#ifndef OBJECT_H
#define OBJECT_H
#include <string>
#include<iostream>
#include "Texture.h"
class Object
{
    public:
        Object(int _m_width, int _m_height, float _m_PosX, float _m_PosY,std::string _m_textureID,float _x,float _y, int _w, int _h, std::string _quaiID, std::string _qbID, std::string _qcID, int _dame)
        :enm{_m_PosX,_m_PosY,_m_width,_m_height}
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
            dame=_dame;
        }
        virtual ~Object(){}
        void update();
        void check(int m, int n);
        void render();
        void shooted(int m, int n);
    private:
        float x,y;
        int remain;
        int w,h,dame;
        SDL_Rect enm,quai;
        double time,timeb;
        float att;
        std::string m_textureID, quaiID, qbID, qcID;
        SDL_Event* e;
		bool insidet=false, insideq=false;

};

#endif // OBJECT_H
