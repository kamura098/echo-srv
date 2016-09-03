#include "myhead.h"

//##########	in_buff	------------------------>	>	>	>

char *init_in_buff(in_buff *ib)
{
	if(ib==NULL){
		errcode=NOCODE;
		return NULL;
	}
	memset(ib,0,sizeof(in_buff));
	ib->buffptr=ib->buff;

	return ib->message;
}//init_in_buff

char *Init_in_buff(in_buff *ib)
{
	char *ptr;
	if( (ptr=init_in_buff(ib)) ==NULL)
		err_quit("init_in_buff");
	return ptr;
}//Init_in_buff

//##########	in_buff	------------------------>	>	>	>


//##########	Write	------------------------>	>	>	>

int sndLine(int fd,char *str,...)
{
	char buff[MAXLINE];
	va_list vp;

	va_start(vp,str);
	vsnprintf(buff,sizeof(buff),str,vp);
	va_end(vp);


	Writen(fd,buff,strlen(buff));
	Writen(fd,"\n",1);

}//Writen

int writen(int fd,char *str,int len)
{
	int snt=0;

	char *ptr=str;


	while(len>0){
		if( (snt=write(fd,ptr,len)) <0){
			if(errno==EINTR)
				continue;
			errcode=ERNO;
			return -1;
		}else if(snt>0){
			ptr+=snt;
			len-=snt;
		}
	}//while

	return 0;
}//writen

void Writen(int fd,char *str,int len)
{
	if(writen(fd,str,len)<0)
		err_quit("writen");
}//Writen

//##########	Write	------------------------>	>	>	>


//##########	Read	------------------------>	>	>	>

ssize_t my_read(int fd,in_buff *ib,char *ptr)
{
	if(ib->rcv_cnt<=0){
again:
		if( (ib->rcv_cnt=read(fd,ib->buff,MAXBUFF))<0){
			if(errno==EINTR)
				goto again;
			errcode=ERNO;
			return -1;
		}else if(ib->rcv_cnt==0){
			*ptr=0;
			return 0;
		}
		ib->buffptr=ib->buff;
	}
	ib->rcv_cnt--;
	*ptr=*ib->buffptr++;
	return 1;
}//my_read

ssize_t recvn(int fd,in_buff *ib)
{
	int n,rcv;
	char c,*ptr=ib->message;
	for(n=1;n<MAXLINE;n++){
		if( (rcv=my_read(fd,ib,&c))<0)
			return -1;
		else if(rcv==0){
			*ptr=0;
			errcode=NOCODE;
			return n-1;
		}else if(c=='\n'){
			break;
		}
		*ptr++=c;
	}//for
	*ptr=0;
	return n;
}//recvn

ssize_t Recvn(int fd,in_buff *ib)
{
	ssize_t n;
	if( (n=recvn(fd,ib))<0)
		err_quit("rcvn");
	return n;
}//Recvn

//##########	Read	------------------------>	>	>	>
