#include "types.h"
#include "stat.h"
#include "user.h"

int
main(void)
{
  int pid;

  setnice(getpid(), 5);

  pid = fork();

  if(pid < 0){
    printf(1, "fork failed\n");
    exit();
  }

  if(pid == 0){
    printf(1, "CHILD is running\n");
    exit();
  }

  printf(1, "PARENT before setnice\n");

  setnice(pid, 4);

  printf(1, "PARENT after setnice\n");

  wait();
  exit();
}
