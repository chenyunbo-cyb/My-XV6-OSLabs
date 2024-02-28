#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void process(int pd[]);
void send_primes(int pd[], int infos[], int info_len);
void generate_num(int nums[]);


int
main(int argc , char**argv){
    //声明管道
    int pd[2];

    //create pipe
    pipe(pd);

    int pid;
    if((pid=fork())==0){
        //chile process
        process(pd);
        exit(0);
        
    }else{
        //parent process
        int nums[34];
        generate_num(nums);
        send_primes(pd, nums, 34);
        exit(0);
    }

}

void
process(int pd[]){
    int p;
    int len;
    int n;
    int infos[34];
    int info_i = 0;
    int pid;
    

    int pd_child[2];
    pipe(pd_child);
    
    close(pd[1]); //关闭写，开始读管道数据
    len = read(pd[0], &p, sizeof(p));
    printf("prime %d\n", p);
    

    //filter 
    while (len!=0)
    {
        /* code */
        len = read(pd[0], &n, sizeof(n));
        if(n % p != 0){
            *(infos + info_i) = n;
            info_i++;
        } 
    }

    close(pd[0]);

    if(info_i==0){
        exit(0);

    } 

    
    if((pid=fork())==0){
        //chile process
        process(pd_child);
        
    }else{
        //parent process
        send_primes(pd_child, infos, info_i);
    }

    //exit(0); 



}

void 
generate_num(int nums[]){
    int i = 0;
    for(int count=2; count<=35; count++){
        nums[i] = count;
        i++;
    }
}

void 
send_primes(int pd[], int infos[], int info_len){
    
    close(pd[0]);
    for(int i=0 ; i<info_len; i++)
    {
        write(pd[1], &infos[i], sizeof(infos[i]));
    }
    //write(pd[1], infos, info_len);

}