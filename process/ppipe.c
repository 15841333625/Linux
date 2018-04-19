#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int f(int x){
	if(x == 1){
		return 1;
	}else if(x > 1){
		return f(x - 1) * x;
	}else{
		printf("illegal input");
		return -1;
	}
}
int g(int x){
	if(x == 1 || x == 2){
		return 1;
	}else if(x > 2){
		return g(x - 1) + g(x - 2);
	}else{
		printf("illegal input");
		return -1;
	}
}
int h(int x, int y){
	return x + y;
}
int main(int argc, char *aargv[]){
	int pipe1[2];
	int pipe2[2];
	int pipe3[2];
	int pipe4[2];
	int pid1;
	int pid2;
	int x, y;

	if(pipe(pipe1) < 0){
		perror("pipe not create");
		exit(EXIT_FAILURE);
	}
	if(pipe(pipe2) < 0){
		perror("pipe not create");
		exit(EXIT_FAILURE);
	}
	if(pipe(pipe3) < 0){
		perror("pipe not create");
		exit(EXIT_FAILURE);
	}
	if(pipe(pipe4) < 0){
		perror("pipe not create");
		exit(EXIT_FAILURE);
	}
	if((pid1 = fork()) < 0){
		perror("process not create");
		exit(EXIT_FAILURE);
	}else if(pid1 ==  0){
		if((pid2 = fork()) < 0){
			perror("process not create");
			exit(EXIT_FAILURE);
		}else if(pid2 == 0){
			close(pipe3[0]);
			close(pipe4[1]);
			read(pipe4[0], &y, sizeof(int));
			y = g(y);
			write(pipe3[1], &y, sizeof(int));
			close(pipe3[1]);
			close(pipe4[0]);
			exit(0);
		}else{
			close(pipe1[0]);
			close(pipe2[1]);
			close(pipe3[1]);
			close(pipe4[0]);
			read(pipe2[0], &x, sizeof(int));
			read(pipe2[0], &y, sizeof(int));
			write(pipe4[1], &y, sizeof(int));
			read(pipe3[0], &y, sizeof(int));
			x = f(x);
			write(pipe1[1], &x, sizeof(int));
			write(pipe1[1], &y, sizeof(int));
			close(pipe1[1]);
			close(pipe2[0]);
			close(pipe3[0]);
			close(pipe4[1]);
			exit(0);
		}
	}else{
		close(pipe1[1]);
		close(pipe2[0]);
		printf("x = ");
		scanf("%d", &x);
		printf("y = ");
		scanf("%d", &y);
		printf("x = %d, y = %d\n", x, y);
		write(pipe2[1], &x, sizeof(int));
		write(pipe2[1], &y, sizeof(int));
		read(pipe1[0], &x, sizeof(int));
		read(pipe1[0], &y, sizeof(int));
  		close(pipe1[0]);
		close(pipe2[1]);
		printf("result = %d\n", h(x, y));
	}
	return 0;
}
