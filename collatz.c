/*
Zena Nuhaily
Howework Assignment 2
collatz.c
*/

#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>



int main( int argc, char **argu)
{

  if(argc !=2)
    {//if arg dne 2, throw error and exit
      fprintf(stderr, "usage: %s <int>  \n", argu[0]);
      return -1;
    }

  int number = atoi(argu[1]);
  printf("\nCollatz Sequence:\n\n\t");

  if( number <= 0 )
    {//error handle 0 or a negative
      fprintf(stderr, "\nEntered Integer was not positive.\nYou entered %s. Sorry.\n", number);
      return -1;
    }

  if(number >= 1)
    {
      pid_t pid = fork();

      if(pid == 0)
        {
          //loop for child process
          while( number != 1)
            {
              printf("%i, ", number);
              if(number%2 == 0) //even
                {number = number/2; }
              else //odd
                {number = (3 * number + 1); }
            }
          printf("%i\n", number);//print last
        } else if (pid > 0)
        { //parent process
          wait();
        } else
        {
          printf("for failed errno = 0x%x, (%s) \n", __FILE__, errno, strerror(errno));
          return -1;
        }

      printf("\nPROCESS #%i COMPLETED\n", pid);
    }
	  return 0;
}

