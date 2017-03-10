#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define BUFF_SIZE 512


void str_remake(char str[]){
	int length = strlen(str);

	int i=0;
	for(i; i < length; i++){
		int ch = str[i];
		if(str[i]>='a' && str[i]<='z'){
			str[i] = ch - 32;
		}
	}
}

int start_rewriting(int descr_from , int descr_to){

    char buff[512];
	size_t nbyte;

    int all_data = 0;
    ssize_t bytes_readen = -1;
    while(bytes_readen!=0){

	    bytes_readen = read(descr_from, buff, BUFF_SIZE);
	    str_remake(buff);
	    ssize_t bytes_written = write(descr_to, buff, bytes_readen);

	    all_data = all_data + bytes_written;
	}
	return all_data;
}

int main(int argc, char *argv[]){

    int descr_file_from = open(argv[1], O_RDONLY);
    mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;

    int descr_file_to = open(argv[2], O_WRONLY | O_CREAT, mode);

    if(descr_file_to == -1 ){
    	printf("Error has occured while opening file %s !\n%s", argv[2], strerror(errno));
    }
    
    int all_data = start_rewriting(descr_file_from, descr_file_to);

    close(descr_file_from);
    close(descr_file_to)
;
    printf("All rewriten bytes: %d\n", all_data);

    return 0;
}