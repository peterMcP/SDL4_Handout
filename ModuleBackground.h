#ifndef __ModuleBackground_H__
#define __ModuleBackground_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

#include "p2Point.h"

struct SDL_Texture;

class ModuleBackground : public Module
{

public:

	ModuleBackground();
	~ModuleBackground();

	bool Start();
	update_status Update();

public:
	
	SDL_Texture* graphics = nullptr;
	SDL_Rect ground;
	SDL_Rect background;
	SDL_Rect ship;
	
	int shipPosX;
	int shipPosY;
	int shipBouyancySpeed;
	bool updatePos; //bool to wait X frameUpdates
	int lastFrame; //stores the count of frames before updatePos

	struct bouyancy
	{
		bool up;
		bool down;
	}shipBouyancy;

	Animation flag;
	Animation girl;
	Animation purpleMan;
	Animation menInBlue;
	Animation dancerMan;
	Animation pizzaHat;
	Animation oldMenCouple;
	iPoint oldMenPoint; //

};

#endif