#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024

void error_handling(char *message);

void main(int argc, char *argv[])
{
  int sock;
  char opmsg[BUF_SIZE];
  int result, opnd_cnt, i;

  struct sockaddr_in serv_adr;
  if (argc != 3)
  {
    printf("nope");
    exit(1);
  }

  sock = socket(PF_INET, SOCK_STREAM,0);
  if (sock == -1)
  {
    error_handling("socket() error");
  }

  memset(&serv_adr, 0, sizeof(serv_adr));
  serv_adr.sin_family = AF_INET;
  serv_adr.sin_addr.s_addr = inet_addr(argv[1]);
  serv_adr.sin_port = htons(atoi(argv[2]));

  if (connect(sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)
  {
    error_handling("connect() error");
  }
  else
  {
    puts("conneted...");
  }

  while (1)
  {
    fputs("operand count", stdout);

    fputs("operand 1", stdout);

    fputs("operator", stdout);


    fputs("operation result: ", stdout);


  }







}


void error_handling(char *message)
{
  fputs(message, stderr);
  fputc('\n', stderr);
  exit(1);
}
