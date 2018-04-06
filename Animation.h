#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include "SDL/include/SDL_rect.h"
#define MAX_FRAMES 25

class Animation
{
public:
	float speed = 1.0f;
	SDL_Rect frames[MAX_FRAMES];
	bool repeat = true; //default animation is circular pattern

private:
	//float current_frame;
	//int last_frame = 0;

public:

	float current_frame; //old workaround
	int last_frame = 0;
	bool finish = false; //to active last

	void PushBack(const SDL_Rect& rect)
	{
		frames[last_frame++] = rect;
	}

	SDL_Rect& GetCurrentFrame() //modified for avoid cycle animations of wanted linears anims
	{
		current_frame += speed;
		if(current_frame >= last_frame && repeat == true)
			current_frame = 0;

		if (repeat)
			return frames[(int)current_frame];
		else if (!repeat)
		{
			if (current_frame >= last_frame)
			{
				finish = true;
				return frames[(int)last_frame - 1];
				
			}

			else
				return frames[(int)current_frame];
		}
			
	}
	//bool ret(return finish);
};

#endif