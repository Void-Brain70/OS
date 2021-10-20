#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
	        printf("Hello World (pid:%d)\n", (int) getpid());
		        int rc = fork();
			        if(rc < 0){
					                fprintf(stderr, "fork failed\n");
							                exit(1);
									        }
				        else if(rc == 0){
						                printf("Hello, I am child (pid:%d)\n", (int) getpid());
								                char *myargs[3];
										                myargs[0] = strdup("ls");
												                myargs[1] = strdup("-Al");
														                myargs[2] = NULL;
																                execvp(myargs[0], myargs);
																		                printf("This shouldn't print out");
																				        }
					        else{
							                int wc = wait(NULL);
									                printf("Hello, I am parent of %d (pid:%d)\n", rc, (int) getpid());
											        }
						        return 0;
}
