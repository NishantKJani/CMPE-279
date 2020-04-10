// Server side C/C++ program to demonstrate Socket programming 
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#define PORT 80

int main(int argc, char const *argv[]) 
{ 
    printf("\n \n welcome to new exec child and new socket passed as arguments \n");

    /*int i=0;
    for(i=0;i<argc;i++)
    {
        printf("%s \n",argv[i]);
    }*/

    int new_socket=atoi(argv[0]);
    char buffer[1024] = {0}; 
    char *hello = "Hello from server"; 

    //printf("value of new socket= %d",new_socket);
    int valread = read( new_socket , buffer, 1024); 
    printf("%s\n",buffer ); 
    send(new_socket , hello , strlen(hello) , 0 ); 
    printf("Hello message sent\n");   
    
    
     return 0; 
} 
