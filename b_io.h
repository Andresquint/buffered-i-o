/**************************************************************
* Class:  CSC-415-0# Summer 2020
* Name:
* Student ID:
* Project: Assignment 2 – Buffered I/O
*
* File: b_io.h
*
* Description:
*
**************************************************************/

#ifndef _B_IO_H
#define _B_IO_H

int b_open (char * filename);
int b_read (int fd, char * buffer, int count);
void b_close (int fd);

#endif

