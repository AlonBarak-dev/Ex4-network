#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <sys/socket.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#define SIZE 256
#define PORT 8085
 

 /*
    this method responsible for receiving files/data from the client.
    it save the files as well
 */
float write_file(int sock, char* file){
    int n;
    FILE *fp;
    char *filename = file;
    char buffer[SIZE];
    bzero(buffer, SIZE);
    float time = 0;
    clock_t before = clock();
    fp = fopen(filename, "w");
    while (1) { 
        n = recv(sock, buffer, SIZE, 0);
        if (n <= 0){
        clock_t delta = clock() - before;
        time = (delta * 1000) / CLOCKS_PER_SEC;
        break;
        return time;
        }
        fprintf(fp, "%s", buffer);
        bzero(buffer, SIZE);
    }
  
    return time;
}
 
/*
    main method responsible for opening a socket on PORT and receive files from a client
*/

int main (char* argc, char** argv)
{
    
    // initilaize variables   
    char *ip = "127.0.0.1";
    int port = atoi(argv[1]);
    int e;
    socklen_t len;
    int sockfd, new_sock;
    struct sockaddr_in server_addr, new_addr;
    socklen_t addr_size;
    char buffer[SIZE];
    char buf[SIZE];


    // create a socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // cheack if the socket is valid
    if(sockfd<0)
    {
        perror("[-]Error in socket");
        exit(1);
    }
    printf("Server socket created. \n");

    // insert valid values to the server address structure
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = port;
    server_addr.sin_addr.s_addr = inet_addr(ip);

    // binding the socket with the IP and the PORT
    e = bind(sockfd,(struct sockaddr*)&server_addr, sizeof(server_addr));
    if(e<0) // throw error if connection is not valid
    {
        perror("Error in Binding");
        exit(1);
    }
    printf("Binding Successfull.\n");
    
    
    strcpy(buf,"cubic");
    getsockopt(sockfd,IPPROTO_TCP,TCP_CONGESTION,buf,&len);
    printf("Current: %s\n", buf);
    
    // receieve 5 files using the cubic TCP's type
    float avg = 0;
    float sum = 0;
    for (int i = 0; i < 5; i++)
    {
        clock_t before = clock();        // starts counting
        e = listen(sockfd, 10);
        if(e==0)
        {
            printf("Listening...\n");
        }
        else 
        {
            perror("Error in Binding");
            exit(1);
        }
        addr_size = sizeof(new_addr);
        new_sock = accept(sockfd,(struct sockaddr*)&new_addr, &addr_size);

        write_file(new_sock,argv[2]);
        printf("Data written in the text file \n");
        time_t delta = clock() - before;            // stop counting
        sum += delta;
    }
    sum = sum * 1000 / CLOCKS_PER_SEC;
    avg = sum / 5;
    printf("Cubic times: %f\n",avg);        // print the avarage time took to reveive 5 files
    

    // change to reno

    strcpy(buf,"reno");     // reno
    len = strlen(buf);

    // checking if the socket is valid using reno
    if(setsockopt(sockfd,IPPROTO_TCP,TCP_CONGESTION,buf, len)!=0){
        perror("getsocket");
        return -1;
    }
    printf("New: %s \n",buf);

    // reset the sum and avg variables
    avg = 0;
    sum = 0;
    
    // do same as with the cubic type
    for (int i = 0; i < 5; i++)
    {
        clock_t before = clock();        // starts counting
        e = listen(sockfd, 10);
        if(e==0)
        {
            printf("Listening...\n");
        }
        else 
        {
            perror("Error in Binding");
            exit(1);
        }
        addr_size = sizeof(new_addr);
        new_sock = accept(sockfd,(struct sockaddr*)&new_addr, &addr_size);

        write_file(new_sock,argv[2]);
        printf("Data written in the text file \n");
        time_t delta = clock() - before;
        sum += delta;
    }
    sum = sum*1000 / CLOCKS_PER_SEC;
    avg = sum / 5;
    printf("Reno times: %f\n",avg);     // print the avg time took to receive 5 files using reno


    // end program
    return 0;
}





