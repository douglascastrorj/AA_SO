#include <stdlib.h>
#include <unistd.h>


struct thread_data{
   int  thread_id;
   int FPS;
   Spaceship *player;
   Asteroid *asteroides;
   int nAsteroides;
   bool *running;
   // SDL_Surface *screen;
   Asteroid* a;
};

void *move_asteroid_thread(void *threadarg)
{
   struct thread_data *my_data;

   my_data = (struct thread_data *) threadarg;

   cout << "Thread ID : " << my_data->thread_id << endl;

	while(my_data->running){

		for(int i =0;i<my_data->nAsteroides;i++){
			if(i != my_data->thread_id ){
				if(my_data->a->colide(my_data->asteroides[i])){
					// cout << i << " "<<  my_data->thread_id<<" colision detected\n" ;
					my_data->a->setVector(0,0);
				}
			}
			usleep(300);
		}

	}


   pthread_exit(NULL);
}
