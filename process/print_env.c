#include<stdio.h>

extern char ** environ;

int main(int argc, char* argv[]){
    while(*environ){
        puts(*environ);
        environ++;
    }
    for(int i=0;i<argc;i++){
        puts(argv[i]);
    }
    return 0;
}