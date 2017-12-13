#include "pipe_networking.h"


/*=========================
  server_handshake
  args: int * to_client

  Performs the client side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe.

  returns the file descriptor for the upstream pipe.
  =========================*/
int server_handshake(int *to_client) {
  char message[256];
  // creates the well known pipe server waits for connection
  mkfifo("server",0644);
  printf("server pipe created\n");
  int pipe= open("server",O_RDONLY);
  *to_client=pipe;
  printf("to_client set to pipe\n");
  printf("Well known pipe waiting for client\n");
  read(pipe,message,sizeof(message));
  printf("message read\n");
  //remove pipe for security
  //close(pipe);
  remove("server");
  printf("removed server byebye!!\n");
  int m=open(message,O_WRONLY);
  write(m,"writingback",100);
  printf("Server wrote back\n");
  return m;

}


/*=========================
  client_handshake
  args: int * to_server

  Performs the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.

  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake(int *to_server) {
  return 0;
}
