/*
Assignment 1 question 1 zombie
Create a child process and assign task of computing the Fibonacci series.
*/
#include <sys/types.h>
#include <stdio.h>

int fibonacci(int n){
	if(n<=2)
		return 1;
	else
		return fibonacci(n-1)+fibonacci(n-2);

}

int main(){
	printf("parent process created\n");
	int n;
	pid_t pid=fork();

	if(pid<0){
		printf("failed to create child process\n");
	}else if(pid==0){
		printf("enter n \n");
		scanf("%d",&n);
		printf("child process is calculating fibonacci series\n");
		printf(" fib(n)=%d \n",fibonacci(n));

	}else{
		sleep(8);
		printf("parent process is being executed\n");
	}
	if(pid!=0){
		printf("parent process ends\n");
	}
return 0;	
}
