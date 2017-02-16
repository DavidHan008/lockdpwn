#include <stdio.h>
<<<<<<< HEAD

int main(int argc, char *argv[])
{
  int a = 1;
  printf("1.2.3.4.5.6.");
  return 0;
=======
#include <string.h>

const int kBufSize = 128;

void off_by_one1(char* in_buf)
{
	char out_buf[128] = "";
	int in_buf_len = strlen(in_buf);
	
	for (int i = 0; i <= in_buf_len; i++)
	{
		out_buf[i] = in_buf[i];
	}
	printf("%s\n",out_buf);
}

void off_by_one2(char* in_buf)
{
	char out_buf[128] = "";
	int in_buf_len = strlen(in_buf);

	if (in_buf_len <= kBufSize)
	{
		strcpy(out_buf, in_buf);
	}
	printf("%s\n", out_buf);
}

int main(int argc, char* argv[])
{
	off_by_one1(argv[1]);
	off_by_one2(argv[1]);
	return 0;
>>>>>>> 6f91d3f3ef9d698836e8e67afe573d5c4daee316
}
