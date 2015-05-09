#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <iostream>
#include <string>
#include <cmath>


#define MAX_SPEED 5

using namespace std;
class Obj
{

	SDL_Rect pos; //position on the screen
	SDL_Surface* sprite; //image of the obj
	int vector[2];
	int maxVel;


public:

	Obj(){
		this->sprite = IMG_Load("img/1.png");
		this->pos.x = 0;
		this->pos.y = 0;
		this->pos.w = 40;
		this->pos.h = 40;
		this->vector[0] = 0;//x
		this->vector[1] = 0;//y
	}

	~Obj(){}


	void setPos(int x,int y){
		this->pos.x = x;
		this->pos.y = y;
	}

	void setPos(int x,int y,int w,int h){
		this->pos.x = x;
		this->pos.y = y;
		this->pos.w = w;
		this->pos.h = h;
	}

	SDL_Rect* getPos(){
		return &this->pos;
	}

	SDL_Surface* getSprite(){
		return this->sprite;
	}

	void setSprite(string path){
		this->sprite = IMG_Load(path.c_str());
	}

	void setSprite(SDL_Surface* sprite){
		this->sprite = sprite;
	}
	

	void setVector(int x,int y){
		this->vector[0] = (x%MAX_SPEED)+1;
		this->vector[1] = (y%MAX_SPEED)+1;
	}

	int* getVector(){
		return this->vector;
	}

	void blit(SDL_Surface* screen){
		SDL_BlitSurface(this->getSprite(),NULL,screen,this->getPos());
	}

	bool colide(Obj obj){
		int x1,x2,y1,y2,r1,r2;
		x1 = this->getPos()->x+this->getPos()->w/2;
		y1 = this->getPos()->y+this->getPos()->h/2;
		r1 = this->getPos()->w/2;

		x2 = obj.getPos()->x+obj.getPos()->w/2;
		y2 = obj.getPos()->y+obj.getPos()->h/2;;
		r2 = obj.getPos()->w/2;


		float distance = sqrt( pow( x2 - x1, 2 ) + pow( y2 - y1, 2 ) );

		if( distance <= ( r1 + r2 ) )
        	return true;
        return false;

	}

	void move(SDL_Surface *screen){
		// this->setPos( this->getPos()->x+this->getVector()[0] ,this->getPos()->y+this->getVector()[1]);
		this->pos.x+=this->vector[0];
		this->pos.y+=this->vector[1];

		if (this->pos.x > screen->w){
			this->pos.x = 0;
		}
		else if(this->pos.x < 0)
			this->pos.x = screen->w;

		if (this->pos.y > screen->h){
			this->pos.y = 0;
		}
		else if(this->pos.y < 0)
			this->pos.y = screen->h;

		// cout << "x " << this->pos.x <<"  y "<<this->pos.y<< endl;
	}
	
};