#include "pipe_networking.h"


/*=========================
  server_handshake
  args: int * to_client

  Performs the client side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe.

  returns the file descriptor for the upstream pipe.
  =========================*/
int server_handshake(int *to_client) {
  char message[HANDSHAKE_BUFFER_SIZE];
  // creates the well known pipe server waits for connection
  mkfifo("wkp",0644);
  printf("wkp pipe created\n");
  int from_client= open("wkp",O_RDONLY);
  printf("to_client set to pipe\n");
  printf("Well known pipe waiting for client\n");
  read(from_client,message,sizeof(message));
  printf("message read: %s\n",message);
  //remove pipe for security
  remove("server");
  printf("removed server byebye!!\n");
  *to_client=open(message,O_WRONLY);
  write(*to_client,ACK,sizeof(message));
  printf("Server wrote back\n");
  return from_client;

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
