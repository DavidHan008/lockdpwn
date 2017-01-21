#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>

void main(int argc, char *argv[])
{
  struct sockaddr_in ad1,ad2;
  char *str_ptr;
  char str_arr[20];

  ad1.sin_addr.s_addr = htonl(0x1020304);
  ad2.sin_addr.s_addr = htonl(0x2030405);

  str_ptr = inet_ntoa(ad1.sin_addr);
  strcpy(str_arr, str_ptr);
  printf("dotted-deical notation1 :%s \n",str_ptr);

  inet_ntoa(ad2.sin_addr);
  printf("dotted ..2 : %s \n", str_ptr);
  printf("dotted ..3 : %s \n", str_arr);

}
