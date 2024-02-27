#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{

  if(argc != 2){
    printf("please enter 2 parameters\n");
    exit(1);
  }else{
    int sleeptime = atoi(argv[1]); // atoi把字符串转换为一个整数（类型为 int 型）
    sleep(sleeptime);

  }
    
  exit(0);
}
