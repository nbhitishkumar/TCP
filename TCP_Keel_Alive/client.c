#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include <netinet/tcp.h>
#include<netinet/in.h>
#include<sys/select.h>
#include<sys/time.h>
#include<netdb.h>

#define mybuf 12345


char *randstring(size_t length) {

    static char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";        
    char *randomString = NULL;

    if (length) {
        randomString = malloc(sizeof(char) * (length +1));

        if (randomString) {            
            for (int n = 0;n < length;n++) {            
                int key = rand() % (int)(sizeof(charset) -1);
                randomString[n] = charset[key];
            }

            randomString[length] = '\0';
        }
    }

    return randomString;
}

int main(int argc, char *argv[]) 
{
  int sfd, portno, n,r,r1;
  int sum=0,s1=0,s2=0,s3=0,s4=0;
  time_t end  = time(NULL) + 14410;
  time_t intervalone,intervaltwo,intervalthree,intervalfour;
  char buf[mybuf];
  int terminate = 1;
  struct sockaddr_in srvaddr;
  struct hostent *host;
  intervalone=time(NULL)+ 3600;
  intervaltwo=intervalone+3600;
  intervalthree=intervaltwo+3600;

  if (argc < 3) { fprintf(stderr,"usage: %s ip port\n", argv[0]); exit(0); }

  portno = atoi(argv[2]);
  sfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sfd < 0) { perror("ERROR: socket()"); exit(0); }

  int flags =1;
  if (setsockopt(sfd, SOL_SOCKET, SO_KEEPALIVE, (void *)&flags, sizeof(flags))) { perror("ERROR: setsocketopt(), SO_KEEPALIVE"); exit(0); };

  flags = 10;
  if (setsockopt(sfd, SOL_TCP, TCP_KEEPIDLE, (void *)&flags, sizeof(flags))) { perror("ERROR: setsocketopt(), SO_KEEPIDLE"); exit(0); };

  host = gethostbyname(argv[1]);
  if (host == NULL) { fprintf(stderr,"ERROR: host does not exist"); exit(0); }

  bzero((char *) &srvaddr, sizeof(srvaddr));
  srvaddr.sin_family = AF_INET;
  srvaddr.sin_port = htons(portno);

  bcopy((char *)host->h_addr, (char *)&srvaddr.sin_addr.s_addr, host->h_length);

  if (connect(sfd, (struct sockaddr *)&srvaddr, sizeof(srvaddr)) < 0) { perror("ERROR: connect()"); exit(0); }


  while(terminate){
      
      if (time(NULL) > end) 
      {
          sum=s1+s2+s3+s4;
          printf("%d %d %d %d %d\n",sum,s1,s2,s3,s4);
	  printf("%d %d",r,r1);
          terminate=0;
          
      }
      else if (time(NULL)<intervalone) {

            
            n=write(sfd,randstring(6),strlen(randstring));
            if (n < 0)
            {
                printf("error wirting  from socket\n");
            }
            s1=s1+sizeof(randstring);
            n = read(sfd,buf,mybuf);
            if (n<0) {
                printf("reading  from socket\n");
            }
	    r=r+sizeof(mybuf);
            printf("%s \n", randstring(6));
      }
      else if (time(NULL)<intervaltwo) {

            
            n=write(sfd,randstring(8),strlen(randstring));
            if (n < 0)
            {
                printf("error wirting  from socket\n");
            }
            s2=s2+sizeof(randstring);
            n = read(sfd,buf,mybuf);
            if (n<0) {
                printf("reading  from socket\n");
            }
	    r1=r1+sizeof(mybuf);
            printf("%s \n", randstring(8));
      }
      else if (time(NULL)<intervalthree) {

            
            n=write(sfd,randstring(10),strlen(randstring));
            if (n < 0)
            {
                printf("error wirting  from socket\n");
            }
            s4=s4+sizeof(randstring);
            n = read(sfd,buf,mybuf);
            if (n<0) {
                printf("reading  from socket\n");
            }
            printf("%s \n", randstring(10));
      }
      
      
      else
      {
           
            n=write(sfd,randstring(11),strlen(randstring));
            if (n < 0)
            {
                printf("error wirting  from socket\n");
            }
            s3=s3+sizeof(randstring);
            n = read(sfd,buf,mybuf);
            if (n<0) {
                printf("reading  from socket\n");
            }
            printf("%s \n", randstring(11));
        }
    }
    
  return 0;
}
