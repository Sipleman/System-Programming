#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#define MSG_LEN 64

int start_select(char *identificator){
	char buffer[255];
	fd_set rfds;
	struct timeval tv;
	int retval;

    FD_ZERO(&rfds);
    FD_SET(STDIN_FILENO, &rfds);

    tv.tv_sec = 5;
    tv.tv_usec = 0;

	retval = select(STDOUT_FILENO, &rfds, NULL, NULL, &tv);

    if (retval == -1)
        perror("select()");
    else if (retval){
        printf("Data is available now.\n");
	    read(STDIN_FILENO, buffer, 1024);
	    printf( "%s : %s", identificator, buffer);
	}
    else{
    	return -1;
    }
}


int main(int argc, char *argv[]){

	if(argc != 2){
		printf("You need to enter argument!");
		return -1;
	}
	char *identificator = argv[1];
	while(start_select(identificator) == -1){
		char tmp[MSG_LEN];
    	sprintf(tmp, "%s Time is gone", identificator);
    	perror(tmp);
	}
    return 0;
}