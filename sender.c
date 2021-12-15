#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#define SIZE 1024
 
void send_file(FILE *fp, int sock){
  //int n;
  char data[SIZE] = {0};
 
  while(fgets(data, SIZE, fp) != NULL) {
    if (send(sock, data, sizeof(data), 0) == -1) {
      perror("[-]Error in sending file.");
      exit(1);
    }
    bzero(data, SIZE);
  }
}
 
int main(){
  char *ip = "127.0.0.1";
  int port = 8080;
  int e;


  //-------------------------------------

    char buf[SIZE];
    socklen_t len;
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock == -1)
    {
        perror("socket");
        return -1;
    }

    len = sizeof(buf);

    if (getsockopt(sock, IPPROTO_TCP, TCP_CONGESTION, buf, &len) != 0)
    {
        perror("getsockopt");
        return -1;
    }

    printf("Current: %s\n", buf);

  //-------------------------------------
 
  struct sockaddr_in server_addr;
  FILE *fp;
  char *filename = "1000Nodes.json";
 
  
  printf("[+]Server socket created successfully.\n");
  
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = port;
  server_addr.sin_addr.s_addr = inet_addr(ip);
 
  e = connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
  if(e == -1) {
    perror("[-]Error in socket");
    exit(1);
  }
 printf("[+]Connected to Server.\n");
 
  fp = fopen(filename, "r");
  if (fp == NULL) {
    perror("[-]Error in reading file.");
    exit(1);
  }
  printf("%d", sock);
  for (int i = 0; i < 5; i++)
  {
    send_file(fp, sock);
  }
  printf("[+]File data sent successfully in cubic.\n");

    close(sock);
  //--------------------------------------------

    sock = socket(AF_INET, SOCK_STREAM, 0);

    strcpy(buf, "reno");

    len = strlen(buf);

    if (setsockopt(sock, IPPROTO_TCP, TCP_CONGESTION, buf, len) != 0)
    {
        perror("setsockopt");
        return -1;
    }

    len = sizeof(buf);

    if (getsockopt(sock, IPPROTO_TCP, TCP_CONGESTION, buf, &len) != 0)
    {
        perror("getsockopt");
        return -1;
    }

    printf("New: %s\n", buf);

  //--------------------------------------------
e = connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
  if(e == -1) {
    perror("[-]Error in socket");
    exit(1);
  }
 printf("[+]Connected to Server.\n");
 
  fp = fopen(filename, "r");
  if (fp == NULL) {
    perror("[-]Error in reading file.");
    exit(1);
  }

printf("%d", sock);
for (int i = 0; i < 5; i++)
  {
      
    send_file(fp, sock);
  }
  printf("[+]File data sent successfully in reno.\n");



  printf("[+]Closing the connection.\n");
  close(sock);
 
  return 0;
}