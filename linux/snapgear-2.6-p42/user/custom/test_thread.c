 /* example.c*/
#include <stdio.h>
#include <pthread.h>
void thread(void)
{    
  int i,j; 
 
  while(1) {
    for (i = 0;i < 100000;i++) {
      j++;
    }
    printf("This is a pthread %i.\n",j);
  }
}  
                   
int main(void)
{    
  pthread_t id;
  int i,ret,j;
  ret=pthread_create(&id,NULL,(void *) thread,NULL);

  if(ret!=0){
    printf ("Create pthread error!\n");
    exit (1);
  }
  while(1) {
    printf("This is the main process %i.\n",j);
    for (i = 0;i < 100000;i++) {
      j++;
    }
  }
  
  pthread_join(id,NULL);
  return (0);
}   
 
 
 
  
 
