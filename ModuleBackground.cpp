#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleBackground.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleBackground::ModuleBackground()
{
	// ground
	ground.x = 8;
	ground.y = 391;
	ground.w = 896;
	ground.h = 72;

	// Background / sky
	background.x = 72;
	background.y = 208;
	background.w = 768;
	background.h = 176;

	// flag animation
	flag.PushBack({848, 208, 40, 40});
	flag.PushBack({848, 256, 40, 40});
	flag.PushBack({848, 304, 40, 40});
	flag.speed = 0.08f;

	//ship background
	ship.x = 8;
	ship.y = 24;
	ship.h = 180;
	ship.w = 528;

	//girl animation
	girl.PushBack({624, 16, 31, 55});
	girl.PushBack({ 624, 80, 31, 55 }); //middle position
	girl.PushBack({ 624, 144, 31, 55 });
	girl.PushBack({ 624, 80, 31, 55 }); //return to middle pos
	girl.speed = 0.08f;

	//purpleMan Cycle
	purpleMan.PushBack({808, 24, 47, 31 });
	purpleMan.PushBack({ 808, 24, 47, 31 }); //repeat frame
	purpleMan.PushBack({ 808, 72, 47, 31 });
	purpleMan.PushBack({ 808, 120, 47, 31 });
	purpleMan.speed = 0.08f;

	//menInBlue
	menInBlue.PushBack({704,16,47,55});
	menInBlue.PushBack({ 704,80,47,55 });
	menInBlue.PushBack({ 704,144,47,55 });
	menInBlue.PushBack({ 704,80,47,55 });
	menInBlue.PushBack({ 704,144,47,55 });
	
	
	menInBlue.speed = 0.10f;

	//dancerMan Cycle
	dancerMan.PushBack({664,16, 31,55}); //start
	dancerMan.PushBack({ 664,80, 31,55 }); //final
	dancerMan.PushBack({ 664,16, 31,55 }); //start
	dancerMan.PushBack({ 664,80, 31,55 }); //final
	dancerMan.PushBack({ 664,16, 31,55 }); //start
	dancerMan.speed = 0.05f;

	//oldMenCouple
	oldMenCouple.PushBack({552,8,63,63});
	oldMenCouple.PushBack({552,80,63,55});
	oldMenCouple.PushBack({552,144,63,55});
	oldMenCouple.speed = 0.12f;

	oldMenPoint.x = 0;
	oldMenPoint.y = 159;

	//pizzaHat man
	pizzaHat.PushBack({760,16,40,40});
	pizzaHat.PushBack({760,64,40,40});
	pizzaHat.PushBack({ 760,112,40,40 });
	pizzaHat.PushBack({ 760,64,40,40 });
	pizzaHat.speed = 0.09f;
}

ModuleBackground::~ModuleBackground()
{}

// Load assets
bool ModuleBackground::Start()
{
	//start ship bouyancy values
	shipBouyancy = {true,false}; //up, down bools
	updatePos = true;
	shipPosY = -4;
	shipBouyancySpeed = 1;
	shipPosX = -200;

	//lastFrameCouple = 1;

	LOG("Loading background assets");
	bool ret = true;
	graphics = App->textures->Load("ken_stage.png");
	return ret;

}

// Update: draw background
update_status ModuleBackground::Update()
{
	// Draw everything --------------------------------------
	App->render->Blit(graphics, 0, 0, &background, 0.75f); // sea and sky
	App->render->Blit(graphics, 560, 8, &(flag.GetCurrentFrame()), 0.75f); // flag animation

	// TODO 2: Draw the ship from the sprite sheet with some parallax effect
	//And extended todo, move up and down to simulate a little buoyancy
	//And entry anim

	if (shipBouyancy.up && updatePos)
	{
		shipPosY += shipBouyancySpeed; //updates pos
		if (shipPosX < -57) //x animation stop position
			shipPosX += 2;
		updatePos = false;
		if (shipPosY >= 0) //if reach max pos
		{
			shipBouyancy.up = false;
			shipBouyancy.down = true;
		}
	}
	else if (shipBouyancy.down && updatePos)
	{
		shipPosY -= shipBouyancySpeed;
		if(shipPosX < -57) 
			shipPosX += 2;
		//if (shipPosX <= -47) shipPosX--; //slowdown speed increment while up
		updatePos = false;
		if (shipPosY <= -5)
		{
			shipBouyancy.up = true;
			shipBouyancy.down = false;
		}
	}
	lastFrame += 1;
	if (lastFrame >= 20) //wait x frames before update position bool
	{
		lastFrame = 0;
		updatePos = true;
	}
	///////////ship scene entry animation
	//max x pos = 50 aprox


	App->render->Blit(graphics, shipPosX, shipPosY, &ship, 0.8f);

	// TODO 3: Animate the girl on the ship (see the sprite sheet)
	//extended todo, all people on background
	//128 = distance ship x=0 to first pixels of purlple and old men
	App->render->Blit(graphics, shipPosX+192, shipPosY + ( 104 ), &(girl.GetCurrentFrame()), 0.8f); //girl
	App->render->Blit(graphics, shipPosX+128, shipPosY + (24), &(purpleMan.GetCurrentFrame()), 0.8f); //purpleMan
	App->render->Blit(graphics, shipPosX+288, shipPosY + (96), &(menInBlue.GetCurrentFrame()), 0.8f); //menInBlue  
	App->render->Blit(graphics, shipPosX+96+128, shipPosY + (104), &(dancerMan.GetCurrentFrame()), 0.8f); //dancerMan 
	App->render->Blit(graphics, shipPosX+88,shipPosY + (24), &(pizzaHat.GetCurrentFrame()), 0.8f);

	/////oldMenCouple
	Animation* current_animation = &oldMenCouple;
	SDL_Rect r = current_animation->GetCurrentFrame();

	App->render->Blit(graphics, oldMenPoint.x+shipPosX+128, 159+shipPosY -r.h , &r, 0.8f);
	/////////////////
	App->render->Blit(graphics, 0, 170, &ground); //draw ground

	return UPDATE_CONTINUE;
}