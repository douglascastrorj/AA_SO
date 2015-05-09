#include <iostream>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_ttf.h"
#include "time.h"
#include "classes/Obj.h"
#include "classes/Asteroid.h"
#include "classes/Spaceship.h"
#include "thread_functions.cpp"
#include <cstdlib>
#include <pthread.h>


// CONSTANTS

#define ASTEROID_MAX_SPEED 3
const int FPS = 60;


SDL_Surface *screen = NULL;
using namespace std;
int main(){
	srand(time(NULL));
	

	//INITIALIZING SDL
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_WM_SetCaption("asTHREADoides", NULL);
	TTF_Init();
	Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 );
	screen=SDL_SetVideoMode(800,640,16,SDL_SWSURFACE);


	//CREATING THE RANDOM ASTEROIDS
	int nAsteroid = 5;
	Asteroid *asteroides = new Asteroid[nAsteroid];
	for(int i=0;i<nAsteroid;i++){
		string s = "img/"+to_string( (i%nAsteroid)+1) +".png";
		cout << s <<endl;
		asteroides[i].setSprite(s);
		asteroides[i].setVector(rand()%ASTEROID_MAX_SPEED,rand()%ASTEROID_MAX_SPEED);
		asteroides[i].setPos(rand()%screen->w,rand()%screen->h);
	}


	//the player
	Spaceship* player = new Spaceship();

	//THIS VARIABLE INDICATES WETHER THE GAME IS RUNNING
	bool running = true;

	//creating the threads for running each asteroid in
	pthread_t threads[nAsteroid];
	struct thread_data td[nAsteroid];
	int rc;
   	int i;
	for( i=0; i < nAsteroid; i++ ){

		td[i].thread_id = i;
      	td[i].a = &asteroides[i];
      	td[i].running = &running;
      	td[i].FPS = FPS;
      	td[i].nAsteroides = nAsteroid;
      	td[i].player = player;
      	td[i].asteroides = asteroides;


		cout <<"main() : creating thread, " << i << endl;
		rc = pthread_create(&threads[i], NULL,move_asteroid_thread,  (void *)&td[i]);
		// pthread_join(threads[i], NULL /* void ** return value could go here */);


		if (rc){
			cout << "Error:unable to create thread," << rc << endl;
			exit(-1);
		}
	}

	

	//background
	SDL_Surface* f = IMG_Load("img/espaco.jpg");

	SDL_Event event;	
	while(running){

		int t1 = SDL_GetTicks();

		//handling the events
		while(SDL_PollEvent(&event)){
			if( event.type==SDL_QUIT){
				running = false;
			}
			if( event.type == SDL_MOUSEMOTION )	{
				
			}
			if(event.type == SDL_KEYDOWN){
				switch( event.key.keysym.sym )
				{
					case SDLK_UP: { player->moveShip(screen); break;}
					case SDLK_LEFT:{ player->increaseAngle(); break;}
					case SDLK_RIGHT:{player->decreaseAngle(); break;}
				}
			}
		}
		SDL_BlitSurface(f,NULL,screen,NULL);

		for (int i = 0; i < nAsteroid; i++)	{
			asteroides[i].blit(screen);
			asteroides[i].move(screen);
		}


		// for (int i = 0; i < nAsteroid; i++)
		// {
		// 	for (int j = 0; j < nAsteroid; j++)
		// 	{
		// 		if(i!=j){
		// 			if(asteroides[i].colide(asteroides[j]))
		// 				cout << "colision detected " << i << " "<<j<<endl;
		// 		}
		// 	}
		// }

		player->moveShip(screen);
		player->blit(screen);


		int t2 = SDL_GetTicks();
        int wait = t2 - t1;
        wait = (1000/FPS) - wait;

        if(wait > 0)
			SDL_Delay(wait);
		

		SDL_Flip(screen);

	}

	SDL_Quit();
}