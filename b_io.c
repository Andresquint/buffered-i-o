/**************************************************************
* Class:  CSC-415-0# Summer 2020
* Name:
* Student ID:
* Project: Assignment 2 – Buffered I/O
*
* File: b_io.c
*
* Description:
*
**************************************************************/

#include "b_io.h"

int b_open (char * filename)
	{
	//*** TODO ***:  Write open function to return file descriptor
	//               You must use the Linux System Calls
	//				 You may want to allocate the buffer here as well
	//				 But make sure every file has its own buffer
	}
	
int b_read (int fd, char * buffer, int count)
	{
	//*** TODO ***:  Write buffered read function to return the data and # bytes read
	//               You must use the Linux System Calls and you must buffer the data
	//				 in 512 byte chunks.
	
	}
	
void b_close (int fd)
	{
	//*** TODO ***:  Close the file and release the buffer
	//				 You must use Linux System Calls
	}