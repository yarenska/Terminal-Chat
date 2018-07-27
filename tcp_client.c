#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

int main(){

    time_t timer;
    char buffer[26];
    struct tm* tm_info;
    
    // creating the socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    // specifying the socket
    struct sockaddr_in serv_addr;
    memset(&serv_addr, '0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(9003);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    
    // connecting socket

    int conn = connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if(conn == -1){
        perror("Error connecting socket");
    }
    else{
        printf("Connected.\n\n");
    }
    
    int flag = 0;
    while(flag == 0){
    // sending my message
    char *cl_msg = malloc(50 * sizeof(char));
    printf(">> ");
    fgets(cl_msg, 50, stdin);
    send(sockfd, cl_msg, strlen(cl_msg), 0);
    free(cl_msg);
     
    // receiving the message
    char serv_msg[256];
    bzero(serv_msg,256);
    
    if (read(sockfd, serv_msg, 256) < 0) {
         perror("ERROR reading from socket");
    }
    
    else {
         
         time(&timer);
    	 tm_info = localtime(&timer);

    	 strftime(buffer, 26, "%Y-%m-%d %H:%M:%S", tm_info);	
         
         printf("-- %s(%s)\n", serv_msg, buffer);
     }
    }

    close(sockfd);
    
    return 0;
}
