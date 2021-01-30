#include<stdio.h>			/* fprintf perror */
#include<stdlib.h>		/* exit */
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/uio.h>

static void simple_cat(const char *path);
static void die(const char *str);

int main(int argc, char *argv[])
{
	int i;
	
	if(argc < 2){
		fprintf(stderr, "%s: file name not given\n",argv[0]);
		exit(1);
	}
	for(i = 0;i < argc; i++)
		simple_cat(argv[i]);
	exit(0);
}

#define BUFSIZE 4096

static void simple_cat(const char *path)
{
	int fd;
	unsigned char buf[BUFSIZE];
	ssize_t cc;

	if((fd = open(path,O_RDONLY)) == -1)
		die(path);
	for(;;){
		cc = read(fd, buf, sizeof buf);
		if(cc == -1)
			die(path);
		if(cc == 0)
			break;
		if(write(STDOUT_FILENO, buf, cc) == -1)
			die(path);
	}
	if(close(fd) == -1)
		die(path);
}

static void die(const char *str)
{
	perror(str);
	exit(1);
}
