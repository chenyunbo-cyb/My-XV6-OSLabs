#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char** argv){

    int pid;  

    int parent_id[2];
    int child_id[2];
    char buf[20];
    
    pipe(parent_id);  // [0]:read读取 ； [1]:write写入
    pipe(child_id);

    // Child
    if((pid=fork()) == 0){  //子进程创建返回0
        close(parent_id[1]); //关闭父进程写入
        read(parent_id[0], buf , 4); //读取
        printf("%d: received %s\n", getpid(), buf);

        close(child_id[0]);
        write(child_id[1], "pong", sizeof(buf));
        exit(0);

    }else{
        close(parent_id[0]); //读端关闭
        write(parent_id[1], "ping", sizeof(buf)); //向写端 进行一个写

        close(child_id[1]);
        read(child_id[0], buf, 4);
        printf("%d: received %s\n", getpid(), buf);
        
        exit(0);

    }
    
}
