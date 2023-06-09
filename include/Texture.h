#ifndef TEXTURE_H
#define TEXTURE_H
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <iostream>
#include <stdio.h>
#include<map>
class Texture
{
    public:
    static Texture* Instance()
    {
    if(s_pInstance == 0)
    {
    s_pInstance = new Texture();
    }
    return s_pInstance;
    }

    bool load(std::string fileName,std::string id, SDL_Renderer* pRenderer);
       SDL_Texture* getTexture(std::string id){ return m_textureMap[id];}
    void clearer(){
        for(std::map<std::string, SDL_Texture*>::iterator itr = m_textureMap.begin(); itr != m_textureMap.end(); itr++)
        {
            delete (itr->second);
        }
    }
    private:
    static Texture* s_pInstance;
    Texture(){};
    ~Texture(){};
    std::map<std::string, SDL_Texture*> m_textureMap;
};
typedef Texture TheTexture;
#endif
