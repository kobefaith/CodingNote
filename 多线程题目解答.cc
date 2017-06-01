子线程循环 10 次，接着主线程循环 100 次，接着又回到子线程循环 10 次，接着再回到主线程又循环 100 次，如此循环50次，试写出代码。
#include <stdio.h> 
#include <stdlib.h> 
#include <pthread.h> 
#include <unistd.h> 
#include <string.h> 

#define LOOP 5

int num = 0; 
int parm_0 = 0; 
int parm_1 = 1;

pthread_mutex_t mylock = PTHREAD_MUTEX_INITIALIZER; 
pthread_cond_t qready=PTHREAD_COND_INITIALIZER;

void* thread_func(void *arg)
{
    int i, j;
    for(i = 0; i < LOOP; i++)
    {
        pthread_mutex_lock(&mylock);
       while(parm_0 != num)
            pthread_cond_wait(&qready, &mylock);
    
        printf("thread: \n");
        for(j = 0; j < 10; j++)
            printf(" %d ", j);
        printf("\n");
        
       num = (num + 1) % 2;
        pthread_mutex_unlock(&mylock);
        pthread_cond_signal(&qready);
    }
    
    return (void*) 0;
}

int main()
{
    int i, k;
    pthread_t tid;
    void *tret;
    
    
    pthread_create(&tid, NULL, thread_func, NULL);
    
    for(i = 0; i < LOOP; i++)
    {
        pthread_mutex_lock(&mylock);
        
        while(parm_1 != num)
            pthread_cond_wait(&qready, &mylock);
        
        printf("main: \n");
        for(k = 0; k < 10; k++)
            printf(" %d", k + 100);
        printf("\n");
        
        num = (num + 1) % 2;
        pthread_mutex_unlock(&mylock);
        pthread_cond_signal(&qready);
    }
    
    pthread_join(tid, &tret);    
}
编写一个程序，开启3个线程，这3个线程的ID分别为A、B、C，每个线程将自己的ID在屏幕上打印10遍，要求输出结果必须按ABC的顺序显示；如：ABCABC….依次递推。

#include <stdio.h> 
#include <stdlib.h> 
#include <pthread.h> 
#include <unistd.h> 
#include <string.h> 
#define DEBUG 1 
  
int num = 0; 
pthread_mutex_t mylock = PTHREAD_MUTEX_INITIALIZER; 
pthread_cond_t qready=PTHREAD_COND_INITIALIZER;

void* thread_func(void *arg)
{
    int param = (int) arg;
    int i;
    
    for(i = 0; i < 10; i++)
    {
        pthread_mutex_lock(&mylock);
        
        while(param != num)
            pthread_cond_wait(&qready, &mylock);
        
        printf("%c", param + 'A');
        num = (num + 1) % 3;
        
        pthread_mutex_unlock(&mylock);
        pthread_cond_broadcast(&qready);
    }
    
    return (void *)0;
}

int main()
{
    int i;
    pthread_t tid[3];
    void *tret;
    
    for(i = 0; i < 3; i++)
        pthread_create(&tid[i], NULL, thread_func, (void *) i);
    for(i = 0; i < 3; i++)
        pthread_join(tid[i], &tret);    
}


/*
* 有四个线程1、2、3、4。线程1的功能就是输出A，线程2的功能就是输出B，以此类推.........
* 现在有四个文件file1, file2,file3, file4。初始都为空。现要让四个文件呈如下格式：
* file1：A B C D A B....
* file2：B C D A B C....
* file3：C D A B C D....
* file4：D A B C D A....
*/
#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

pthread_t threads[4];
char writer_char[4] = {'A','B', 'C', 'D'};
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

struct file_res{
    pthread_t *writer; /*当前文件可以被那个线程写入*/
    int fd; /*文件描述符*/
}file_res[4] = 
{
    {.writer=&threads[0]},/*file1初始化可以被线程1写入'A'*/
    {.writer=&threads[1]},/*file2初始化可以被线程2写入'B'*/
    {.writer=&threads[2]},/*file3初始化可以被线程3写入'C'*/
    {.writer=&threads[3]},/*file4初始化可以被线程4写入'D'*/
};

void *writer_routine(void *arg)
{
    int index = (int)arg;
    int file_index[4] ;
    int can_write_file_cnt = 0;
    int i = 0;
    int next_index=0;
    printf("thread %d is running, and will write '%c' to files\n", index, writer_char[index]);
    
    while(1)
    {
        if (0!=pthread_mutex_lock(&mutex))
            exit(-1);
        for(;;) {
         /*下面的for语句查询本线程可以写的文件id*/
            for(i=0; i<(sizeof(file_res)/sizeof(file_res[0])); i++) {
                if (&threads[index]==file_res[i].writer) {
                    file_index[can_write_file_cnt++] = i;
                    next_index = index+1;
                    if (next_index>3)next_index=0;
                    file_res[i].writer = &threads[next_index];
                }
            }
            /*找到本线程可以写的文件id,则退出for(;;), 执行写操作*/
            if (can_write_file_cnt != 0)
                break;
            /*等待其他线程唤醒*/
            pthread_cond_wait(&cond,&mutex);
        }        
        
        /*本线程可以写的文件,执行写操作*/
        for(i=0; i<can_write_file_cnt; i++) {
            write(file_res[file_index[i]].fd, &writer_char[index], sizeof(writer_char[index]));
        }
        can_write_file_cnt = 0;
        
        /*唤醒下一批线程*/
        pthread_cond_broadcast(&cond);
        if (0!=pthread_mutex_unlock(&mutex))
            exit(-1);    
    }
}
 
int main(int argc, char* argv[])
{
    int i;
    
    for(i=0; i<4; i++)
    {
        char file_name[] = "filex";
        sprintf(file_name, "file%d", i+1);
        if ((file_res[i].fd = open(file_name, O_RDWR|O_CREAT|O_TRUNC, 0666))<0)
        {
            printf("open %s error.\n", file_name);
            exit(-1);
        }
    }
    
    for (i=0; i<(sizeof(threads)/sizeof(pthread_t)); i++)
    {
        if(pthread_create(&threads[i], NULL, writer_routine, (void *)i))
        {
            printf("create writer thread error\n");
            exit(-1);
        }
    }
    pthread_exit(NULL);
    return 0;
}