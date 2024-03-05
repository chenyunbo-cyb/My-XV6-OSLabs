#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"
#include "kernel/fs.h"
#include "kernel/param.h"

char *cutoffinput(char *buf);
void substring(char s[], char sub[], int pos, int len);

/* 子串 */
void 
substring(char s[], char *sub, int pos, int len) {
   int c = 0;   
   while (c < len) {
      *(sub + c) = s[pos+c];
      c++;
   }
   *(sub + c) = '\0';
}

//截断
char*
cutoffinput(char *buf){
    if(strlen(buf) > 1 && buf[strlen(buf)-1]=='\n'){
        char *subbuff = (char*)malloc(sizeof(char) * (strlen(buf) - 1));
        substring(buf, subbuff, 0, strlen(buf) -1);
        return subbuff;
    }
    else{
       char *subbuff = (char*)malloc(sizeof(char) * (strlen(buf))); 
       strcpy(subbuff, buf);
       return subbuff;
    }

}

int
main(int argc , char* argv[]){
    int pid;
    char buf[MAXPATH];
    char *args[MAXARG];

    char *cmd; //*cmd ? 

    if(argc == 1){
        cmd = "echo"; //默认命令为echo
    }else{
        cmd = argv[1];
    }

    int args_num = 0;
    while (1)
    {
        memset(buf, 0 , sizeof(buf)); //void *memset(void *str, int c, size_t n) 复制字符 c（一个无符号字符）到参数 str 所指向的字符串的前 n 个字符。
        gets(buf, MAXPATH);

        char *arg = cutoffinput(buf);

        if(strlen(arg) == 0 || args_num >= MAXARG){
            break;
        }
        args[args_num] = arg;
        args_num++;

    }

    int argstartpos = 1;
    char *argv2exec[MAXARG];
    argv2exec[0] = cmd;

    for(; argstartpos < argc ; argstartpos++){
        argv2exec[argstartpos] = argv[argstartpos - 2];
    }

    for (int i = 0; i < args_num; i++)
    {
        /* code */
        argv2exec[i + argstartpos] = args[i];
    }
    argv2exec[args_num + argstartpos] = 0;

    /* 运行cmd */
    if((pid = fork()) == 0){   
        exec(cmd, argv2exec);    
    }  
    else
    {
        /* code */
       wait(0);
    }
    exit(0);    

}