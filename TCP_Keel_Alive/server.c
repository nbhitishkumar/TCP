#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include <netinet/tcp.h>
#include<netinet/in.h>
#include<sys/select.h>
#include<sys/time.h>
#include<netdb.h>



int main(int argc, char *argv[])
{
  int sfd, rfd, portno, clilen;
  char buffer[256];
  struct sockaddr_in serv_addr, cli_addr;
  int n,s;

  if (argc < 2) { perror("ERROR: no port\n"); exit(1); }

  sfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sfd < 0) { perror("ERROR: socket()"); exit(1); }

  bzero((char *) &serv_addr, sizeof(serv_addr));
  portno = atoi(argv[1]);
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(portno);

  if (bind(sfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) { perror("ERROR: bind()"); exit(1); }

  listen(sfd, 3);

  while (1) {
    clilen = sizeof(cli_addr);
    rfd = accept(sfd, (struct sockaddr *) &cli_addr, &clilen);
    if (rfd < 0) { perror("ERROR: accept()"); exit(1); }

    while (1) {

      bzero(buffer,256);
      n = read(rfd, buffer,255);
      if (n <= 0) { 
        printf("%d",s);
        printf("read() ends\n"); 
        break; }
      printf("received: %s %d\n", buffer,n);
      s=s+n;
      n = write(rfd, buffer,sizeof(buffer));
      
      if (n < 0) { perror("ERROR: write()"); exit(1); }
    }
  }

  return 0;
}
