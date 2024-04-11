#include "kernel/types.h"
#include "kernel/riscv.h"
#include "kernel/sysinfo.h"
#include "user/user.h"
#include "kernel/sysinfo.h"



int
main(int argc, char *argv[])
{
  if(argc != 1){
    prinf("sysinfo need not param\n");
    exit(1);
  }
  struct sysinfo info;
  sysinfo(&info);
  printf("free sapce:%d, used process num:%d\n", info.freenum, info.nproc);
  exit(0);
}
