#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>


int main(void){

    time_t timer;
    char buffer[26];
    struct tm* tm_info;

    // creating the socket 
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    // specifying the serv_addr with parameters
    struct sockaddr_in serv_addr;
    memset(&serv_addr, '0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(9003);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    
    // bind the socket with the parameters 
    bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    
    // listening socket. queue is defined as 10.
    listen(sockfd, 10);
    
    // accepting the client socket side.
    int size_serv = sizeof(struct sockaddr_in);	
    int client_socket = accept(sockfd, (struct sockaddr *)&serv_addr, &size_serv);
    if(client_socket == EAGAIN){
        printf("Error");
    }
    else{
        printf("Connection detected.\n\n");
 	}
   
    int flag = 0;

    while(flag == 0){

    // sending the server message
    char buff[256];
    bzero(buff,256);
    int n;
    n = read(client_socket, buff, 256);
    if(n < 0){ 
	perror("Error reading from socket"); 
 	}

    time(&timer);
    tm_info = localtime(&timer);

    strftime(buffer, 26, "%Y-%m-%d %H:%M:%S", tm_info);	

    printf("-- %s(%s)\n", buff, buffer);
    
    char *my_msg = (char *)malloc(50 * sizeof(char));
    printf(">> ");
    fgets(my_msg, 50, stdin);
    send(client_socket, my_msg, strlen(my_msg), 0);
    free(my_msg);
    }
    
    close(sockfd);
    return 0;
}
