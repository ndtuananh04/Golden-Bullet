#include<SDL.h>
#include"Game.h"
int main(int argc, char* argv[])
{
    TheGame::Instance()->init("The Box", 100, 50, 1280, 720, 0);

while(TheGame::Instance()->running())
{
    TheGame::Instance()->handleEvents();
    TheGame::Instance()->update();
    TheGame::Instance()->render();
}
TheGame::Instance()->clean();
return 0;
}

