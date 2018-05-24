/**********************************************************************************************************************************************************
Zena Nuhaily
Assignment 5
CS433
vmmgr.c
***********************************************************************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#define _GNU_SOURCE
//global vars
const int PAGE_SIZE = 256;
const int VM_SIZE = 256;
const int MM_SIZE = 128;
const int TLB_SIZE = 16;


int main(int argc, char *argv[])
{

  int physical_memory[MM_SIZE];
  int virtual_memory[VM_SIZE][2];
  int tlb[TLB_SIZE][2];

  // INITIAL PAGE TABLE FILLING

  for(int i = 0; i < VM_SIZE; i++)
    {
      virtual_memory[i][0] = (i > MM_SIZE - 1)? -1 : i;
      virtual_memory[i][1] = (i > MM_SIZE - 1)? -1 : MM_SIZE - i;
    }
  for(int i = 0; i < MM_SIZE; i++)
    {
      physical_memory[i] = i;
    }

  for(int i = 0; i < TLB_SIZE; i++)
    {
      tlb[i][0] = (i > TLB_SIZE - 1)? -1 : i;
      tlb[i][1] = (i > TLB_SIZE - 1)? -1 : TLB_SIZE - i;
    }

  // Error Checking: Check to see if correct arguments exist
  if(argc != 2)
    {
    printf("Incorrect Number of Arguments.\n");
    return 1;
    }

  FILE *pFile;
  pFile = fopen(argv[1], "r");

  //checks to see if the .txt file supplied is empty
  if(pFile == NULL)
    {
      printf("Error opening a file %s: %s\n", argv[1], strerror(errno));
      exit(EXIT_FAILURE);
    }

  char *line = NULL;
  size_t len = 0;
  size_t read;

  int page_number = 0;
  int physicalAddress = 0;
  int pageFaultCount = 0;
  int TLBHitCount = 0;
  double pageFaultRate = 0.0;
  double TlbHitRate = 0.0; 

  while((read = getline(&line, &len, pFile)) != -1)
    {
    int offset = atoi(line) & 255;
    int page = atoi(line) & 65280;
    int page_table_number = page >> 8;
    int tlb_hit = 0;//
    
    for(int i = 0; i < TLB_SIZE; i++){
      if(tlb[i][0] == page_table_number){
	tlb_hit = 1;
	printf("TLB HIT\n");
	TLBHitCount++;//*****************************************
	break;
      }
    }

    if(virtual_memory[page_table_number][0] < 0 && !tlb_hit)
      {
      pageFaultCount++;
      // TLBHitCount++;

      srand(time(NULL));
      int r = rand();


      int largest = 0;
      int evict = 0;
      for(int i = 0; i < VM_SIZE; i++){
	if(virtual_memory[i][1] > largest)
	  {
	    largest = virtual_memory[i][1];
	    evict = i;
	}
      }

      int tlb_replace = r % 15;
      tlb[tlb_replace][0] = page_table_number;
      tlb[tlb_replace][1] = virtual_memory[evict][0];
      virtual_memory[page_table_number][0] = virtual_memory[evict][0];
      virtual_memory[page_table_number][1] = 0;
      virtual_memory[evict][0] = -1;
      virtual_memory[evict][1] = 0;
      //TLBHitCount++;
      }

    //printing Virtual Address
    if (page < 100) 
      {
	printf("Virtual Address = %d     \t", page);
      }
    else if (page < 1000) 
      {
	printf("Virtual Address = %d   \t", page);
      }
    else 
      {
	printf("Virtual Address = %d  \t", page);
      }


    //calculate physical address
    physicalAddress = (physical_memory[virtual_memory[page_table_number][0]] * PAGE_SIZE) + offset;

    printf("Physical Address: %d\n", physicalAddress);
    page_number++;

    for(int i = 0; i < VM_SIZE; i++)
      {
	virtual_memory[i][1]++;
      }
  }

  //calculates the % of page faults
  pageFaultRate = (double) pageFaultCount / 1000 * 100;
  printf("\nPage Fault Rate: %.2f%% \n", pageFaultRate);
  
  //calculate TLB Hit rate
  TlbHitRate = (double) TLBHitCount / 1000 * 100;//error right here ***************************************************************************************************** 
  printf("\nTLB Hit Rate: %.2f%% \n", TlbHitRate);
  
  free(line);
  fclose(pFile);

  exit(EXIT_SUCCESS);

}
