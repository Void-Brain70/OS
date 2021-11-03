#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>
#include <semaphore.h>


#define MaxItems 5 // Maximum items a producer can produce or a consumer can consume
#define BufferSize 5 // Size of the buffer

sem_t empty;
sem_t full;
int in = 0; //buffer index
int out = 0;
int buffer[BufferSize];
pthread_mutex_t mutex;
void *producer(void *pno)
{
    int item;
    for(int i = 0; i < MaxItems; i++) {
        item = rand(); // Produce an random item
        sem_wait(&empty); //check for empty slot
        pthread_mutex_lock(&mutex); //0
        buffer[in] = item;
        printf("Producer %d: Insert Item %d at %d\n", *((int *)pno),buffer[in],in);
        //producer no,produced item,position or buffer index
        in = (in+1)%BufferSize; //
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
}
void *consumer(void *cno)
{
    for(int i = 0; i < MaxItems; i++) {
        sem_wait(&full);//check for full slot
        pthread_mutex_lock(&mutex);
        int item = buffer[out];
        printf("Consumer %d: Remove Item %d from %d\n",*((int *)cno),item, out);
        //consumer no,removed item ,item postion
        out = (out+1)%BufferSize;
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
    }
}

int main(int argc, char *argv[]) {
 //printf("hello world (pid:%d)\n", (int) getpid());
 int rc = fork();
 int rc1=fork();
 while(1){
 if (rc < 0 && rc1<0) {
   fprintf(stderr, "fork failed\n");
   exit(1);//process terminate
 } else if (rc == 0&& rc1==0) {
   (void *)producer;
   printf("hello,from process id:%d\n", (int) getpid());
   printf("hello,from process id:%d\n", (int) getpid());
   (void *)consumer;
 } else {

   int wc = wait(NULL); //parent wait until child terminate
      (void *)producer;
   printf("hello, from process id: %d\n",  (int) getpid());
   printf("hello, from process id: %d\n",  (int) getpid());
   (void *)consumer;
 }
 }


 return 0;
}

