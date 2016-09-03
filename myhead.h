#ifndef MY_HEAD
#define MY_HEAD

#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<string.h>
#include<stdarg.h>
#include<signal.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

#define PORT 9788
#define MAXLINE 512
#define MAXBUFF 1024

typedef void Sigfunc(int);

/*
 *################
 *	errs.c
 *################
 */

extern int errcode;
#define NOCODE 0
#define ERNO 1

void err_quit(const char *str);

//errs.c


/*
 *################
 *	rWr.c
 *################
 */

typedef struct{
	char buff[MAXBUFF];
	char message[MAXLINE];
	char *buffptr;
	int rcv_cnt;
}in_buff;

char *init_in_buff(in_buff *ib);

char *Init_in_buff(in_buff *ib);

void Writen(int fd,char *str,int len);

int writen(int fd,char *str,int len);

int sndLine(int fd,char *str,...);

ssize_t my_read(int fd,in_buff *ib,char *ptr);

ssize_t recvn(int fd,in_buff *ib);

ssize_t Recvn(int fd,in_buff *ib);

//rWr.c


/*
 *################
 *	wrapers.c
 *################
 */

int Socket(int domain,int type,int protocol);

void Bind(int fd,struct sockaddr *sa,socklen_t salen);

void Listen(int fd,int backlog);

int Accept(int fd,struct sockaddr *sa,socklen_t *salen);

void Connect(int fd,struct sockaddr *sa,socklen_t salen);

void Close(int fd);

char *Fgets(char *buff,ssize_t siz,FILE *fp);

//wrapers.c

/*
 *################
 *	signal.c
 *################
 */

Sigfunc *signal(int signo,Sigfunc *action);

Sigfunc *Signal(int signo,Sigfunc *action);

void sig_chld(int signo);

//signal.c

#endif
