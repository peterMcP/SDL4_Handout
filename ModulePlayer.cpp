#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer::ModulePlayer()
{
	position.x = 100;
	position.y = 220;

	// idle animation (arcade sprite sheet)
	idle.PushBack({ 7, 14, 60, 90 });
	idle.PushBack({ 95, 15, 60, 89 });
	idle.PushBack({ 184, 14, 60, 90 });
	idle.PushBack({ 276, 11, 60, 93 });
	idle.PushBack({ 366, 12, 60, 92 });
	idle.speed = 0.2f;

	// walk forward animation (arcade sprite sheet)
	//forward.frames.PushBack({9, 136, 53, 83});
	//forward.PushBack({14,136,53,83}); //first frame
	forward.PushBack({ 78, 131, 60, 88 });
	forward.PushBack({ 162, 128, 64, 92 });
	forward.PushBack({ 259, 128, 63, 90 });
	forward.PushBack({ 352, 128, 54, 91 });
	forward.PushBack({ 432, 131, 50, 89 });
	forward.speed = 0.1f;

	// TODO 4: Make ryu walk backwards with the correct animations
	backward.PushBack({ 542,131,61,87 });
	backward.PushBack({ 628, 129,59,90 });
	backward.PushBack({ 713, 128,57,90 });
	backward.PushBack({ 797,127,58,90 });
	backward.PushBack({ 883,128,58,91 });
	backward.PushBack({ 974, 129, 57,89 });
	backward.speed = 0.1f;

	//------------HomeWork
	//punch
	punch.PushBack({19,272,64,91}); 
	punch.PushBack({108,272,92,91});
	punch.PushBack({ 19,272,64,91 });
	punch.speed = 0.20f;
	punch.repeat = false;
	//kick
	kick.PushBack({ 607, 269,60,94 });
	kick.PushBack({689,267,66,92});
	kick.PushBack({777,265,114,94});
	kick.PushBack({ 689,267,66,92 });
	kick.PushBack({ 607, 269,60,94 });
	kick.speed = 0.16f;
	kick.repeat = false;
	//jumpUp
	jumpUpwards.PushBack({17,847,55,85});
	jumpUpwards.PushBack({100,823,56,104});
	jumpUpwards.PushBack({176,805,50,97});
	jumpUpwards.PushBack({251,798,54,77});
	jumpUpwards.speed = 0.12f;
	jumpUpwards.repeat = false;
	//jumpDown
	jumpDown.PushBack({327,813,48,70});
	jumpDown.PushBack({397,810,48,89});
	jumpDown.PushBack({464,819,55,109});
	jumpDown.speed = 0.12f;//0.16f;
	jumpDown.repeat = false;

}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	isPunching = false;
	isGrounding = true;
	isJumping = false;

	LOG("Loading player textures");
	bool ret = true;
	graphics = App->textures->Load("ryu.png"); // arcade version
	return ret;
}

// Update: draw background
update_status ModulePlayer::Update()
{

	Animation* current_animation = &idle;

	int speed = 1;

	if (App->input->keyboard[SDL_SCANCODE_D] == 1 && 
		App->input->keyboard[SDL_SCANCODE_P] == 0 &&
		App->input->keyboard[SDL_SCANCODE_K] == 0) //&& isPunching == false)
	{
		current_animation = &forward;
		position.x += speed;
	}

	if (App->input->keyboard[SDL_SCANCODE_A] == 1 && 
		App->input->keyboard[SDL_SCANCODE_P] == 0 &&
		App->input->keyboard[SDL_SCANCODE_K] == 0) //&& isPunching == false)
	{
		current_animation = &backward;
		position.x -= speed;
	}
	if (App->input->keyboard[SDL_SCANCODE_P] == 1 && !isPunching)
	{
		//current_animation = &punch;
		isPunching = true;
		punch.finish = false;
	}
	if (App->input->keyboard[SDL_SCANCODE_K] == 1 && !isKicking)
	{
		//current_animation = &kick;
		isKicking = true;
		kick.finish = false;
	}
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1 && isGrounding)
	{
		isJumping = true;
		isGrounding = false;
		//current_animation = &jumpUpwards;
	}

	if (isPunching)
	{
		current_animation = &punch;
		//bool temp = current_animation->finish;
		if (current_animation->finish)
		{
			current_animation->current_frame = 0;
			isPunching = false;
			
			//current_animation = &idle;
		}
		
	}

	if (isKicking)
	{
		current_animation = &kick;
		if (current_animation->finish)
		{
			current_animation->current_frame = 0;
			isKicking = false; 
		}
	}

	if (isJumping || !isGrounding)
	{
		if (isJumping == false) //down
		{
			current_animation = &jumpDown; //jumpDown anim
			position.y += 5; // = 200 = 200 + x -> (200+x) = (200+x) + x
			//isJumping == false;
			/*int current = current_animation->current_frame;
			int last = current_animation->last_frame - 1;
			if (current == last)
				current_animation->current_frame = 2;// current_animation->last_frame;*/

			if (position.y >= 220) //and reset jump animations last frames vars
			{					   //for prepare clean next jump
				isGrounding = true;
				jumpUpwards.current_frame = 0; //animation jumpUpwards
				current_animation->current_frame = 0; //this (if)animation -> jumpDown
			}
		}

		 if(!isGrounding && isJumping)
		{
			
			current_animation = &jumpUpwards;
			position.y -= 5; //update position
			/*int current = current_animation->current_frame;
			int last = current_animation->last_frame-1;
			if (current == last)
				current_animation->current_frame = 3;// current_animation->last_frame;*/

			if (position.y <= 100) isJumping = false; //if we reach the max estiulated height
		}

	}
	
	// Draw everything --------------------------------------
	SDL_Rect r = current_animation->GetCurrentFrame();
	
	App->render->Blit(graphics, position.x, position.y - r.h, &r);
	
	return UPDATE_CONTINUE;
}