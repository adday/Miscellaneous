//expox.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int expox(char* X, char* N);

int Usage(){
	printf("Usage: ./expox <x value (float <1)> < Number of terms n (int)>");
	return 1;
}

int main(int argc, char *argv[])
{   
  if(argc != 3)
	return Usage();
  return expox(argv[1],argv[2]); 
}

int expox(char* X, char* N){
  double x = atof(X);
  if(!(x>0) || !(x<1)){
	printf("The value of x is outside of the range (0,1)\n");
	return 1;}
  pid_t pid;
  int status;
  pid = fork();
  if(pid < 0){//error
	printf("Fork failed");
 	return 1;
	}
  else if (pid == 0){//child process
	execlp("./expoxch","./expoxch",X,N,NULL);
  	}
  else {//parent process
  	wait(&status);
        printf("Child exit code: %d %s\n", WEXITSTATUS(status), status == 0?"(ok)":"(error)");
  	printf("Parent (PID = %d): done\n", (int)getpid());
	}
  return 0;
}


