#include "pipe_networking.h"


/*=========================
  server_handshake
  args: int * to_client

  Perofrms the client side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe.

  returns the file descriptor for the upstream pipe.
  =========================*/
int server_handshake(int *to_client) {
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
  mkfifo("ctos", 0755);
  char * handshak = "Howdy";
  char shakhand[HANDSHAKE_BUFFER_SIZE];

  int ctos_fd = open("ctos", )
  write("ctos", handhsak, HANDSHAKE_BUFFER_SIZE);
  read("stoc", shakhand, HANDSHAKE_BUFFER_SIZE);
  write("ctos", shakhand, HANDSHAKE_BUFFER_SIZE);
  return 0;
}
