/* On-demand 3-thread synchronization */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> // Compile with "gcc cv-sync-2.c -o cv-sync-2 -lpthread"

int done = 0, total_runs = 0, t1_runs = 0, t2_runs = 0, t3_runs = 0, global_index_run = 1, t1_ran = 0, t2_ran = 0, t3_ran = 0;
long * t_id1, * t_id2, * t_id3;
pthread_cond_t cond1 = PTHREAD_COND_INITIALIZER; 
pthread_cond_t cond2 = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond3 = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void thread1_execute(long * t_id1){
  assert(done == 0); 
  for(int i = 0; i < t1_runs; i++){
    if(total_runs == 0){
        break;
      }
      printf("%d: In thread T1, TID=%ld\n",global_index_run,*t_id1);
      global_index_run++;
      t1_ran++;
      total_runs--;
  }
  done = 1;
}

void thread2_execute(long * t_id2){
  assert(done == 1);   
  for(int i = 0; i < t2_runs; i++){
      if(total_runs == 0){
        break;
      }
      printf("%d: In thread T2, TID=%ld\n",global_index_run,*t_id2);
      global_index_run++;
      t2_ran++;
      total_runs--;      
  }
  done = 2;
}

void thread3_execute(long * t_id3){
  assert(done == 2);   
  for(int i = 0; i < t3_runs; i++){
      if(total_runs == 0){
        break;
      }
      printf("%d: In thread T3, TID=%ld\n",global_index_run,*t_id3);
      global_index_run++;
      t3_ran++;
      total_runs--;      
  }
  done = 0;
}

void *thread1_func(void *arg){
  t_id1 = (long*)arg;
  while(total_runs > 0){
    pthread_mutex_lock(&mutex);
    while(done == 1){
      pthread_cond_wait(&cond1,&mutex);
    }
    thread1_execute(t_id1);
    pthread_cond_signal(&cond2);
    pthread_mutex_unlock(&mutex);
  }
}

void *thread2_func(void * arg){
  t_id2 = (long*)arg;
  while(total_runs > 0){
    pthread_mutex_lock(&mutex);
    while(done == 2){
      pthread_cond_wait(&cond2,&mutex);
    }
    thread2_execute(t_id2);
    pthread_cond_signal(&cond3);
    pthread_mutex_unlock(&mutex);
  }
}

void *thread3_func(void * arg){
  t_id3 = (long*)arg;
  while(total_runs > 0){
    pthread_mutex_lock(&mutex);
    while(done == 0){
      pthread_cond_wait(&cond3,&mutex);
    }
    thread3_execute(t_id3);
    pthread_cond_signal(&cond1);
    pthread_mutex_unlock(&mutex);
  }
}

void usage(char * bin_str) {
	printf("Too few arguments. Please pass correct arguments.\n");
    printf("Usage: %s total_runs t1_runs t2_runs t3_runs\n", bin_str);
}

int main(int argc, char * argv[]) {

    if (argc != 5) {
        usage(argv[0]);
        return 0;
    }

    total_runs = atoi(argv[1]);
    t1_runs = atoi(argv[2]);
    t2_runs = atoi(argv[3]);
    t3_runs = atoi(argv[4]);

    pthread_t thread1, thread2, thread3;
    pthread_create(&thread1,NULL,thread1_func,(void *)&thread1);
    pthread_create(&thread2,NULL,thread2_func,(void *)&thread2);
    pthread_create(&thread3,NULL,thread3_func,(void *)&thread3);
    
    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);
    pthread_join(thread3,NULL);

    printf("In main thread: T1 printed %d time(s). T2 printed %d time(s). T3 printed %d time(s)\n",t1_ran,t2_ran,t3_ran);

    return 0;
}
