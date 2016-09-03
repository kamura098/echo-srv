#include"myhead.h"

int Socket(int domain,int type,int protocol)
{
	int n;
	if( (n=socket(domain,type,protocol)) <0){
		errcode=ERNO;
		err_quit("socket");
	}
	return n;
}//Socket

void Bind(int fd,struct sockaddr *sa,socklen_t salen)
{
	if(bind(fd,sa,salen)<0){
		errcode=ERNO;
		err_quit("bind");
	}//if
}//Bind

void Listen(int fd,int backlog)
{
	if(listen(fd,backlog)<0){
		errcode=ERNO;
		err_quit("listen");
	}//if
}//Listen

int Accept(int fd,struct sockaddr *sa,socklen_t *salen)
{
	int n;
start:
	if( (n=accept(fd,sa,salen))<0){
		if(errno==EINTR)
			goto start;
		errcode=ERNO;
		err_quit("accept");
	}
	return n;

}//Accept

void Connect(int fd,struct sockaddr *sa,socklen_t salen)
{
	if(connect(fd,sa,salen)<0){
		errcode=ERNO;
		err_quit("connect");
	}//if
}//connect

void Inet_pton(int af,const char *src,void *dst)
{
	if(inet_pton(af,src,dst)<0){
		errcode=ERNO;
		err_quit("inet_pton");
	}
}//Inet_pton

void Close(int fd)
{
	if(close(fd)<0){
		errcode=ERNO;
		err_quit("close");
	}//if
}//Close

char *Fgets(char *buff,ssize_t siz,FILE *fp)
{
	char *str,*tmp;
	if( (str=fgets(buff,siz,fp)) ==NULL&&ferror(fp)){
		errcode==NOCODE;
		err_quit("fgets");
	}
	if( (tmp=strchr(buff,'\n'))!=NULL)
		*tmp=0;

	return str;
}//str
