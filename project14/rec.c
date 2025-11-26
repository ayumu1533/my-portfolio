#include<signal.h>
#include <unistd.h>
#include<stdio.h>
void sig_handler(int signum){
	printf("OK\n");
}
int main(){
	signal(SIGUSR1,sig_handler);
	while(1){
	printf("z\n");
	sleep(1);
	}
	return 0;
}
