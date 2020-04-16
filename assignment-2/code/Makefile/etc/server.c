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
    int server_fd, new_socket, valread; 
    struct sockaddr_in address; 
    int opt = 1;
    int addrlen = sizeof(address); 
    char buffer[1024] = {0}; 
    char *hello = "Hello from server"; 
       
    printf("you entered %s",argv[1]);
    // Creating socket file descriptor 
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    } 
       
    // Forcefully attaching socket to the port 8080 
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR , &opt, sizeof(opt)))
    { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    } 
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons( PORT ); 
       
    // Forcefully attaching socket to the port 8080 
    if (bind(server_fd, (struct sockaddr *)&address,  
                                 sizeof(address))<0) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
    if (listen(server_fd, 3) < 0) 
    { 
        perror("listen"); 
        exit(EXIT_FAILURE); 
    } 
    // Upper part sets up the socket
    //seteuid(-1);
    printf("mode of execution=%d \n",getuid());
    int n1=fork();
    //int n1=0;

    if(n1==0)
     {
        printf("Child Process\n");
        printf("Setting the UID to 65535:- %d \n",setuid(65535));

        printf("new Child message %d\n",getuid());     
       //Processes data from the client
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address,  
                           (socklen_t*)&addrlen))<0) 
        { 
            perror("accept"); 
            exit(EXIT_FAILURE); 
        } 

        char array[64];
        int n=new_socket;
        int len=0;
        while(n>0)
        {
            n=n/10;
            len++;
        }

        int i=0;
        n=new_socket;
        for(i=0;i<len;i++)
        {
            int r=n%10;
            n=n/10;
            array[len-(i+1)]=r+'0';
        }
        array[len]='\0';

        
        char *args[]={array,NULL};
        execvp(argv[1],args);

        
     }
     else{
      printf("Parent message\n");     
      printf("Parent User-id %d\n",getuid());
     }  
     return 0; 
} 
