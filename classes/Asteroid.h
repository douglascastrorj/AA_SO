#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <iostream>
// #include "Obj.h"

#define BIG 3
#define MEDIUM 2
#define LITTLE 1

#define BIG_DIM 40
#define MID_DIM 20
#define LITTLE_DIM 10
using namespace std;
class Asteroid : public Obj
{
private:
	int size;

public:

	Asteroid(){
		Obj();
		this->size = BIG;
		this->setSprite ("img/1.png");
		this->setPos(0,0,BIG_DIM,BIG_DIM);
		
		this->setVector(1,3);//x,y
	}

	Asteroid(SDL_Surface *sprite,SDL_Rect pos){
		Obj();
		this->size = BIG;
		this->setSprite( sprite);
		this->setPos (pos.x,pos.y,pos.w,pos.h);

	}
	~Asteroid(){}

	void setSize(int size){
		if (size <= BIG and size >= LITTLE)
		{
			this->size=size;
		}
	}

	
	
};