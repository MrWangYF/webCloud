#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <fcgi_stdio.h>
#include <fcntl.h>
void getS(char *buf, char *s1, char *s2);

int main(int argc, char **argv)
{
	int pid;
	char *method;
	char *str, *path_fifo, *file;
/*	//if(argc < 2)
	//	exit(-1);
	//file = argv[1];
	char a[3][50];

	path_fifo = "/usr/local/nginx/sbin/fifo";
	unlink(path_fifo);
	mkfifo(path_fifo, 777);
*/
	while(FCGI_Accept() >= 0)
	{
		method = getenv("REQUEST_METHOD");
		printf("Content-type: text/html\r\n"
				"\r\n"
				"<title>LI DAWEI</title>"
				"<h1>Hello LeXiang!</h1>"
				"running on host <i>%s</i> \n"
				,getenv("REMOTE_ADDR"));
		if(strncmp(method, "get", 3) == 0 || strncmp(method, "GET", 3) == 0)
		{
			printf("get");
		printf("%s", getenv("QUERY_STRING"));
		}
		else if(strncmp(method, "post", 4) == 0 || strncmp(method, "POST", 4) == 0)
		{
			printf("post");
		printf("%s", getenv("QUERY_STRING"));
		}	
		else
			printf("method is Nothing");
				

	}
/*
	pid = fork();
	if(pid == 0)
	{
		memset(a, 0, sizeof(a));
		strcpy(a[0], "fdfs_upload_file");
		strcpy(a[1], "/etc/fdfs/client.conf");
		strcpy(a[2], "/usr/include/stdlib.h");
	// int execvp(const char *file, char *const argv[]);
	//#sudo fdfs_upload_file /etc/fdfs/client.conf /usr/include/stdlib.h
		printf("%s,%s,%s", a[0], a[1], a[2]);
		execlp(a[0], a[0], a[1], a[2], NULL);
	}
	*/
	return 0;
}

void getS(char *buf, char *s1, char *s2)
{
	char c2[10] = { 0 }, c4[10] = { 0 };
	
	int i, j = 0;
	while (buf[j] != '=')
		j++;
	i = 0;
	j++;
	while (buf[j] != '&')
	{
		c2[i] = buf[j];
		i++; j++;
	}
	i = 0;
	j++;
	while (buf[j] != '=')
	{
		i++; j++;
	}
	i = 0;
	j++;
	while (buf[j] != '\0')
	{
		c4[i] = buf[j];
		i++; j++;
	}
	strcpy(s1, c2);
	strcpy(s2, c4);
}
