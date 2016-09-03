#include "myhead.h"

void doit(int fd);

int main(int argc,char *argv[])
{
	if(argc!=2){
		printf("./cli <server ipv4.addr>");
		exit(1);
	}
	struct sockaddr_in srvaddr;
	int sockfd;

	sockfd=Socket(AF_INET,SOCK_STREAM,0);

	memset(&srvaddr,0,sizeof(srvaddr));
	srvaddr.sin_family=AF_INET;
	srvaddr.sin_port=htons(PORT);
	Inet_pton(AF_INET,argv[1],&srvaddr.sin_addr);

	Connect(sockfd,(struct sockaddr*)&srvaddr,sizeof(srvaddr));

	doit(sockfd);

	return 0;
}

void doit(int fd)
{
	in_buff buff;
	char *str=Init_in_buff(&buff);
	char line[MAXLINE];

	while( Fgets(line,MAXLINE,stdin) !=NULL){
		sndLine(fd,"%s",line);
		Recvn(fd,&buff);
		printf("%s\n",str);
	}//while
}//doit
