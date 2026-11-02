#include "types.h"
#include "stat.h"
#include "user.h"

int
main(void)
{
  int pid;

  setnice(getpid(), 5);
  printf(1, "=== R3 TEST START ===\n");

  // Test 1: Change child priority from 6 to 4
  pid = fork();

  if(pid < 0){
    printf(1, "fork failed\n");
    exit();
  }

  if(pid == 0){
    printf(1, "TEST1 CHILD running\n");
    exit();
  }

  printf(1, "TEST1 PARENT before same priority\n");
  setnice(pid, 6);
  printf(1, "TEST1 PARENT after same priority\n");

  printf(1, "TEST1 PARENT before higher priority\n");
  setnice(pid, 4);
  printf(1, "TEST1 PARENT after higher priority\n");
  wait();

  // Test 2: Same priority, higher PID wins
  pid = fork();

  if(pid < 0){
    printf(1, "fork failed\n");
    exit();
  }

  if(pid == 0){
    printf(1, "TEST2 CHILD running\n");
    exit();
  }

  printf(1, "TEST2 PARENT before setnice\n");
  setnice(pid, 5);
  printf(1, "TEST2 PARENT after setnice\n");
  wait();

  // Test 3: Parent lowers its own priority
  pid = fork();

  if(pid < 0){
    printf(1, "fork failed\n");
    exit();
  }

  if(pid == 0){
    printf(1, "TEST3 CHILD running\n");
    exit();
  }

  printf(1, "TEST3 PARENT before setnice\n");
  setnice(getpid(), 20);
  printf(1, "TEST3 PARENT after setnice\n");
  wait();

  printf(1, "=== R3 TEST DONE ===\n");
  exit();
}
