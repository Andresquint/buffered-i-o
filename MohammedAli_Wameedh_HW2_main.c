/**************************************************************
* Class:  CSC-415-0# Summer 2020
* Name: Wameedh Mohammed Ali
* Student ID: 920678405
* Project: Assignment 2 – Buffered I/O
*
* File: MohammedAli_Wameedh_HW2_main.c
*
* Description: The main method for the program where we call our three methods, open read and close.
* 
*
**************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "b_io.h"


int main(int argc, char* argv[]){
	int fdIndex;
    int cnt;

	//allocating 80 bytes for myBuf
	char* myBuf = (char *)malloc(BYTESTOBEREAD);
	
	//Initializes the struct arrays
    //The array is limited to 20 files per the HW instruction
	initMyFileControlBlock();

	//for(int i = 1; i < argc; i++){
    // open the file and return an index of the FCb fd in array of structs.
	fdIndex = b_open(argv[1]);
	
	do {
	  cnt = b_read(fdIndex, myBuf, BYTESTOBEREAD);
	  if(cnt == 0){
	      break;
      }
	  printf("%s\n", myBuf);
	} while(cnt == BYTESTOBEREAD);
	b_close(fdIndex); // Close the linux fd and free the buffers 
   // }

    // Free myBuf(80 bytes)
	free(myBuf);

	//b_close(fd);

  return 0;
}
