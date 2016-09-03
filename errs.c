#include "myhead.h"

int errcode=0;

void err_quit(const char *str)
{
	switch(errcode){
	case ERNO:
		perror(str);
		break;
	default:
		printf("err: %s\n",str);
	}//switch
	exit(1);
}//err_quit
