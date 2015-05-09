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
					my_data->a->setVector(my_data->asteroides[i].getVector()[0]+my_data->a->getVector()[0],my_data->asteroides[i].getVector()[1]+my_data->a->getVector()[1]);
               my_data->asteroides[i].setVector(my_data->asteroides[i].getVector()[0]+my_data->a->getVector()[0],my_data->asteroides[i].getVector()[1]+my_data->a->getVector()[1]);
				}
			}
		}
      usleep(300);

	}


   pthread_exit(NULL);
}


void *move_asteroides_thread(void *threadarg)
{
   struct thread_data *my_data;

   my_data = (struct thread_data *) threadarg;

   cout << "Thread ID : " << my_data->thread_id << endl;

   while(my_data->running){

      for(int i =0;i<my_data->nAsteroides-1;i++){   
         for(int j =i+1;j<my_data->nAsteroides;j++){
            if(my_data->asteroides[i].colide(my_data->asteroides[j])){
               int x1,x2,y1,y2;
               x1 = my_data->asteroides[i].getVector()[0];
               y1 = my_data->asteroides[i].getVector()[1];

               x2 = my_data->asteroides[j].getVector()[0];
               y2 = my_data->asteroides[j].getVector()[1];

               my_data->asteroides[i].setVector(x2-x1,y2-y1);
               my_data->asteroides[j].setVector(x1-x2,y1-y2);
               
            }
            
         }
      }
      usleep(300);

   }


   pthread_exit(NULL);
}
