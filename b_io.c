/**************************************************************
* Class:  CSC-415-0# Summer 2020
* Name: Wameedh Mohammed Ali
* Student ID: 920678405
* Project: Assignment 2 – Buffered I/O
*
* File: b_io.c
*
* Description: Using System Calls (API’s) to handle buffered IO.
*
**************************************************************/

#include "b_io.h"

int b_open (char* filename)
{
        //*** TODO ***:  Write open function to return file descriptor
        //               You must use the Linux System Calls
        //		 You may want to allocate the buffer here as well
        //		 But make sure every file has its own buffer

        //will be used to store index of the File Control Block that we will be returning from this function
        int indexOfFd = getMyFcb();
        myFileControlBlock[indexOfFd].linux_fd = open(filename, O_RDONLY);
        myFileControlBlock[indexOfFd].inUse = true;
               
        //checks if there was an error with opening the file
     if (myFileControlBlock[indexOfFd].linux_fd < 0)   { 
       // print the error code 
        printf("Error Number %d\n", errno); 
        exit(1); 
    }
        return indexOfFd;
}
	
int b_read(int fd, char * buffer, int count)
{
	  //*** TODO ***: Write buffered read function to return the data and # bytes read
	  // You must use the Linux System Calls and you must buffer the data
	  // in 512 byte chunks.

      int readValue;
    
      //checks if the postion is at the begining og the buffer are in the same place.
      if(myFileControlBlock[fd].position == myFileControlBlock[fd].buffer){
         
	    read(myFileControlBlock[fd].linux_fd, myFileControlBlock[fd].buffer, BUFFERSIZE);
       
      }
      //checks to see if buffer count is lower than 512 bytes, if so read the next 80 bytes
      //else; we will reload the buffer and get the remaining bytes
	  if( (myFileControlBlock[fd].position + count) < (myFileControlBlock[fd].buffer + BUFFERSIZE)){
          memcpy(buffer, myFileControlBlock[fd].position, count);
          myFileControlBlock[fd].position += count;
          myFileControlBlock[fd].remaining -= count;
	  } else {
          //if there is less than the requested bytes we will need to copy over the remaining bytes
	    //and call read() function to get the rest to print within the 80 byte buffer
	      memcpy(buffer, myFileControlBlock[fd].position,myFileControlBlock[fd].remaining);
	      readValue = read(myFileControlBlock[fd].linux_fd, myFileControlBlock[fd].buffer, BUFFERSIZE);
	      //null termnait the buffer
	      myFileControlBlock[fd].buffer[readValue] = '\0';
	      // readValue is 0 then we have reached the end of the file!
          if(readValue == 0){
              return readValue;
          }
	      //Reset the buffer position to the beginign of buffer
	      myFileControlBlock[fd].position = myFileControlBlock[fd].buffer;
	      //copy remaining bytes to buffer
	      memcpy(buffer+myFileControlBlock[fd].remaining, myFileControlBlock[fd].position, (count - myFileControlBlock[fd].remaining));
	      //Increment the buffer position by 'count' minus the remaining bytes
          myFileControlBlock[fd].position += (count - (myFileControlBlock[fd].remaining));
          //Rset the remaining to 512 bytes minus the remaining bytes left in the 
          myFileControlBlock[fd].remaining = BUFFERSIZE - (count - myFileControlBlock[fd].remaining);
	  }
	  return count;
}
	
void b_close (int fd){
	//*** TODO ***:  Close the file and release the buffer
	//				 You must use Linux System Calls

	//Close the file descriptor
	close(myFileControlBlock[fd].linux_fd);
    //Free the buffer and rest the linux fd in all indexes of the array to 0.
	 restmyFileControlBlock();
}

// Return the index of file control block that is not in use
int getMyFcb(){
    for(int i = 0; i < MAXFCB; i++) {
        if(myFileControlBlock[i].inUse == false)
            return i;
    }
    return -1;
}
// Initializes the FCB structs array
void initMyFileControlBlock(){
    //Initialize all the variables of my File Control Block in the array
    for(int i = 0; i < MAXFCB; i++){
       myFileControlBlock[i].remaining = BUFFERSIZE;
        myFileControlBlock[i].inUse = false;
        myFileControlBlock[i].buffer = (char *) malloc(BUFFERSIZE);
        myFileControlBlock[i].position = myFileControlBlock[i].buffer;
        myFileControlBlock[i].linux_fd = 0;
        
    }
}
// Rest the FCB structs array
void restmyFileControlBlock(){
     for(int i = 0; i < MAXFCB; i++){
	      free(myFileControlBlock[i].buffer);
	      myFileControlBlock[i].linux_fd = 0;
	      myFileControlBlock[i].inUse = false;
	      myFileControlBlock[i].position = NULL;
	      myFileControlBlock[i].remaining = 0;
      }

}