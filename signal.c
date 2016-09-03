#include "myhead.h"

Sigfunc *signal(int signo,Sigfunc *action)
{
	struct sigaction act,oact;

	act.sa_flags=0;
	sigemptyset(&act.sa_mask);
	act.sa_handler=action;

	if(signo==SIGALRM){
#ifdef SA_INTERRUPT
		act.sa_flags|=SA_INTERRUPT;
#endif
	}else{
#ifdef SA_RESTART
		act.sa_flags|=SA_RESTART;
#endif
	}

	if( sigaction(signo,&act,&oact)<0){
		errcode=NOCODE;
		return SIG_ERR;
	}
	return oact.sa_handler;
}//signal

Sigfunc *Signal(int signo,Sigfunc *action)
{
	Sigfunc *oact;
	if( (oact=signal(signo,action))==SIG_ERR)
		err_quit("signal");
	return oact;
}//Signal

void sig_chld(int signo)
{
	pid_t c_pid;
	int stat;

	while( (c_pid=waitpid(-1,&stat,WNOHANG))>0){
		printf("child %d terminated\n",c_pid);
	}//while
}//sig_chld
