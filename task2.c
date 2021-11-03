#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, char *argv[]){
        printf("Hello World (pid:%d)\n", (int) getpid());
        int rc = fork();
        if(rc < 0){

                fprintf(stderr, "fork failed\n");
                exit(1);
        }
        else if(rc == 0){
                close(STDOUT_FILENO);
                open("./forking_with_wait.c", O_CREAT | O_WRONLY | O_TRUNC | S_IRWXU);
                char *myargs[3];
                myargs[0] = strdup("stat");
                myargs[1] = strdup("forking_with_wait.c");
                myargs[2] = NULL;
                execvp(myargs[0], myargs);
                printf("This shouldn't print out");
        }
        else{
                int wc = wait(NULL);
                printf("Hello, I am parent of %d (wc:%d) (pid:%d)\n", rc, wc, (int) getpid());
        }
        return 0;
}
