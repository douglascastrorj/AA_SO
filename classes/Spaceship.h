#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <iostream>
#include <cmath>
// #include "Obj.h"
#define DIM 40
using namespace std;
class Spaceship : public Obj
{
private:
	int angle;

	int v;
	SDL_Surface* sprite1;
	SDL_Surface* sprite2;

	Obj tiros[10];

public:


	Spaceship(){
		Obj();
		this->setV(4);
		this->angle = 0;
		this->setSprite ("img/goku1.png");
		this->setPos(0,0,DIM,DIM);

		this->sprite1 = IMG_Load("img/goku1.png");
		this->sprite2 = IMG_Load("img/goku2.png");
		
		this->setVector(0,0);//x,y
	}

	Spaceship(SDL_Surface *sprite,SDL_Rect pos){
		Obj();
		this->setV(4);
		this->angle = 0;
		this->setSprite(sprite);
		this->setPos (pos.x,pos.y,pos.w,pos.h);

	}
	~Spaceship(){}	

	void switchSprite(){
		if(this->getVector()[0] > 0)
			this->setSprite(sprite1);
		else
			this->setSprite(sprite2);
	}

	void increaseAngle(){
		this->angle+=15;
	}
	void decreaseAngle(){
		this->angle-=15;
	}

	void moveShip(SDL_Surface *screen){
		int v = this->getV();
		const double pi = 3.1415926535897;
		// this->setPos( this->getPos()->x+this->getVector()[0] ,this->getPos()->y+this->getVector()[1]);
		this->setVector(v*cos(pi*this->angle/180),-v*sin(pi*this->angle/180));

		this->switchSprite();
		// cout << this->angle<< endl;
		// cout << "x "<<this->getVector()[0]<< " y "<<this->getVector()[1] << endl;
		this->move(screen);

	}

	void setV(int v){
		this->v = v;
	}
	int getV(){
		return this->v;
	}

	void atirar(){

	}
	
};