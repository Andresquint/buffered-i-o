/**************************************************************
* Class:  CSC-415-0# Summer 2020
* Name: Wameedh Mohammed Ali
* Student ID: 920678405
* Project: Assignment 2 – Buffered I/O
*
* File: b_io.h
*
* Description: Header file for b_io.c that includs prototypes functions. 
*
**************************************************************/

#ifndef _B_IO_H
#define _B_IO_H


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include<errno.h> // Header file defines the integer variable errno

#define MAXFCB 20 //Defined the max number of files
#define BUFFERSIZE 512 //Defined Buffer of 512 as instructed in the hw
#define BYTESTOBEREAD 80 // number of bytes to be read and print form the buffer
extern int errno;


int b_open (char * filename);
int b_read (int fd, char * buffer, int count);
void b_close (int fd);

void initMyFileControlBlock();
void restmyFileControlBlock();
int getMyFcb();

struct fileControlBlock{
  int linux_fd; // linux file discriptor
  char* buffer; // buffer that will alocate 512 bytes
  char* position; // position of buffer
  bool inUse; // state of the file in use or not
  int remaining; // to track the remaining bytes in buffer
};
struct fileControlBlock myFileControlBlock[MAXFCB];

#endif

