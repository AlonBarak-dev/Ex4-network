#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <sys/socket.h>
#include <unistd.h>
#include <time.h>
#define SIZE 256
 
float write_file(int sock){
    int n;
    FILE *fp;
    char *filename = "recv.txt";
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
 
int main ()
{
    
        
        char *ip = "127.0.0.1";
        int port = 80;
        int e;

        int sockfd, new_sock;
        struct sockaddr_in server_addr, new_addr;
        socklen_t addr_size;
        char buffer[SIZE];
        char buf[SIZE];
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if(sockfd<0)
        {
            perror("[-]Error in socket");
            exit(1);
        }
        printf("[+]Server socket created. \n");

        server_addr.sin_family = AF_INET;
        server_addr.sin_port = port;
        server_addr.sin_addr.s_addr = inet_addr(ip);

        e = bind(sockfd,(struct sockaddr*)&server_addr, sizeof(server_addr));
        if(e<0)
        {
            perror("[-]Error in Binding");
            exit(1);
        }
        printf("[+]Binding Successfull.\n");
    printf("Current: %s\n", buf);
    float avg = 0;
    float sum = 0;
    for (int i = 0; i < 5; i++)
    {
        time_t before = clock();        // starts counting
        e = listen(sockfd, 10);
        if(e==0)
        {
            printf("[+]Listening...\n");
        }
        else 
        {
            perror("[-]Error in Binding");
            exit(1);
        }
        addr_size = sizeof(new_addr);
        new_sock = accept(sockfd,(struct sockaddr*)&new_addr, &addr_size);

        write_file(new_sock);
        printf("[+]Data written in the text file \n");
        time_t delta = clock() - before;
        sum += delta;
    }
    sum = sum *1000 / CLOCKS_PER_SEC;
    avg = sum / 5;
    printf("Cubic times: %f\n",avg);

    strcpy(buf,"reno");     // reno
    socklen_t len = strlen(buf);

    if(setsockopt(sockfd,IPPROTO_TCP,TCP_CONGESTION,buf, len)!=0){
        perror("getsocket");
        return -1;
    }
    printf("New: %s \n",buf);

    avg = 0;
    sum = 0;

    for (int i = 0; i < 5; i++)
    {
        time_t before = clock();        // starts counting
        e = listen(sockfd, 10);
        if(e==0)
        {
            printf("[+]Listening...\n");
        }
        else 
        {
            perror("[-]Error in Binding");
            exit(1);
        }
        addr_size = sizeof(new_addr);
        new_sock = accept(sockfd,(struct sockaddr*)&new_addr, &addr_size);

        write_file(new_sock);
        printf("[+]Data written in the text file ");
        time_t delta = clock() - before;
        sum += delta;
    }
    sum = sum *1000 / CLOCKS_PER_SEC;
    avg = sum / 5;
    printf("Reno times: %f\n",avg);








    return 0;
}



























//if (sock == -1)
// {
//     perror("socket");
//     return -1;
// }

// len = sizeof(buf);

// if (getsockopt(sock, IPPROTO_TCP, TCP_CONGESTION, buf, &len) != 0)
// {
//     perror("getsockopt");
//     return -1;
// }

// printf("Current: %s\n", buf);

// //-----------------------------------------------------------------------

//   int new_sock;
//   struct sockaddr_in server_addr, new_addr;
//   socklen_t addr_size;
//   char buffer[SIZE];
 
// //   sock = socket(AF_INET, SOCK_STREAM, 0);
// //   if(sock < 0) {
// //     perror("[-]Error in socket");
// //     exit(1);
// //   }
//   printf("[+]Server socket created successfully.\n");
 
//   server_addr.sin_family = AF_INET;
//   server_addr.sin_port = port;
//   server_addr.sin_addr.s_addr = inet_addr(ip);
 
//   e = bind(sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
//   if(e < 0) {
//     perror("[-]Error in bind");
//     exit(1);
//   }
//   printf("[+]Binding successfull.\n");
 
//   if(listen(sock, 10) == 0){
//     printf("[+]Listening....\n");
//   }
//   else{
//     perror("[-]Error in listening");
//     exit(1);
//   }

// addr_size = sizeof(new_addr);
// new_sock = accept(sock, (struct sockaddr*)&new_addr, &addr_size);

 
// time_cubic += write_file(new_sock);
// printf("%f",time_cubic);
// printf("[+]Data written in the file successfully in cubic.\n");
// close(sock);

// //------------------------------------

// sock = socket(AF_INET, SOCK_STREAM, 0);
// strcpy(buf, "reno");

// len = strlen(buf);

// if (setsockopt(sock, IPPROTO_TCP, TCP_CONGESTION, buf, len) != 0)
// {
//     perror("setsockopt");
//     return -1;
// }

// len = sizeof(buf);

// if (getsockopt(sock, IPPROTO_TCP, TCP_CONGESTION, buf, &len) != 0)
// {
//     perror("getsockopt");
//     return -1;
// }

// printf("New: %s\n", buf);
// //------------------------------------

//   if(listen(sock, 10) == 0){
//     printf("[+]Listening....\n");
//   }
//   else{
//     perror("[-]Error in listening");
//     exit(1);
//   }

// addr_size = sizeof(new_addr);
// new_sock = accept(sock, (struct sockaddr*)&new_addr, &addr_size);

// time_reno += write_file(new_sock);
// printf("%f",time_reno);
// printf("[+]Data written in the file successfully in reno.\n");





// close(sock);
// return 0;