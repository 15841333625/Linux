#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
int main(void){
	int i = 0;
	int count = 0;

	pid_t pid;

	for(i; i < 3; i += 1){
		pid = fork();
		printf("%d \n", i);

		if(pid == 0){
			count ++;
			printf("subprocess %d\n", count);
		} else {
			wait(NULL);
			count ++;
			printf("process %d\n", count);
		}
	}
	return 0;
}
