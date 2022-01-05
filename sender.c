#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <math.h>
#define SIZE 256
#define PORT 8085
 
void send_file(FILE *fp, int sock){
    /*
        this method sends the file to the server through a given socket
    */
    char data[SIZE] = {0};
    
    while(fgets(data, SIZE, fp) != NULL) {
        if (send(sock, data, sizeof(data), 0) == -1) {  // send the file to the server
            perror("[-]Error in sending file.");
            exit(1);
        }
        bzero(data, SIZE);
    }
}
 


int main(char* argc, char* argv[]){

    // default values in case no input was given
    if (argc == 0)
    {
        argv[0] = "./sender";
        argv[1] = "100mb.txt";      // file name
        argv[2] = "8087";       // PORT
    }
    
    // send a file five times using cubic algorithm
    for (int i = 0; i < 5; i++)
    {
        
        char *ip = "127.0.0.1";     // ip address of the local host
        int port = atoi(argv[1]);   // use the given PORT
        int e;

        int sockfd; // socket variable
        struct sockaddr_in server_addr;     // struct for the server address
        FILE *fp;   // pointer to the file we want to send
        char *filename = argv[2];   // import the file name from the arguments 

        // create a socket for IPv4 using the TCP protocol (cubic)
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if(sockfd<0)    // check if the socket creation failed or not
        {
            perror("[-]Error in socket");
            exit(1);// exit if failed
        }


        printf("[+]Server socket created. \n");

        // set address to connect to
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = port;
        server_addr.sin_addr.s_addr = inet_addr(ip);

        // create a connection from the client to the server
        e = connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
        if(e == -1)     // check if the connection failed
        {
            perror("[-]Error in Connecting");
            exit(1); // exit if failed
        }

        printf("[+]Connected to server.\n");
        // open the file
        fp = fopen(filename, "r");
        if(fp == NULL)      // if the file isnt found , raise error and exit
        {
            perror("[-]Error in reading file.");
            exit(1);
        }
        // send the file to the server we connected to
        send_file(fp,sockfd);
        printf("[+] File data send successfully. \n");
        close(sockfd);      // close the socket
        printf("[+]Disconnected from the server. \n");
    }


    // send the file five times using reno algorithm 
    for (int i = 0; i < 5; i++)
    {
        
        char *ip = "127.0.0.1";     // ip address of the local host
        int port = atoi(argv[1]);    // use the given PORT
        int e;
        char buf[SIZE];
        socklen_t len;
        
        int sockfd; // socket variable
        struct sockaddr_in server_addr;     // struct for the server address
        FILE *fp;   // pointer to the file we want to send
        char *filename = argv[2];   // import the file name from the arguments 
        
        // create a socket for IPv4 using the TCP protocol (reno)
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if(sockfd<0)        // check if the socket creation failed or not
        {
            perror("[-]Error in socket");
            exit(1);
        }
        printf("[+]Server socket created. \n");

        // set the server which we connect to 
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = port;
        server_addr.sin_addr.s_addr = inet_addr(ip);
        
        strcpy(buf,"reno");     // copy reno to the buffer
        len = strlen(buf);
        // change the congestion control protocol from cubic to reno
        if(setsockopt(sockfd,IPPROTO_TCP,TCP_CONGESTION,buf,len) != 0){
            perror("setsockopt");
            return -1;      // exit if failed
        }
        printf("New: %s", buf);

        // connect to the server using the socket
        e = connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
        if(e == -1)
        {
            perror("[-]Error in Connecting");
            exit(1);        // exit if failed
        }
        printf("[+]Connected to server.\n");
        // open the desired file 
        fp = fopen(filename, "r");
        if(fp == NULL)
        {
            perror("[-]Error in reading file.");
            exit(1);
        }
        // send file to the server
        send_file(fp,sockfd);
        printf("[+] File data send successfully. \n");
        close(sockfd);
        printf("[+]Disconnected from the server. \n");

    }

    return 0;
}




