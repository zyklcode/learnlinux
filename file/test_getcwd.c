#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>


int main(void){
    // char buf[1024] = {'\0'};
    // if(getcwd(buf, 12)==NULL){
    //    perror("getcwd");
    //    exit(1);	
    // }
    char *cwd = getcwd(NULL, 0);
    puts(cwd);
    free(cwd);
    return 0;    
}
