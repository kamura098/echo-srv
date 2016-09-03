#include "myhead.h"

void doit(int fd);

int main(int argc,char *argv[])
{
	int listenfd,connfd;
	struct sockaddr_in srvaddr,cliaddr;

	Signal(SIGCHLD,sig_chld);

	listenfd=Socket(AF_INET,SOCK_STREAM,0);

	memset(&srvaddr,0,sizeof(srvaddr));
	srvaddr.sin_family=AF_INET;
	srvaddr.sin_port=htons(PORT);
	srvaddr.sin_addr.s_addr=htonl(INADDR_ANY);

	Bind(listenfd,(struct sockaddr*)&srvaddr,sizeof(srvaddr));

	Listen(listenfd,5);

	for(;;){
		connfd=Accept(listenfd,NULL,NULL);
		if(fork()==0){//child process
			Close(listenfd);
			doit(connfd);
			exit(0);
		}
		Close(connfd);
	}//for

}//main

void doit(int fd)
{
	in_buff buff;
	char *str=Init_in_buff(&buff);

	while( Recvn(fd,&buff)!=0){
		sndLine(fd,"you sent %s",str);
		printf("%s\n",str);
	}//while
}//doit
