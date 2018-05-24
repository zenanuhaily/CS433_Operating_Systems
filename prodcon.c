/**************************************************************************
Zena Nuhaily
Assignment 4 
prodcon.c
**************************************************************************/

#include <unistd.h>     
#include <sys/types.h>  
#include <errno.h>      
#include <stdio.h>      
#include <stdlib.h>     
#include <pthread.h>    
#include <string.h>     
#include <semaphore.h>  
#include <sched.h>

pthread_t tid[2];
pthread_mutex_t mutex1;

int counter = 5;

void *producer(void *arg)
{
  int i, register1;


  pthread_mutex_lock(&mutex1);

  /* Begin the critical section */
  register1 = counter;
  register1 = register1 + 1;

  /* use loop to simulate some processing */
  for (i = 0; i< (0xFFFFF); i++);

  /* enforce a thread switch to illustrate "interleaving" */
  sched_yield();

  counter = register1;
  /* end the critical section */

  pthread_mutex_unlock(&mutex1);

  printf("%s:Counter = %d \n", __FUNCTION__, counter);

  return NULL;
}

void *consumer(void *arg)
{

  int i,register2;

  pthread_mutex_lock(&mutex1);

  /* Begin the critical section */
  register2 = counter;
  register2 = register2 - 1;

  /* use loop to simulate processing */
  for (i = 0; i< (0xFFFFF); i++);

  counter = register2;
  /* End the critical section */

  pthread_mutex_unlock(&mutex1);

  printf("%s:Counter = %d \n", __FUNCTION__, counter);

  return NULL;
}



static unsigned short checksum(unsigned short *ptr, int nbytes)
{

  int sum;
  unsigned short exbyte;
  unsigned short cksum;

  sum = 0;
  while (nbytes > 1 )
 {
    sum += *ptr++;
    nbytes -= 2;
  }

  if (nbytes == 1) {
    exbyte = 0;
    *((unsigned char *) &exbyte) = *(unsigned char *)ptr;
    sum += exbyte;
  }

  sum = (sum >> 16) + (sum & 0xffff);
  sum += (sum >> 16);
  cksum = ~sum;

  return cksum;

}

int main(int argc, char *argv[])
{
  int i = 0;
  int err;

  if (argc !=2){
    fprintf(stderr,"usage: a.out <memsize> <ntimes>\n");
    /*exit(1);*/
    return -1;}

    if (atoi(argv[1]) >= 64000){
      fprintf(stderr,"Argument is limited to 64k\n",atoi(argv[1]));
      /*exit(1);*/
      return -1; }

    if (atoi(argv[2]) < 0) {
      fprintf(stderr,"Argument must be non-negative\n",atoi(argv[2]));
      /*exit(1);*/
      return -1;
    }

  /* Create the mutex semaphore to protect the critical section */
  if (pthread_mutex_init(&mutex1, NULL) != 0) {
    printf("\n error creating mutex\n");
    return -1;
  }

  err = pthread_create(&(tid[0]), NULL, &producer, NULL);
  if (err != 0) {
    printf("\ncan't create thread 1 :[%s]", strerror(err));
  }

  err = pthread_create(&(tid[1]), NULL, &consumer, NULL);
  if (err != 0) {
    printf("\ncan't create thread 2 :[%s]", strerror(err));
  }

  pthread_join(tid[0], NULL);
  pthread_join(tid[1], NULL);

  printf("Final Counter = %d \n", counter);

  pthread_mutex_destroy(&mutex1);

  unsigned short cksum;
  unsigned char buf[512];
  int   fd;
  int   x=0;

  if (argc != 2) 
    {
    //  fprintf(stderr, "Usage: %s <filename> \n", argv[0]);
    return EXIT_FAILURE;
    }

  // fd = open(argv[1], O_CREAT | O_WRONLY, 0644);
  if (fd == -1) 
    {
     return EXIT_FAILURE;
    }

  srand(2);
  for (x = 0; x < 30; x++) 
    {
      buf[x] = (unsigned char)(rand() % 255);
    }

  cksum = checksum((unsigned short *)&buf[0], 510);
  printf("cksum = 0x%hx \n", cksum);

  memcpy((void *)&buf[30], (void *)&cksum, 2);
  //      
   
    
  

  return EXIT_SUCCESS;


return 0;
}
