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
  char pid[10];
  sprintf(pid, "%d", getpid());
  mkfifo(pid, 0755); //Created secret pipe to write to server with
  int ctos_fd = open(pid, O_RDONLY); //Open the secret pipe and get its file descriptor
  *to_server = ctos_fd; //Set to_server to the secret pipe's fd
  char * tosend; //Message to send
  sprintf(tosend, "%d" + 0, getpid()); //Write the pid/name of the pipe to tosend

  int stoc_fd = open("wkp", O_WRONLY); //Open the pipe to comm with the server
  write(stoc_fd, tosend, strlen(tosend)); //Write the name of the secret pipe
  remove(pid); //Remove, for security reasons

  char server_message[HANDSHAKE_BUFFER_SIZE]; //Message from server
  read(ctos_fd, server_message, sizeof(server_message)); //Read the Message
  write(stoc_fd, server_message, sizeof(server_message)); //Write back the message

  return stoc_fd; //Downstream pipe






}
