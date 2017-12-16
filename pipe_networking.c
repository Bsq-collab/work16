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
  mkfifo("stoc",0644);
  printf("server pipe created\n");
  int pipe= open("stoc",O_RDONLY);
  *to_client=pipe;
  printf("to_client set to pipe\n");
  printf("Well known pipe waiting for client\n");
  read(pipe,message,sizeof(message));
  printf("message read\n");
  //remove pipe for security
  close(pipe);
  remove("stoc");
  printf("removed server byebye!!\n");

  return 0;
}


/*=========================
  client_handshake
  args: int * to_server

  Performs the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.

  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake(int *to_server) {
  mkfifo(getpid(), 0755);
  int ctos_fd = open(getpid(), O_RDONLY);
  *to_server = ctos_fd;
  char * tosend;
  sscanf(tosend, "%d" + 0, getpid());

  int stoc_fd = open("stoc", O_WRONLY);
  write(stoc_fd, tosend, strlen(tosend));
  close(stoc_fd);

  char server_message[HANDSHAKE_BUFFER_SIZE];
  read(ctos_fd, server_message, sizeof(server_message));






}
